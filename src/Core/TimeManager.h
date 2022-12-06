//
// TimeManager.h
// WraithEngine
//
// Created by Andre Rodrigues on 05/12/2022.
//

#pragma once

#include "Wraith/Singleton.h"
#include "Wraith/Time.h"

namespace Wraith {

    class TimeManager : public Singleton<TimeManager> {
    public:
        void Init();
        void Update();

        Time::Timestep GetTime() const;
        Time::Timestep GetDeltaTime() const;
        Time::Timestep GetFixedDeltaTime() const;

    private:
        Time::Timestep _time = 0.0;
        Time::Timestep _deltaTime = 0.0;
        Time::Timestep _fixedDeltaTime = 0.0;

        Time::Timestep _timeAccumulator = 0.0;
        Time::Timestamp _lastFrameTimestamp;
        Time::Timestamp _lastFixedFrameTimestamp;
    };

}
