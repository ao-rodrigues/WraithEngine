//
// FreeListAllocator.h
// WraithEngine
//
// Created by Andre Rodrigues on 27/02/2024.
//


#pragma once
#include "Memory/AllocatorBase.h"

namespace Wraith
{

class FreeListAllocator : public AllocatorBase
{
public:
    explicit FreeListAllocator(uint64 sizeBytes);
    ~FreeListAllocator();

    void* Alloc(uint64 sizeBytes, uint8 alignment) override;
    void Free(void* address) override;

private:
    struct AllocationHeader
    {
        uint64 Size = 0;
        uint8 Adjustment = 0;
    };

    struct FreeBlock
    {
        uint64 Size = 0;
        FreeBlock* Next = nullptr;
    };

    FreeBlock* m_FreeBlocks = nullptr;
};

} // Wraith
