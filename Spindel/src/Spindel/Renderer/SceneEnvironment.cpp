#include "sppch.h"
#include "SceneEnvironment.h"

#include "SceneRenderer.h"

namespace Spindel {

	Environment Environment::Load(const std::string& filepath)
	{
		auto [radiance, irradiance] = SceneRenderer::CreateEnvironmentMap(filepath);
		return { filepath, radiance, irradiance };
	}
}