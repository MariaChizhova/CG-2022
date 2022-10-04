#version 330 core

in vec2 vert_pos;
out vec4 out_col;

uniform int iterations;
uniform float threshold;

void main() {
    float x0 = vert_pos.x;
    float y0 = vert_pos.y;
    float x = 0.0;
    float y = 0.0;
    for (int i = 0; i < iterations; i++) {
        float xtemp = x * x - y * y + x0;
        float ytemp = 2 * x * y + y0;
        x = xtemp;
        y = ytemp;
        if (x * x + y * y > threshold * threshold) {
            out_col = vec4(0.0, float(i) / iterations, 0.0, 1.0);
            break;
        }
    }
}