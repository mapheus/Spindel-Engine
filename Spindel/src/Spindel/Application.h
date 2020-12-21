#pragma once

#include "Core.h"

#include "Window.h"
#include "Spindel/LayerStack.h"
#include "Events/Event.h"
#include "Spindel/Events/ApplicationEvent.h"

#include "Spindel/ImGui/ImGuiLayer.h"

namespace Spindel {

	class SPINDEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// Define in client
	Application* CreateApplication();
}

