#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform CameraBuffer {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
} cameraData;

layout(push_constant) uniform constants {
    vec4 data;
    mat4 renderMatrix;
} PushConstants;

void main() {
    mat4 transformMatrix = (cameraData.viewProj * PushConstants.renderMatrix);
    gl_Position = transformMatrix * vec4(inPosition, 1.0f);
    fragColor = inColor;
}