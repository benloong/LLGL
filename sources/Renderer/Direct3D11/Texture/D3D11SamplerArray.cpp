/*
 * D3D11SamplerArray.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "D3D11SamplerArray.h"
#include "D3D11Sampler.h"
#include "../../../Core/Helper.h"


namespace LLGL
{


D3D11SamplerArray::D3D11SamplerArray(std::uint32_t numSamplers, Sampler* const * samplerArray)
{
    /* Store the pointer of each SRV inside the array */
    samplerStates_.reserve(numSamplers);
    while (auto next = NextArrayResource<D3D11Sampler>(numSamplers, samplerArray))
        samplerStates_.push_back(next->GetNative());
}


} // /namespace LLGL



// ================================================================================
