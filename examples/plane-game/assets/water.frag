#version 410
precision mediump float;

in vec4 fragColor;
uniform float time;
uniform vec2 resolution;

out vec4 outColor;

void main() { 
	vec2 uv = gl_FragCoord.xy / resolution.xy;

	float t = 0.4 + cos(5.0 * time + 20.0 * uv.y)/20.0;
	vec3 color = vec3(0, t, 1.0);

	outColor = vec4(color, 1.0); 
}
