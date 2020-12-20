#include "sppch.h"
#include "Application.h"

#include "Spindel/Events/ApplicationEvent.h"


namespace Spindel {
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() 
	{
		
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}