// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "BlendStateD3D11.h"
#include "RendererD3D11.h"
#include "core/Engine.h"
#include "utils/Log.h"

namespace ouzel
{
    namespace graphics
    {
        BlendStateD3D11::BlendStateD3D11()
        {
        }

        BlendStateD3D11::~BlendStateD3D11()
        {
            if (blendState)
            {
                blendState->Release();
            }
        }

        void BlendStateD3D11::free()
        {
            BlendStateResource::free();

            if (blendState)
            {
                blendState->Release();
                blendState = nullptr;
            }
        }

        static D3D11_BLEND getBlendFactor(BlendStateResource::BlendFactor blendFactor)
        {
            switch (blendFactor)
            {
                case BlendStateResource::BlendFactor::ZERO: return D3D11_BLEND_ZERO;
                case BlendStateResource::BlendFactor::ONE: return D3D11_BLEND_ONE;
                case BlendStateResource::BlendFactor::SRC_COLOR: return D3D11_BLEND_SRC_COLOR;
                case BlendStateResource::BlendFactor::INV_SRC_COLOR: return D3D11_BLEND_INV_SRC_COLOR;
                case BlendStateResource::BlendFactor::SRC_ALPHA: return D3D11_BLEND_SRC_ALPHA;
                case BlendStateResource::BlendFactor::INV_SRC_ALPHA: return D3D11_BLEND_INV_SRC_ALPHA;
                case BlendStateResource::BlendFactor::DEST_ALPHA: return D3D11_BLEND_DEST_ALPHA;
                case BlendStateResource::BlendFactor::INV_DEST_ALPHA: return D3D11_BLEND_INV_DEST_ALPHA;
                case BlendStateResource::BlendFactor::DEST_COLOR: return D3D11_BLEND_DEST_COLOR;
                case BlendStateResource::BlendFactor::INV_DEST_COLOR: return D3D11_BLEND_INV_DEST_COLOR;
                case BlendStateResource::BlendFactor::SRC_ALPHA_SAT: return D3D11_BLEND_SRC_ALPHA_SAT;
                case BlendStateResource::BlendFactor::BLEND_FACTOR: return D3D11_BLEND_BLEND_FACTOR;
                case BlendStateResource::BlendFactor::INV_BLEND_FACTOR: return D3D11_BLEND_INV_BLEND_FACTOR;
                default: return D3D11_BLEND_ZERO;
            }
        }

        static D3D11_BLEND_OP getBlendOperation(BlendStateResource::BlendOperation blendOperation)
        {
            switch (blendOperation)
            {
                case BlendStateResource::BlendOperation::ADD: return D3D11_BLEND_OP_ADD;
                case BlendStateResource::BlendOperation::SUBTRACT: return D3D11_BLEND_OP_SUBTRACT;
                case BlendStateResource::BlendOperation::REV_SUBTRACT: return D3D11_BLEND_OP_REV_SUBTRACT;
                case BlendStateResource::BlendOperation::MIN: return D3D11_BLEND_OP_MIN;
                case BlendStateResource::BlendOperation::MAX: return D3D11_BLEND_OP_MAX;
                default: return D3D11_BLEND_OP_ADD;
            }
        }

        bool BlendStateD3D11::upload()
        {
            if (!BlendStateResource::upload())
            {
                return false;
            }

            RendererD3D11* rendererD3D11 = static_cast<RendererD3D11*>(sharedEngine->getRenderer());

            // Blending state
            D3D11_BLEND_DESC blendStateDesc;
            blendStateDesc.AlphaToCoverageEnable = FALSE;
            blendStateDesc.IndependentBlendEnable = FALSE;

            D3D11_RENDER_TARGET_BLEND_DESC targetBlendDesc;
            targetBlendDesc.BlendEnable = uploadData.enableBlending ? TRUE : FALSE;
            targetBlendDesc.SrcBlend = getBlendFactor(uploadData.colorBlendSource);
            targetBlendDesc.DestBlend = getBlendFactor(uploadData.colorBlendDest);
            targetBlendDesc.BlendOp = getBlendOperation(uploadData.colorOperation);
            targetBlendDesc.SrcBlendAlpha = getBlendFactor(uploadData.alphaBlendSource);
            targetBlendDesc.DestBlendAlpha = getBlendFactor(uploadData.alphaBlendDest);
            targetBlendDesc.BlendOpAlpha = getBlendOperation(uploadData.alphaOperation);
            targetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

            blendStateDesc.RenderTarget[0] = targetBlendDesc;

            if (blendState) blendState->Release();

            HRESULT hr = rendererD3D11->getDevice()->CreateBlendState(&blendStateDesc, &blendState);
            if (FAILED(hr))
            {
                Log(Log::Level::ERR) << "Failed to create Direct3D 11 blend state";
                return false;
            }

            return true;
        }
    } // namespace graphics
} // namespace ouzel
