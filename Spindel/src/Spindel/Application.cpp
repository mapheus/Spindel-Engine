#include "sppch.h"
#include "Application.h"


#include "glad/glad.h"

namespace Spindel {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SP_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {

	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SP_BIND_EVENT_FN(Application::OnWindowClosed));
		//SP_CORE_TRACE("{0}", e);

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
			glClearColor(0.2, 0.2, 0.6, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}