#version 330 core
uniform mat4 MVP;

in vec3 vpoint;
in vec2 vtexcoord;
out vec2 uv;


void main(){
    gl_Position =  MVP * vec4(vpoint,1); 
	//gl_Position = vec4(vpoint,0.0f);
    uv = vtexcoord;
}