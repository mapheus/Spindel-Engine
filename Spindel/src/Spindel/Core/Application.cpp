#include "sppch.h"
#include "Application.h"

#include "Input.h"

#include "Spindel/Renderer/Renderer.h"

#include "GLFW/glfw3.h"

namespace Spindel {

	Application* Application::s_Instance = nullptr;



	Application::Application() 
		: m_Accumalator(0.0), m_UpdatePeriod(0.01)
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SP_BIND_EVENT_FN(Application::OnEvent));


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

	void Application::Run() 
	{
		
		while (m_Running)
		{
			Spindel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			Spindel::RenderCommand::Clear();

			float newTime = glfwGetTime();
			Timestep timestep = newTime - m_LastFrameTime;
			m_LastFrameTime = newTime;

			m_Accumalator += timestep.GetSeconds();
			while (m_Accumalator >= m_UpdatePeriod)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				//////////
				m_Accumalator -= m_UpdatePeriod;
			}
			
			for (Layer* layer : m_LayerStack)
				layer->OnRender();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}