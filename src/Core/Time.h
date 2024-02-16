//
// Time.h
// WraithEngine
//
// Created by Andre Rodrigues on 05/12/2022.
//

#pragma once

namespace Wraith::Time
{
    using Timestep = double;
    using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

    Timestep GetTime();
    Timestep GetDeltaTime();
    Timestep GetFixedDeltaTime();
}
