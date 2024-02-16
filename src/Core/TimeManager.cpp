//
// TimeManager.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 05/12/2022.
//

#include "wrpch.h"

#include "TimeManager.h"

namespace Wraith
{
    static constexpr Time::Timestep k_FixedTimestep = 1.0 / 60.0;

    void TimeManager::Init()
    {
        m_LastFrameTimestamp = std::chrono::high_resolution_clock::now();
        m_LastFixedFrameTimestamp = std::chrono::high_resolution_clock::now();
    }

    void TimeManager::Update()
    {
        const Time::Timestamp currentTime = std::chrono::high_resolution_clock::now();
        const auto deltaDuration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
            currentTime - m_LastFrameTimestamp);
        m_DeltaTime = deltaDuration.count() / 1000.0;
        m_LastFrameTimestamp = currentTime;

        m_TimeAccumulator += m_DeltaTime;
        if (m_TimeAccumulator >= k_FixedTimestep)
        {
            const auto fixedDeltaDuration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                currentTime - m_LastFixedFrameTimestamp);
            m_FixedDeltaTime = fixedDeltaDuration.count() / 1000.0;
            m_LastFixedFrameTimestamp = currentTime;
            m_TimeAccumulator = 0.0;
        }

        m_Time += m_DeltaTime;
    }

    Time::Timestep TimeManager::GetTime() const
    {
        return m_Time;
    }

    Time::Timestep TimeManager::GetDeltaTime() const
    {
        return m_DeltaTime;
    }

    Time::Timestep TimeManager::GetFixedDeltaTime() const
    {
        return m_FixedDeltaTime;
    }


    Time::Timestep Time::GetTime()
    {
        return TimeManager::GetInstance().GetTime();
    }

    Time::Timestep Time::GetDeltaTime()
    {
        return TimeManager::GetInstance().GetDeltaTime();
    }

    Time::Timestep Time::GetFixedDeltaTime()
    {
        return TimeManager::GetInstance().GetFixedDeltaTime();
    }
}
