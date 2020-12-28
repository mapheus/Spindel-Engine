#pragma once

#include "Spindel/Core/Layer.h"

#include "Spindel/Events/MouseEvent.h"
#include "Spindel/Events/ApplicationEvent.h"
#include "Spindel/Events/KeyEvent.h"

namespace Spindel {
	class SPINDEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 60.f;
	};
}