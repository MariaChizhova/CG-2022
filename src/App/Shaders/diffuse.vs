#version 330 core

layout(location=0) in vec2 pos;

uniform float zoom;
uniform vec2 shift;

out vec2 vert_pos;

void main() {
    vert_pos = vec2((pos.x + shift.x) / zoom, (pos.y + shift.y)/ zoom);
	gl_Position = vec4(pos.xy, 0.0, 1.0);
}
