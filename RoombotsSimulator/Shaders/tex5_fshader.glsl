#version 330 core
uniform sampler2D tex;
in vec2 uv;
out vec3 color;

/*This vertex shader uses the 2D texture passed as uniform
and draws it five times over the whole model*/
void main(){
    color = texture(tex, 5*uv).rgb;
}
