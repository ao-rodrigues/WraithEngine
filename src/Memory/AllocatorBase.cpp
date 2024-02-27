//
// AllocatorBase.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 19/02/2024.
//

#include "wrpch.h"

#include "AllocatorBase.h"

namespace Wraith {
    AllocatorBase::AllocatorBase(uint64 sizeBytes) : m_Size(sizeBytes)
    {
        WR_ASSERT(sizeBytes > 0);
        m_Start = malloc(sizeBytes);
    }

    AllocatorBase::~AllocatorBase()
    {
        WR_ASSERT(m_NumAllocations == 0 && m_UsedMemory == 0);
        free(m_Start);
    }
} // Wraith