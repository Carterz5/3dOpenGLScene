#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec3 u_Offsets[200];
uniform vec3 cameraPosition;


void main()
{
    // Get the instance offset
    vec3 offset = u_Offsets[gl_InstanceID];
    
    // Calculate the world position for this instance
    vec3 instancePos = offset; // Since model matrix is identity
    
    // Calculate the direction to camera for this instance
    vec3 toCamera = normalize(cameraPosition - instancePos);
    
    // Calculate the right vector (perpendicular to up and toCamera)
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), toCamera));
    
    // Calculate final up vector (ensures orthogonal basis)
    vec3 up = vec3(0.0, 1.0, 0.0);
    
    // Build the billboard rotation matrix
    mat3 billboardRotation = mat3(
        right,          // X axis
        up,            // Y axis
        cross(right, up) // Z axis
    );
    
    // Transform the vertex position
    vec3 billboardPos = billboardRotation * position.xyz;
    
    // Offset the position to instance location
    vec3 finalPosition = billboardPos + instancePos;
    
    // Final clip space position
    gl_Position = projectionMatrix * viewMatrix * vec4(finalPosition, 1.0);
    
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
