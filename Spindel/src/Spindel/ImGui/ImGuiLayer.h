#pragma once

#include "Spindel/Core/Layer.h"

#include "Spindel/Events/MouseEvent.h"
#include "Spindel/Events/ApplicationEvent.h"
#include "Spindel/Events/KeyEvent.h"

namespace Spindel {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 60.f;
	};
}