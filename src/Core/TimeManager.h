//
// TimeManager.h
// WraithEngine
//
// Created by Andre Rodrigues on 05/12/2022.
//

#pragma once

#include "Utils/Singleton.h"
#include "Core/Time.h"

namespace Wraith
{
    class TimeManager : public Singleton<TimeManager>
    {
    public:
        void Init();
        void Update();

        Time::Timestep GetTime() const;
        Time::Timestep GetDeltaTime() const;
        Time::Timestep GetFixedDeltaTime() const;

    private:
        Time::Timestep m_Time = 0.0;
        Time::Timestep m_DeltaTime = 0.0;
        Time::Timestep m_FixedDeltaTime = 0.0;

        Time::Timestep m_TimeAccumulator = 0.0;
        Time::Timestamp m_LastFrameTimestamp;
        Time::Timestamp m_LastFixedFrameTimestamp;
    };
}
