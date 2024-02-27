//
// StackAllocator.h
// WraithEngine
//
// Created by Andre Rodrigues on 19/02/2024.
//

#pragma once

#include "Memory/AllocatorBase.h"

namespace Wraith {

class StackAllocator : public AllocatorBase {
public:
    explicit StackAllocator(uint32 sizeBytes) : AllocatorBase(sizeBytes), m_CurrentPos(m_Start) {}

    void* Alloc(uint64 sizeBytes, uint8 alignment) override;
    void Free(void* ptr) override;

    void Clear();

private:
    struct AllocationHeader
    {
#ifdef WR_CONFIG_DEBUG
        void* PrevAddress;
#endif

        uint8 Adjustment;
    };

#ifdef WR_CONFIG_DEBUG
    void* m_PrevPosition = nullptr;
#endif

    void* m_CurrentPos = nullptr;
};

} // Wraith
