#version 330 core


in vec2 texCoord;



uniform sampler2D tex;


out vec4 fcolor;

void main(){


fcolor = texture(tex, texCoord);

//fcolor = vec4(1.0,0.0,0.0,1.0);

} 