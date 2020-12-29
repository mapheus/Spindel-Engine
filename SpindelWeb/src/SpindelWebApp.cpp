#include <Spindel.h>
#include "EditorLayer.h"

#include "Spindel/Core/EntryPoint.h"

namespace Spindel {

	class SpindelWeb : public Application
	{
	public:
		SpindelWeb() : Application("SpindelWeb")
		{
			PushLayer(new EditorLayer());
		}
		~SpindelWeb()
		{

		}
	};

	Application* CreateApplication()
	{
		return new SpindelWeb();
	}

}