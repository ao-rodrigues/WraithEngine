//
// MemoryCommon.h
// WraithEngine
//
// Created by Andre Rodrigues on 19/02/2024.
//

#pragma once

#include "Core/Core.h"

namespace Wraith::PointerMath
{
    inline void* AlignForward(void* address, uint8 alignment)
    {
        const uint8 mask = alignment - 1;
        WR_ASSERT_MSG((alignment & mask) == 0, "Alignment must be a power of 2!");

        return (address + mask) & ~mask;
    }

    inline uint8 GetAlignForwardAdjustment(const void* address, uint8 alignment)
    {
        const uint8 adjustment = alignment - (static_cast<uint8*>(address) & static_cast<uint8*>(alignment - 1));

        if (adjustment == alignment)
        {
            return 0;
        }
        return adjustment;
    }

    inline uint8 GetAlignForwardAdjustmentWithHeader(const void* address, uint8 alignment, uint8 headerSize)
    {
        uint8 adjustment = GetAlignForwardAdjustment(address, alignment);
        uint8 neededSpace = headerSize;

        if (adjustment < neededSpace)
        {
            neededSpace -= adjustment;
            adjustment += alignment * (neededSpace / alignment);

            if (neededSpace % alignment > 0)
            {
                adjustment += alignment;
            }
        }

        return adjustment;
    }
}
