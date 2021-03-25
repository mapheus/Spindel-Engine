#pragma once

#include <map>
#include <memory>
#include <string>
#include "Loader.h"
#include "Cache.h"
#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Shader.h"
#include "Spindel/Renderer/Resources/Mesh.h"

namespace Spindel
{
    class Cache;

    class Asset final
    {
    public:
        Asset(Loader::Type initType,
            const std::string& initName,
            const std::string& initFilename,
            bool initMipmaps = true) :
            type(initType),
            name(initName),
            filename(initFilename),
            mipmaps(initMipmaps)
        {
        }

        Loader::Type type;
        std::string name;
        std::string filename;
        bool mipmaps;
    };

    class Bundle
    {
        friend Cache;
    public:
        Bundle(Ref<Cache>& cache);
        ~Bundle();

        Bundle(const Bundle&) = delete;
        Bundle& operator=(const Bundle&) = delete;

        Bundle(Bundle&&) = delete;
        Bundle& operator=(Bundle&&) = delete;

        void loadAsset(Loader::Type loaderType, const std::string& name,
            const std::string& filename, bool mipmaps = true);
        void loadAssets(const std::vector<Asset>& assets);

        Ref<Texture2D> getTexture(const std::string& name) const;
        void setTexture(const std::string& name, const Ref<Texture2D>& texture);
        void releaseTextures();

        const Ref<Shader> getShader(const std::string& shaderName) const;
        void setShader(const std::string& name, Ref<Shader> shader);
        void releaseShaders();

        const Ref<Mesh> getMesh(const std::string& name) const;
        void setMesh(const std::string& name, Ref<Mesh>& newStaticMesh);
        void releaseStaticMesh();

    private:
        Ref<Cache> m_Cache;

        std::map<std::string, Ref<Texture2D>> textures;
        std::map<std::string, Ref<Shader>> shaders;
        std::map<std::string, Ref<Mesh>> staticMesh;

    };
}