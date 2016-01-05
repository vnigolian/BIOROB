#version 330 core
uniform vec4 colorVec;

out vec4 color;

/*This fragment shader uses the color stored 
in the uniform colorVec to color all fragments
Note that colorVec is a vec4, the fourth 
coordinates being the alpha value*/
void main(){
	color = colorVec;
}
