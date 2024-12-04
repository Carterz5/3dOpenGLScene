#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float textureID;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;


void main()
{
    gl_Position = vec4(position, 1.0);
    v_Color = color;
    v_TexCoord = texCoord;
    v_TexIndex = textureID;
}

#shader fragment
#version 450 core

out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Textures[3];

void main()
{
    int index = int(v_TexIndex);
    
    if (index == 0){
        o_Color = v_Color;
    } else{
        o_Color = texture(u_Textures[index], v_TexCoord);
    }
  
}
