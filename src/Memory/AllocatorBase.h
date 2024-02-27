//
// AllocatorBase.h
// WraithEngine
//
// Created by Andre Rodrigues on 19/02/2024.
//


#pragma once

namespace Wraith {

class AllocatorBase {
public:
    explicit AllocatorBase(uint64 sizeBytes);
    virtual ~AllocatorBase();

    virtual void* Alloc(uint64 sizeBytes, uint8 alignment = 4) = 0;
    virtual void Free(void* ptr) = 0;

    uint64 GetSize() const { return m_Size; }
    uint64 GetUsedMemory() const { return m_UsedMemory; }
    uint64 GetNumAllocations() const { return m_NumAllocations; }

protected:
    void* m_Start = nullptr;
    uint64 m_Size = 0;
    uint64 m_UsedMemory = 0;
    uint64 m_NumAllocations = 0;
};

} // Wraith
