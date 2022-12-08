//
// Renderable.h
// WraithEngine
//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Material.h"

namespace Wraith {

    struct Renderable {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        glm::mat4 transform;
    };
}


