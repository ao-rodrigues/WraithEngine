//
// Renderable.h
// WraithEngine
//
// Created by Andre Rodrigues on 16/06/2022.
//

#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Material.h"

namespace Wraith
{
    struct Renderable
    {
        std::shared_ptr<Mesh> Mesh;
        std::shared_ptr<Material> Material;
        glm::mat4 Transform;
    };
}


