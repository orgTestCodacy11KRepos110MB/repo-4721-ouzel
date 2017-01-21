// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <atomic>
#define NOMINMAX
#include <d3d11.h>
#include "graphics/Renderer.h"
#include "graphics/TextureResource.h"

namespace ouzel
{
    namespace graphics
    {
        class RendererD3D11: public Renderer
        {
            friend Engine;
        public:
            virtual ~RendererD3D11();
            virtual void free() override;

            virtual bool present() override;

            virtual std::vector<Size2> getSupportedResolutions() const override;

            virtual BlendStateResourcePtr createBlendState() override;
            virtual TextureResourcePtr createTexture() override;
            virtual ShaderResourcePtr createShader() override;
            virtual MeshBufferResourcePtr createMeshBuffer() override;
            virtual IndexBufferResourcePtr createIndexBuffer() override;
            virtual VertexBufferResourcePtr createVertexBuffer() override;

            ID3D11Device* getDevice() const { return device; }
            ID3D11DeviceContext* getContext() const { return context; }

        protected:
            RendererD3D11();

            virtual bool init(Window* newWindow,
                              const Size2& newSize,
                              uint32_t newSampleCount,
                              TextureResource::Filter newTextureFilter,
                              PixelFormat newBackBufferFormat,
                              bool newVerticalSync,
                              bool newDepth) override;
            bool update();
            bool resizeBackBuffer(UINT newWidth, UINT newHeight);

            virtual bool saveScreenshot(const std::string& filename) override;

            IDXGIOutput* getOutput() const;

            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* context = nullptr;
            IDXGISwapChain* swapChain = nullptr;
            IDXGIAdapter* adapter = nullptr;
            ID3D11Texture2D* backBuffer = nullptr;
            ID3D11RenderTargetView* renderTargetView = nullptr;
            ID3D11SamplerState* samplerState = nullptr;
            ID3D11RasterizerState* rasterizerStates[4];
            ID3D11Texture2D* depthStencilTexture = nullptr;
            ID3D11DepthStencilView* depthStencilView = nullptr;
            ID3D11DepthStencilState* depthStencilStates[4];
            ID3D11ShaderResourceView* resourceViews[TextureResource::LAYERS];
            ID3D11SamplerState* samplerStates[TextureResource::LAYERS];

            UINT width = 0;
            UINT height = 0;

            UINT swapInterval = 0;
            FLOAT frameBufferClearColor[4];
            bool clearColorBuffer = true;
            bool clearDepthBuffer = false;
        };
    } // namespace graphics
} // namespace ouzel
