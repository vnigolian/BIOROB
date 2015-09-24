#version 330 core
uniform sampler2D tex;
in vec2 uv;
out vec3 color;

void main(){
    color = texture(tex, 5*uv).rgb;
	//color = vec3(0.0,0.0,1.0);
}
