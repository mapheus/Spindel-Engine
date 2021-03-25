#include "sppch.h"
#include "Bundle.h"

#include <cctype>
#include <stdexcept>
#include "Loader.h"

namespace Spindel
{
    Bundle::Bundle(Ref<Cache>& cache)
        : m_Cache(cache)
    {
        m_Cache->addBundle(this);
    }

    Bundle::~Bundle()
    {
        textures.clear();
        staticMesh.clear();
        shaders.clear();
        m_Cache->removeBundle(this);
    }

    void Bundle::loadAsset(Loader::Type loaderType, const std::string& name,
        const std::string& filename, bool mipmaps)
    {
        const auto& loaders = m_Cache->getLoaders();

        for (auto i = loaders.rbegin(); i != loaders.rend(); ++i)
        {
            Loader* loader = i->get();
            if (loader->getType() == loaderType &&
                loader->loadAsset(*this, name, filename, mipmaps))
                return;
        }

        throw std::runtime_error("Failed to load asset " + filename);
    }


    void Bundle::loadAssets(const std::vector<Asset>& assets)
    {
        for (const auto& asset : assets)
            loadAsset(asset.type, asset.name, asset.filename, asset.mipmaps);
    }

   Ref<Texture2D> Bundle::getTexture(const std::string& name) const
    {
        if (const auto i = textures.find(name); i != textures.end())
            return i->second;

        return nullptr;
    }

    void Bundle::setTexture(const std::string& name, const Ref<Texture2D>& texture)
    {
        textures[name] = texture;
    }

    void Bundle::releaseTextures()
    {
        textures.clear();
    }

    const Ref<Shader> Bundle::getShader(const std::string& name) const
    {
        if (const auto i = shaders.find(name); i != shaders.end())
            return i->second;

        return nullptr;
    }

    void Bundle::setShader(const std::string& name, Ref<Shader> shader)
    {
        shaders[name] = std::move(shader);
    }

    void Bundle::releaseShaders()
    {
        shaders.clear();
    }


    const Ref<Mesh> Bundle::getMesh(const std::string& name) const
    {
        if (const auto i = staticMesh.find(name); i != staticMesh.end())
            return i->second;
        return nullptr;
    }

    void Bundle::setMesh(const std::string& name, Ref<Mesh>& newStaticMeshData)
    {
        staticMesh[name] = newStaticMeshData;
    }

    void Bundle::releaseStaticMesh()
    {
        staticMesh.clear();
    }
}