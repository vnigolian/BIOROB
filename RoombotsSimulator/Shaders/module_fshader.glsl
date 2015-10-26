#version 330 core
uniform sampler2D tex;
uniform vec4 colorVec;

in vec2 uv;
out vec4 color;

void main(){
    //color = texture(tex, uv).rgb;
	//color = vec4(0.0,1.0,0.0,0.8);
	
	color = colorVec;
}
