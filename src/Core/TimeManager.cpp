//
// TimeManager.cpp
// WraithEngine
//
// Created by Andre Rodrigues on 05/12/2022.
//

#include "wrpch.h"

#include "TimeManager.h"

namespace Wraith {

    static constexpr Time::Timestep FIXED_TIMESTEP = 1.0 / 60.0;

    void TimeManager::Init() {
        _lastFrameTimestamp = std::chrono::high_resolution_clock::now();
        _lastFixedFrameTimestamp = std::chrono::high_resolution_clock::now();
    }

    void TimeManager::Update() {
        Time::Timestamp currentTime = std::chrono::high_resolution_clock::now();
        auto deltaDuration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(currentTime - _lastFrameTimestamp);
        _deltaTime = deltaDuration.count() / 1000.0;
        _lastFrameTimestamp = currentTime;

        _timeAccumulator += _deltaTime;
        if (_timeAccumulator >= FIXED_TIMESTEP) {
            auto fixedDeltaDuration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(currentTime - _lastFixedFrameTimestamp);
            _fixedDeltaTime = fixedDeltaDuration.count() / 1000.0;
            _lastFixedFrameTimestamp = currentTime;
            _timeAccumulator = 0.0;
        }

        _time += _deltaTime;
    }

    Time::Timestep TimeManager::GetTime() const {
        return _time;
    }

    Time::Timestep TimeManager::GetDeltaTime() const {
        return _deltaTime;
    }

    Time::Timestep TimeManager::GetFixedDeltaTime() const {
        return _fixedDeltaTime;
    }


    Time::Timestep Time::GetTime() {
        return TimeManager::GetInstance().GetTime();
    }

    Time::Timestep Time::GetDeltaTime() {
        return TimeManager::GetInstance().GetDeltaTime();
    }

    Time::Timestep Time::GetFixedDeltaTime() {
        return TimeManager::GetInstance().GetFixedDeltaTime();
    }

}