#include <Spindel.h>

class Sandbox : public Spindel::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Spindel::Application* Spindel::CreateApplication()
{
	return new Sandbox();
}