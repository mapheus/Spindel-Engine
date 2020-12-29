#include <Spindel.h>

#include "Spindel/Core/EntryPoint.h"
#include "Test.h"


class Sandbox : public Spindel::Application
{
public:
	Sandbox() : Spindel::Application("Sandbox")
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