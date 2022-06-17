//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Core/VulkanBase.h"
#include "Graphics/Pipeline.h"

namespace Wraith {

    struct Material {
        std::shared_ptr<Pipeline> pipeline;
    };
}

