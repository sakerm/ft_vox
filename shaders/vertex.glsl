#version 400

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 positions;
layout(location = 2) in uint which;

out vec3 textureDir;

uniform mat4 MVP;

flat out uint texturess;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace + positions, 1);
	textureDir = vertexPosition_modelspace;
	texturess = which;
}