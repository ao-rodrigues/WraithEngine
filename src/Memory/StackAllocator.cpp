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

        void* alignedAddress = m_CurrentPos + adjustment;

        const auto header = static_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
        header->Adjustment = adjustment;

#ifdef WR_CONFIG_DEBUG
        header->PrevAddress = m_PrevPosition;
        m_PrevPosition = alignedAddress;
#endif

        m_CurrentPos = alignedAddress + sizeBytes;
        m_UsedMemory += sizeBytes + adjustment;
        m_NumAllocations++;

        return alignedAddress;
    }

    void StackAllocator::Free(void* ptr)
    {
        WR_ASSERT(ptr == m_PrevPosition);

        const auto header = static_cast<AllocationHeader*>(ptr - sizeof(AllocationHeader));
        m_UsedMemory -= m_CurrentPos - ptr + header->Adjustment;
        m_CurrentPos = ptr - header->Adjustment;

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