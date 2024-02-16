//
// DeletionQueue.h
// WraithEngine
//
// Created by Andre Rodrigues on 07/12/2022.
//

#pragma once

#include <deque>
#include <functional>

namespace Wraith
{
    struct DeletionQueue
    {
        void Push(std::function<void()>&& function)
        {
            Deletors.push_back(function);
        }

        void Flush()
        {
            for (auto& deletor : Deletors)
            {
                deletor();
            }
            Deletors.clear();
        }

        std::deque<std::function<void()>> Deletors;
    };
}
