#include <Spindel.h>

class ExampleLayer : public Spindel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
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
		PushLayer(new ExampleLayer());
		PushOverlay(new Spindel::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Spindel::Application* Spindel::CreateApplication()
{
	return new Sandbox();
}