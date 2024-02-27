//
// StackAllocator.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 19/02/2024.
//

#include "wrpch.h"

#include "StackAllocator.h"

#include "Memory/MemoryCommon.h"

namespace Wraith {
    void* StackAllocator::Alloc(uint64 sizeBytes, uint8 alignment)
    {
        WR_ASSERT(sizeBytes > 0);

        const uint8 adjustment = PointerMath::GetAlignForwardAdjustmentWithHeader(m_CurrentPos, alignment, sizeof(AllocationHeader));
        if (m_UsedMemory + adjustment + sizeBytes > m_Size)
        {
            return nullptr;
        }

        const uintptr alignedAddress = reinterpret_cast<uintptr>(m_CurrentPos) + adjustment;
        const auto header = reinterpret_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
        header->Adjustment = adjustment;

#ifdef WR_CONFIG_DEBUG
        header->PrevAddress = m_PrevPosition;
        m_PrevPosition = reinterpret_cast<void*>(alignedAddress);
#endif

        m_CurrentPos = reinterpret_cast<void*>(alignedAddress + sizeBytes);
        m_UsedMemory += sizeBytes + adjustment;
        m_NumAllocations++;

        return reinterpret_cast<void*>(alignedAddress);
    }

    void StackAllocator::Free(void* address)
    {
        WR_ASSERT(address == m_PrevPosition);
        const auto addr = reinterpret_cast<uintptr>(address);

        const auto header = reinterpret_cast<AllocationHeader*>(addr - sizeof(AllocationHeader));
        m_UsedMemory -= reinterpret_cast<uintptr>(m_CurrentPos) - addr + header->Adjustment;
        m_CurrentPos = reinterpret_cast<void*>(addr - header->Adjustment);

#ifdef WR_CONFIG_DEBUG
        m_PrevPosition = header->PrevAddress;
#endif

        m_NumAllocations--;
    }

    void StackAllocator::Clear()
    {
#ifdef WR_CONFIG_DEBUG
        m_PrevPosition = m_CurrentPos;
#endif
        m_CurrentPos = m_Start;
        m_UsedMemory = 0;
        m_NumAllocations = 0;
    }
} // Wraith