#include "sppch.h"
#include "Application.h"

#include "Input.h"

#include "Spindel/Renderer/Renderer.h"

#include "GLFW/glfw3.h"

#include "imgui.h"

namespace Spindel {

	Application* Application::s_Instance = nullptr;


	Application::Application(const std::string& title) 
		: m_Accumalator(0.0), m_UpdatePeriod(0.01)
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;
		WindowProps prop;
		prop.Title = title;
		m_Window = std::unique_ptr<Window>(Window::Create(prop));
		m_Window->SetEventCallback(SP_BIND_EVENT_FN(Application::OnEvent));

		AssetManager::Init(m_Cache, m_Bundle);
		Renderer::Init();
		Renderer::WaitAndRender();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		// TEMPORARY
		m_LastFrameTime = glfwGetTime();
	}

	Application::~Application() {

	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SP_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::RenderImGui()
	{
		m_ImGuiLayer->Begin();

		ImGui::Begin("Renderer");
		auto& caps = RendererAPI::GetCapabilities();
		ImGui::Text("Vendor: %s", caps.Vendor.c_str());
		ImGui::Text("Renderer: %s", caps.Renderer.c_str());
		ImGui::Text("Version: %s", caps.Version.c_str());
		ImGui::Text("Frame Time: %.2fms\n", m_Timestep.GetMilliseconds());
		ImGui::End();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

		m_ImGuiLayer->End();
	}


	void Application::Run() 
	{
		
		while (m_Running)
		{

			m_Accumalator += m_Timestep.GetSeconds();
			while (m_Accumalator >= m_UpdatePeriod)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				//////////
				m_Accumalator -= m_UpdatePeriod;
			}
			
			for (Layer* layer : m_LayerStack)
				layer->OnRender();

			// Render ImGui on render thread
			Application* app = this;
			Renderer::Submit([app]() { app->RenderImGui(); });


			Renderer::WaitAndRender();
			
			m_Window->OnUpdate();

			float time = glfwGetTime();
			m_Timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		//Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
		return true;
	}
}