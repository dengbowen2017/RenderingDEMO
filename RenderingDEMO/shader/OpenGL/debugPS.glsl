#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 0) uniform sampler2D depthMap;

void main()
{             
    float depthValue = texture(depthMap, TexCoords).r;

    FragColor = vec4(vec3(depthValue), 1.0); // orthographic
    //FragColor = vec4(0.5);
}