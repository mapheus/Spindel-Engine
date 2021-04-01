#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace Spindel
{
    class Cache;
    class Bundle;

    class Loader
    {
    public:
        enum class Type
        {
            staticMesh,
            image,
            shader
        };

        Loader(Cache& initCache, Type initType) :
            m_Cache{ initCache }, m_Type{ initType }
        {
        }

        virtual ~Loader() = default;

        Loader(const Loader&) = delete;
        Loader& operator=(const Loader&) = delete;

        Loader(Loader&&) = delete;
        Loader& operator=(Loader&&) = delete;

        auto getType() const noexcept { return m_Type; }

        virtual bool loadAsset(Bundle& bundle,
            const std::string& name,
            const std::string& filename,
            bool mipmaps = true) = 0;

    protected:
        Cache& m_Cache;
        Type m_Type;
    };
}
