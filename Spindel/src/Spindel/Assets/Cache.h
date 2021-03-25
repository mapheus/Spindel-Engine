#pragma once

#include <string>
#include <vector>
#include "Spindel/Core/Core.h"

#include "Bundle.h"
#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Shader.h"
#include "Spindel/Renderer/Resources/Mesh.h"

namespace Spindel
{
    class Bundle;
    class Loader;

    class Cache
    {
        friend Bundle;
    public:
        Cache();

        Cache(const Cache&) = delete;
        Cache& operator=(const Cache&) = delete;

        Cache(Cache&&) = delete;
        Cache& operator=(Cache&&) = delete;

        auto& getBundles() const noexcept { return bundles; }
        auto& getLoaders() const noexcept { return loaders; }

        Ref<Texture2D> getTexture(const std::string& name) const;
        const Ref<Shader> getShader(const std::string& name) const;
        const Ref<Mesh> getMesh(const std::string& name) const;

    private:
        void addBundle(const Bundle* bundle);
        void removeBundle(const Bundle* bundle);

        void addLoader(Scope<Loader> loader);
        void removeLoader(const Loader* loader);

        std::vector<const Bundle*> bundles;
        std::vector<Scope<Loader>> loaders;

    };
}