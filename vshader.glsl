#version 330 core


in vec2 vertexTexture;

in vec3 vertexPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



out vec2 texCoord;






void main()
{


       texCoord = vertexTexture;


    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}