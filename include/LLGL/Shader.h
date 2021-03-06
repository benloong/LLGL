/*
 * Shader.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_SHADER_H
#define LLGL_SHADER_H


#include "RenderSystemChild.h"
#include "ShaderFlags.h"


namespace LLGL
{


/**
\brief Shader interface.
\see RenderSystem::CreateShader
\todo Replace "Compile" and "LoadBinary" functions by moving the descriptor structure to "RenderSystem::CreateShader".
*/
class LLGL_EXPORT Shader : public RenderSystemChild
{

    public:

        /**
        \brief Compiles the specified shader source.
        \remarks The input source code must be one of the high level shading languages the respective renderer supports (e.g. GLSL or HLSL).
        \param[in] sourceCode Specifies the shader source code which is to be compiled.
        \param[in] shaderDesc Specifies the shader descriptor.
        \return True on success, otherwise "QueryInfoLog" can be used to query the reason for failure.
        \note Only supported with: Direct3D 11, Direct3D 12, OpenGL.
        \see QueryInfoLog
        \see ShaderDescriptor
        */
        virtual bool Compile(const std::string& sourceCode, const ShaderDescriptor& shaderDesc = {}) = 0;

        /**
        \brief Loads the specified binary code into the shader object.
        \param[in] binaryCode Binary shader code container.
        \param[in] shaderDesc Specifies the shader descriptor. Only the optional stream output format is used here.
        \return True on success, otherwise "QueryInfoLog" can be used to query the reason for failure.
        \note Only supported with: Direct3D 11, Direct3D 12, Vulkan.
        \see QueryInfoLog
        \see ShaderDescriptor
        */
        virtual bool LoadBinary(std::vector<char>&& binaryCode, const ShaderDescriptor& shaderDesc = {}) = 0;

        /**
        \brief Disassembles the previously compiled shader byte code.
        \param[in] flags Specifies optional disassemble flags. This can be a bitwise OR combination of the 'ShaderDisassembleFlags' enumeration entries. By default 0.
        \return Disassembled assembler code or an empty string if disassembling was not possible.
        \note Only supported with: Direct3D 11, Direct3D 12.
        */
        virtual std::string Disassemble(int flags = 0) = 0;

        //! Returns the information log after the shader compilation.
        virtual std::string QueryInfoLog() = 0;

        /**
        \brief Returns the shader stage bitmask for this shader object.
        \see StageFlags
        */
        long GetStageFlags() const;

        //! Returns the type of this shader.
        inline ShaderType GetType() const
        {
            return type_;
        }

    protected:

        Shader(const ShaderType type);

    private:

        ShaderType type_;

};


} // /namespace LLGL


#endif



// ================================================================================
