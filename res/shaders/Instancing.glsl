#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform vec3 u_Offsets[400];

void main()
{
    vec3 offset = u_Offsets[gl_InstanceID];
    vec4 extendedOffset = vec4(offset, 0.0);
    gl_Position = u_MVP * (position + extendedOffset);
    v_TexCoord = texCoord;
}

#shader fragment
#version 450 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
