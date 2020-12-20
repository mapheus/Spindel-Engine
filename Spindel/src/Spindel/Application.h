#pragma once

#include "Core.h"

namespace Spindel {

	class SPINDEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Define in client
	Application* CreateApplication();
}

