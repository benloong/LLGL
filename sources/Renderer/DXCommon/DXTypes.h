/*
 * DXTypes.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_DX_TYPES_H
#define LLGL_DX_TYPES_H


#include <LLGL/VertexAttribute.h>
#include <LLGL/RenderSystemFlags.h>
#include <LLGL/GraphicsPipelineFlags.h>
#include <LLGL/TextureFlags.h>
#include <LLGL/BufferFlags.h>
#include <dxgiformat.h>
#include <d3dcommon.h>


namespace LLGL
{

namespace DXTypes
{


[[noreturn]]
void MapFailed(const char* typeName, const char* dxTypeName);

[[noreturn]]
void UnmapFailed(const char* typeName, const char* dxTypeName);

[[noreturn]]
void ParamNotSupported(const char* paramName, const char* requirement);


DXGI_FORMAT             Map( const VectorType           vectorType    );
DXGI_FORMAT             Map( const DataType             dataType      );
DXGI_FORMAT             Map( const TextureFormat        textureFormat );
D3D_PRIMITIVE_TOPOLOGY  Map( const PrimitiveTopology    topology      );

TextureFormat           Unmap( const DXGI_FORMAT            format    );
StorageBufferType       Unmap( const D3D_SHADER_INPUT_TYPE  inputType );


} // /namespace DXTypes

} // /namespace LLGL


#endif



// ================================================================================
