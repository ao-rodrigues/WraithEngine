//
// FreeListAllocator.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 27/02/2024.
//

#include "FreeListAllocator.h"

#include "Memory/MemoryCommon.h"

namespace Wraith {
    FreeListAllocator::FreeListAllocator(uint64 sizeBytes)
        : AllocatorBase(sizeBytes)
        , m_FreeBlocks(static_cast<FreeBlock*>(m_Start))
    {
        WR_ASSERT(sizeBytes > sizeof(FreeBlock))

        m_FreeBlocks->Size = sizeBytes;
        m_FreeBlocks->Next = nullptr;
    }

    FreeListAllocator::~FreeListAllocator()
    {
        m_FreeBlocks = nullptr;
    }

    void* FreeListAllocator::Alloc(uint64 sizeBytes, uint8 alignment)
    {
        FreeBlock* prevFreeBlock = nullptr;
        FreeBlock* freeBlock = m_FreeBlocks;

        while (freeBlock != nullptr)
        {
            const uint8 adjustment = PointerMath::GetAlignForwardAdjustmentWithHeader(freeBlock, alignment, sizeof(AllocationHeader));
            uint64 totalSize = sizeBytes + adjustment;

            if (freeBlock->Size < totalSize)
            {
                prevFreeBlock = freeBlock;
                freeBlock = freeBlock->Next;
                continue;
            }

            if (freeBlock->Size - totalSize <= sizeof(AllocationHeader))
            {
                totalSize = freeBlock->Size;

                if (prevFreeBlock != nullptr)
                {
                    prevFreeBlock->Next = freeBlock->Next;
                }
                else
                {
                    m_FreeBlocks = freeBlock->Next;
                }
            }
            else
            {
                FreeBlock* nextBlock = freeBlock + totalSize;

                nextBlock->Size = freeBlock->Size - totalSize;
                nextBlock->Next = freeBlock->Next;

                if (prevFreeBlock != nullptr)
                {
                    prevFreeBlock->Next = nextBlock;
                }
                else
                {
                    m_FreeBlocks = nextBlock;
                }
            }

            const uintptr alignedAddress = reinterpret_cast<uintptr>(freeBlock) + adjustment;
            auto header = reinterpret_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
            header->Size = totalSize;
            header->Adjustment = adjustment;

            m_UsedMemory += totalSize;
            m_NumAllocations++;

            return reinterpret_cast<void*>(alignedAddress);
        }
    }

    void FreeListAllocator::Free(void* address)
    {
    }
} // Wraith