#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spindel::Application* Spindel::CreateApplication();

void main(int argc, char** argv)
{
	Spindel::Log::Init();
	SP_CORE_WARN("Initialized Log.");
	int a = 5;
	SP_INFO("App! {0}", a);
	auto app = Spindel::CreateApplication();
	app->Run();
	delete app;
}

#endif