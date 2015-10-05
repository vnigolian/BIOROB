#version 330 core
uniform sampler2D tex;
in vec2 uv;
out vec3 color;

void main(){
    //color = texture(tex, uv).rgb;
	color = vec3(0.7,0.0,0.0);
}
