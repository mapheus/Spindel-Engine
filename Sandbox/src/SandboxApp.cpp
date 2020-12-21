#include <Spindel.h>

#include "imgui/imgui.h"

class TestLayer : public Spindel::Layer
{
public:
	TestLayer()
		: Layer("Test")
	{

	}

	void OnUpdate() override
	{
		if (Spindel::Input::IsKeyPressed(SP_KEY_E))
			SP_WARN("E was pressed");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("WOW!");
		ImGui::End();
	}

	void OnEvent(Spindel::Event& event) override
	{

	}
};


class Sandbox : public Spindel::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	~Sandbox()
	{

	}
};

Spindel::Application* Spindel::CreateApplication()
{
	return new Sandbox();
}