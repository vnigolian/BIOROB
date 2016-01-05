#version 330 core
uniform sampler2D tex;
in vec2 uv;
out vec3 color;

/*This vertex shader uses the 2D texture passed as uniform*/
void main(){
    color = texture(tex, uv).rgb;
}
