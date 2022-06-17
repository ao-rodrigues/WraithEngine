//
// Created by Andre Rodrigues on 17/06/2022.
//

#pragma once

class Mesh;
class Material;

namespace Wraith {

    struct TransformComponent {
        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform) : transform(transform) {}

        operator const glm::mat4&() const { return transform; }
        operator glm::mat4&() { return transform; }

        glm::mat4 transform;
    };

    struct RenderableComponent {
        RenderableComponent() = default;
        RenderableComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
            : mesh(mesh), material(material) {}

        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
    };
}
