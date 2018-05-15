/*
 * D3D11RenderSystem.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_D3D11_RENDER_SYSTEM_H
#define LLGL_D3D11_RENDER_SYSTEM_H


#include <LLGL/RenderSystem.h>
#include <LLGL/VideoAdapter.h>

#include "D3D11CommandQueue.h"
#include "D3D11CommandBuffer.h"
#include "D3D11RenderContext.h"

#include "Buffer/D3D11Buffer.h"
#include "Buffer/D3D11BufferArray.h"

#include "RenderState/D3D11GraphicsPipeline.h"
#include "RenderState/D3D11ComputePipeline.h"
#include "RenderState/D3D11StateManager.h"
#include "RenderState/D3D11Query.h"
#include "RenderState/D3D11Fence.h"

#include "Shader/D3D11Shader.h"
#include "Shader/D3D11ShaderProgram.h"

#include "Texture/D3D11Texture.h"
#include "Texture/D3D11TextureArray.h"
#include "Texture/D3D11Sampler.h"
#include "Texture/D3D11SamplerArray.h"
#include "Texture/D3D11RenderTarget.h"

#include "../ContainerTypes.h"
#include "../DXCommon/ComPtr.h"
#include <d3d11.h>
#include <dxgi.h>


namespace LLGL
{


class D3D11RenderSystem : public RenderSystem
{

    public:

        /* ----- Common ----- */

        D3D11RenderSystem();
        ~D3D11RenderSystem();

        /* ----- Render Context ------ */

        RenderContext* CreateRenderContext(const RenderContextDescriptor& desc, const std::shared_ptr<Surface>& surface = nullptr) override;

        void Release(RenderContext& renderContext) override;

        /* ----- Command queues ----- */

        CommandQueue* GetCommandQueue() override;

        /* ----- Command buffers ----- */

        CommandBuffer* CreateCommandBuffer() override;
        CommandBufferExt* CreateCommandBufferExt() override;

        void Release(CommandBuffer& commandBuffer) override;

        /* ----- Buffers ------ */

        Buffer* CreateBuffer(const BufferDescriptor& desc, const void* initialData = nullptr) override;
        BufferArray* CreateBufferArray(std::uint32_t numBuffers, Buffer* const * bufferArray) override;

        void Release(Buffer& buffer) override;
        void Release(BufferArray& bufferArray) override;

        void WriteBuffer(Buffer& buffer, const void* data, std::size_t dataSize, std::size_t offset) override;

        void* MapBuffer(Buffer& buffer, const BufferCPUAccess access) override;
        void UnmapBuffer(Buffer& buffer) override;

        /* ----- Textures ----- */

        Texture* CreateTexture(const TextureDescriptor& textureDesc, const ImageDescriptor* imageDesc = nullptr) override;
        TextureArray* CreateTextureArray(std::uint32_t numTextures, Texture* const * textureArray) override;

        void Release(Texture& texture) override;
        void Release(TextureArray& textureArray) override;

        void WriteTexture(Texture& texture, const SubTextureDescriptor& subTextureDesc, const ImageDescriptor& imageDesc) override;

        void ReadTexture(const Texture& texture, std::uint32_t mipLevel, ImageFormat imageFormat, DataType dataType, void* data, std::size_t dataSize) override;

        void GenerateMips(Texture& texture) override;
        void GenerateMips(Texture& texture, std::uint32_t baseMipLevel, std::uint32_t numMipLevels, std::uint32_t baseArrayLayer, std::uint32_t numArrayLayers) override;

        /* ----- Sampler States ---- */

        Sampler* CreateSampler(const SamplerDescriptor& desc) override;
        SamplerArray* CreateSamplerArray(std::uint32_t numSamplers, Sampler* const * samplerArray) override;

        void Release(Sampler& sampler) override;
        void Release(SamplerArray& samplerArray) override;

        /* ----- Render Targets ----- */

        RenderTarget* CreateRenderTarget(const RenderTargetDescriptor& desc) override;

        void Release(RenderTarget& renderTarget) override;

        /* ----- Shader ----- */

        Shader* CreateShader(const ShaderType type) override;
        ShaderProgram* CreateShaderProgram() override;

        void Release(Shader& shader) override;
        void Release(ShaderProgram& shaderProgram) override;

        /* ----- Pipeline States ----- */

        GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor& desc) override;
        ComputePipeline* CreateComputePipeline(const ComputePipelineDescriptor& desc) override;

        void Release(GraphicsPipeline& graphicsPipeline) override;
        void Release(ComputePipeline& computePipeline) override;

        /* ----- Queries ----- */

        Query* CreateQuery(const QueryDescriptor& desc) override;

        void Release(Query& query) override;

        /* ----- Fences ----- */

        Fence* CreateFence() override;

        void Release(Fence& fence) override;

        /* ----- Extended internal functions ----- */

        inline D3D_FEATURE_LEVEL GetFeatureLevel() const
        {
            return featureLevel_;
        }

        inline ID3D11Device* GetDevice() const
        {
            return device_.Get();
        }

    private:

        void CreateFactory();
        void QueryVideoAdapters();
        void CreateDevice(IDXGIAdapter* adapter);
        bool CreateDeviceWithFlags(IDXGIAdapter* adapter, const std::vector<D3D_FEATURE_LEVEL>& featureLevels, UINT flags, HRESULT& hr);
        void CreateStateManagerAndCommandQueue();

        void QueryRendererInfo();
        void QueryRenderingCaps();

        void BuildGenericTexture1D(D3D11Texture& textureD3D, const TextureDescriptor& desc, const ImageDescriptor* imageDesc);
        void BuildGenericTexture2D(D3D11Texture& textureD3D, const TextureDescriptor& desc, const ImageDescriptor* imageDesc);
        void BuildGenericTexture3D(D3D11Texture& textureD3D, const TextureDescriptor& desc, const ImageDescriptor* imageDesc);
        void BuildGenericTexture2DMS(D3D11Texture& textureD3D, const TextureDescriptor& desc);

        void UpdateGenericTexture(
            Texture& texture, std::uint32_t mipLevel, std::uint32_t layer,
            const Offset3D& offset, const Extent3D& extent,
            const ImageDescriptor& imageDesc
        );

        void InitializeGpuTexture(
            D3D11Texture& textureD3D, const TextureFormat format, const ImageDescriptor* imageDesc,
            std::uint32_t width, std::uint32_t height, std::uint32_t depth, std::uint32_t numLayers
        );

        void InitializeGpuTextureWithImage(
            D3D11Texture& textureD3D, const TextureFormat format, ImageDescriptor imageDesc,
            std::uint32_t width, std::uint32_t height, std::uint32_t depth, std::uint32_t numLayers
        );

        void InitializeGpuTextureWithDefault(
            D3D11Texture& textureD3D, const TextureFormat format,
            std::uint32_t width, std::uint32_t height, std::uint32_t depth, std::uint32_t numLayers
        );

        /* ----- Common objects ----- */

        ComPtr<IDXGIFactory>                        factory_;
        ComPtr<ID3D11Device>                        device_;
        ComPtr<ID3D11DeviceContext>                 context_;
        D3D_FEATURE_LEVEL                           featureLevel_ = D3D_FEATURE_LEVEL_9_1;

        std::unique_ptr<D3D11StateManager>          stateMngr_;

        /* ----- Hardware object containers ----- */

        HWObjectContainer<D3D11RenderContext>       renderContexts_;
        HWObjectInstance<D3D11CommandQueue>         commandQueue_;
        HWObjectContainer<D3D11CommandBuffer>       commandBuffers_;
        HWObjectContainer<D3D11Buffer>              buffers_;
        HWObjectContainer<D3D11BufferArray>         bufferArrays_;
        HWObjectContainer<D3D11Texture>             textures_;
        HWObjectContainer<D3D11TextureArray>        textureArrays_;
        HWObjectContainer<D3D11Sampler>             samplers_;
        HWObjectContainer<D3D11SamplerArray>        samplerArrays_;
        HWObjectContainer<D3D11RenderTarget>        renderTargets_;
        HWObjectContainer<D3D11Shader>              shaders_;
        HWObjectContainer<D3D11ShaderProgram>       shaderPrograms_;
        HWObjectContainer<D3D11GraphicsPipeline>    graphicsPipelines_;
        HWObjectContainer<D3D11ComputePipeline>     computePipelines_;
        HWObjectContainer<D3D11Query>               queries_;
        HWObjectContainer<D3D11Fence>               fences_;

        /* ----- Other members ----- */

        std::vector<VideoAdapterDescriptor>         videoAdatperDescs_;

        BufferCPUAccess                             mappedBufferCPUAccess_  = BufferCPUAccess::ReadOnly;

};


} // /namespace LLGL


#endif



// ================================================================================
