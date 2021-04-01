#pragma once

#include "Core.h"

#include "Window.h"
#include "Spindel/Core/LayerStack.h"
#include "Spindel/Events/Event.h"
#include "Spindel/Events/ApplicationEvent.h"

#include "Spindel/ImGui/ImGuiLayer.h"

#include "Spindel/Core/Timestep.h"

#include "Spindel/Assets/AssetManager.h"

namespace Spindel {

	class Application
	{
	public:
		Application(const std::string& title = "Spindel App");
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;

		Ref<Cache> m_Cache;
		Ref<Bundle> m_Bundle;

		double m_UpdatePeriod;
		double m_Accumalator;
		double m_LastFrameTime;
	private:
		static Application* s_Instance;

	};

	// Define in client
	Application* CreateApplication();
}

