// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_TEXTURE_HPP
#define OUZEL_GRAPHICS_TEXTURE_HPP

#include <vector>
#include "graphics/GraphicsResource.hpp"
#include "graphics/CubeFace.hpp"
#include "graphics/PixelFormat.hpp"
#include "graphics/SamplerAddressMode.hpp"
#include "graphics/SamplerFilter.hpp"
#include "math/Color.hpp"
#include "math/Size.hpp"
#include "utils/Inline.h"

namespace ouzel
{
    namespace graphics
    {
        class Renderer;

        class Texture final
        {
        public:
            enum class Dimensions
            {
                ONE,
                TWO,
                THREE,
                CUBE
            };

            enum Flags
            {
                DYNAMIC = 0x01,
                BIND_RENDER_TARGET = 0x02,
                BIND_SHADER = 0x04,
                BIND_SHADER_MSAA = 0x08
            };

            struct Level final
            {
                Size2U size;
                uint32_t pitch;
                std::vector<uint8_t> data;
            };

            Texture() = default;

            explicit Texture(Renderer& initRenderer);
            Texture(Renderer& initRenderer,
                    const Size2U& newSize,
                    uint32_t newFlags = 0,
                    uint32_t newMipmaps = 0,
                    uint32_t newSampleCount = 1,
                    PixelFormat newPixelFormat = PixelFormat::RGBA8_UNORM);
            Texture(Renderer& initRenderer,
                    const std::vector<uint8_t>& newData,
                    const Size2U& newSize,
                    uint32_t newFlags = 0,
                    uint32_t newMipmaps = 0,
                    PixelFormat newPixelFormat = PixelFormat::RGBA8_UNORM);
            Texture(Renderer& initRenderer,
                    const std::vector<Level>& newLevels,
                    const Size2U& newSize,
                    uint32_t newFlags = 0,
                    PixelFormat newPixelFormat = PixelFormat::RGBA8_UNORM);

            ALWAYSINLINE const Resource& getResource() const { return resource; }

            ALWAYSINLINE const Size2U& getSize() const { return size; }

            void setData(const std::vector<uint8_t>& newData);
            void setData(const std::vector<uint8_t>& newData, CubeFace face);

            ALWAYSINLINE uint32_t getFlags() const { return flags; }
            ALWAYSINLINE uint32_t getMipmaps() const { return mipmaps; }

            ALWAYSINLINE SamplerFilter getFilter() const { return filter; }
            void setFilter(SamplerFilter newFilter);

            ALWAYSINLINE SamplerAddressMode getAddressX() const { return addressX; }
            void setAddressX(SamplerAddressMode newAddressX);

            ALWAYSINLINE SamplerAddressMode getAddressY() const { return addressY; }
            void setAddressY(SamplerAddressMode newAddressY);

            ALWAYSINLINE SamplerAddressMode getAddressZ() const { return addressZ; }
            void setAddressZ(SamplerAddressMode newAddressZ);

            ALWAYSINLINE Color getBorderColor() const { return borderColor; }
            void setBorderColor(Color newBorderColor);

            ALWAYSINLINE uint32_t getMaxAnisotropy() const { return maxAnisotropy; }
            void setMaxAnisotropy(uint32_t newMaxAnisotropy);

            ALWAYSINLINE uint32_t getSampleCount() const { return sampleCount; }

            ALWAYSINLINE PixelFormat getPixelFormat() const { return pixelFormat; }

        private:
            Renderer& renderer;
            Resource resource;

            Dimensions dimensions = Dimensions::TWO;
            Size2U size;
            uint32_t flags = 0;
            uint32_t mipmaps = 0;
            uint32_t sampleCount = 1;
            PixelFormat pixelFormat = PixelFormat::RGBA8_UNORM;
            SamplerFilter filter = SamplerFilter::DEFAULT;
            SamplerAddressMode addressX = SamplerAddressMode::CLAMP_TO_EDGE;
            SamplerAddressMode addressY = SamplerAddressMode::CLAMP_TO_EDGE;
            SamplerAddressMode addressZ = SamplerAddressMode::CLAMP_TO_EDGE;
            Color borderColor;
            uint32_t maxAnisotropy = 0;
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_TEXTURE_HPP
