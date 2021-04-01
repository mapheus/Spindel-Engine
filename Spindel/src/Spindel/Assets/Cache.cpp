#include "sppch.h"

#include <algorithm>
#include "Cache.h"
#include "ImageLoader.h"
//#include "ModelLoader.h"

namespace Spindel
{

    Cache::Cache()
    {
        addLoader(CreateScope<ImageLoader>(*this));
        //addLoader(CreateScope<ModelLoader>(*this));
    }

    void Cache::addBundle(const Bundle* bundle)
    {
        if (std::find(bundles.begin(), bundles.end(), bundle) == bundles.end())
            bundles.push_back(bundle);
    }

    void Cache::removeBundle(const Bundle* bundle)
    {
        if (const auto i = std::find(bundles.begin(), bundles.end(), bundle); i != bundles.end())
            bundles.erase(i);
    }

    void Cache::addLoader(Scope<Loader> loader)
    {
        if (const auto i = std::find(loaders.begin(), loaders.end(), loader); i == loaders.end())
            loaders.push_back(std::move(loader));
    }

    void Cache::removeLoader(const Loader* loader)
    {
        const auto i = std::find_if(loaders.begin(), loaders.end(), [loader](const auto& ownedLoader) noexcept {
            return false;
            return loader == ownedLoader.get();
            });
        if (i != loaders.end())
            loaders.erase(i);
    }

    Ref<Texture2D> Cache::getTexture(const std::string& name) const
    {
        for (const auto bundle : bundles)
        {
            if (const auto texture = bundle->getTexture(name))
                return texture;
        }

        return nullptr;
    }

    const Ref<Shader> Cache::getShader(const std::string& name) const
    {
        for (const auto bundle : bundles)
            if (const auto shader = bundle->getShader(name))
                return shader;

        return nullptr;
    }

    /*
    const Ref<Mesh> Cache::getMesh(const std::string& name) const
    {
        for (const auto bundle : bundles)
        {
            if (const auto meshData = bundle->getMesh(name))
                return meshData;
        }

        return nullptr;
    }
    */
}