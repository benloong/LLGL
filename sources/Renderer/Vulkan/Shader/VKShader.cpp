/*
 * VKShader.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "VKShader.h"
#include "../VKCore.h"
#include "../VKTypes.h"
#include <LLGL/Strings.h>

#ifdef LLGL_ENABLE_SPIRV_REFLECT
#   include "../../SPIRV/SPIRVReflect.h"
#endif


namespace LLGL
{


VKShader::VKShader(const VKPtr<VkDevice>& device, const ShaderType type) :
    Shader        { type                          },
    device_       { device                        },
    shaderModule_ { device, vkDestroyShaderModule }
{
}

bool VKShader::Compile(const std::string& sourceCode, const ShaderDescriptor& shaderDesc)
{
    return false; // dummy
}


bool VKShader::LoadBinary(std::vector<char>&& binaryCode, const ShaderDescriptor& shaderDesc)
{
    #ifdef LLGL_ENABLE_SPIRV_REFLECT

    /* Reflect SPIR-V shader module */
    errorLog_.clear();

    try
    {
        /* Parse shader module */
        SPIRVReflect reflect;
        reflect.Parse(binaryCode.data(), binaryCode.size());

        /* Store reflection data */
        //TODO...
    }
    catch (const std::exception& e)
    {
        errorLog_ = e.what();
        loadBinaryResult_ = LoadBinaryResult::ReflectFailed;
        return false;
    }

    #else

    /* Validate code size */
    if (binaryCode.empty() || binaryCode.size() % 4 != 0)
    {
        loadBinaryResult_ = LoadBinaryResult::InvalidCodeSize;
        return false;
    }

    #endif

    /* Store shader entry point (by default "main" for GLSL) */
    if (shaderDesc.entryPoint.empty())
        entryPoint_ = "main";
    else
        entryPoint_ = shaderDesc.entryPoint;

    /* Create shader module */
    VkShaderModuleCreateInfo createInfo;
    {
        createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.pNext    = nullptr;
        createInfo.flags    = 0;
        createInfo.codeSize = binaryCode.size();
        createInfo.pCode    = reinterpret_cast<const std::uint32_t*>(binaryCode.data());
    }
    auto result = vkCreateShaderModule(device_, &createInfo, nullptr, shaderModule_.ReleaseAndGetAddressOf());
    VKThrowIfFailed(result, "failed to create Vulkan shader module");

    loadBinaryResult_ = LoadBinaryResult::Successful;

    return true;
}

std::string VKShader::Disassemble(int flags)
{
    return ""; // dummy
}

std::string VKShader::QueryInfoLog()
{
    std::string s;

    switch (loadBinaryResult_)
    {
        case LoadBinaryResult::Undefined:
            s += ToString(GetType());
            s += " shader: shader module is undefined";
            break;
        case LoadBinaryResult::InvalidCodeSize:
            s += ToString(GetType());
            s += " shader: shader module code size is not a multiple of four bytes";
            break;
        case LoadBinaryResult::ReflectFailed:
            s = errorLog_;
            break;
        default:
            break;
    }

    return s;
}

void VKShader::FillShaderStageCreateInfo(VkPipelineShaderStageCreateInfo& createInfo) const
{
    createInfo.sType                = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    createInfo.pNext                = nullptr;
    createInfo.flags                = 0;
    createInfo.stage                = VKTypes::Map(GetType());
    createInfo.module               = shaderModule_;
    createInfo.pName                = entryPoint_.c_str();
    createInfo.pSpecializationInfo  = nullptr;
}


} // /namespace LLGL



// ================================================================================
