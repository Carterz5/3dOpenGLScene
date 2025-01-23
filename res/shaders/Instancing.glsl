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

uniform float time; // Add this uniform for animation

void main()
{
    // Get the instance offset
    vec3 offset = u_Offsets[gl_InstanceID];
    
    // Wind parameters
    float windStrength = 0.05; // Adjust for stronger/weaker wind
    float windSpeed = 2.0; // Adjust for faster/slower wind
    float windFrequency = 1.0; // Adjust for more/less frequent waves
    
    // Create varied wind movement based on position
    float windOffset = offset.x * 0.5 + offset.z * 0.5; // Varies wind phase based on position
    
    // Calculate wind displacement
    float windDisplacement = sin(time * windSpeed + windOffset * windFrequency) * windStrength;
    
    // Apply more wind effect to the top of the grass (based on vertex Y position)
    float heightFactor = position.y / 0.1; // Assuming grass is 0.1 units tall
    vec3 windVector = vec3(windDisplacement, 0.0, windDisplacement) * heightFactor;
    
    // Calculate the world position for this instance
    vec3 instancePos = offset;
    
    // Calculate the direction to camera for this instance
    vec3 toCamera = normalize(cameraPosition - instancePos);
    
    // Calculate the right vector
    vec3 right = normalize(cross(vec3(0.0, 1.0, 0.0), toCamera));
    
    // Calculate final up vector
    vec3 up = vec3(0.0, 1.0, 0.0);
    
    // Build the billboard rotation matrix
    mat3 billboardRotation = mat3(
        right,          // X axis
        up,            // Y axis
        cross(right, up) // Z axis
    );
    
    // Transform the vertex position and add wind effect
    vec3 billboardPos = billboardRotation * position.xyz;
    vec3 windedPosition = billboardPos + billboardRotation * windVector;
    
    // Offset the position to instance location
    vec3 finalPosition = windedPosition + instancePos;
    
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
