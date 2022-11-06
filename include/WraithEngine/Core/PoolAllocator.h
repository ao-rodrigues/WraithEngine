//
// PoolAllocator.h
// WraithEngine
//
// Created by Andre Rodrigues on 06/11/2022.
//

#pragma once

#include "StackLinkedList.h"

namespace Wraith {

    template<typename T>
    class PoolAllocator {
    public:
        explicit PoolAllocator(size_t amount) : _chunkSize(sizeof(T)), _chunksPerBlock(amount) {}

        void Init() {
            _start = malloc(_chunkSize * _chunksPerBlock);

            for (int i = 0; i < _chunksPerBlock; i++) {
                size_t address = (size_t) _start + i * _chunkSize;
                _freeList.Push((typename StackLinkedList<T>::Node*) address);
            }
        }

        void Shutdown() {
            free(_start);
        }

        void* Allocate() {
            auto* freePosition = _freeList.Pop();
            return (void*)freePosition;
        }

        void Free(void* address) {
            _freeList.Push((typename StackLinkedList<T>::Node*)address);
        }

    private:
        StackLinkedList<T> _freeList;
        void* _start = nullptr;

        size_t _chunkSize;
        size_t _chunksPerBlock;
    };
}
