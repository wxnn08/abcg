#version 410

layout(location = 0) in vec2 inPosition;

uniform vec4 color;
uniform vec2 scale;
uniform vec2 translation;

out vec4 fragColor;

void main() {
	vec2 newPosition = inPosition * scale + translation;
	gl_Position = vec4(newPosition, 0, 1);
	fragColor = color;
}
