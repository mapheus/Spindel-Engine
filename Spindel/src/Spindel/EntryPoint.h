#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spindel::Application* Spindel::CreateApplication();

void main(int argc, char** argv)
{
	printf("Spindel Engine\n");
	auto app = Spindel::CreateApplication();
	app->Run();
	delete app;
}

#endif