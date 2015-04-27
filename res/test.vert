#version 330

in vec4 in_coordinates;
out vec2 pass_texCoords;

void main() {
    vec2 coords = in_coordinates.xy;

    coords.x /= 320;
    coords.x -= 1;

    coords.y /= 240;
    coords.y -= 1;

    pass_texCoords = in_coordinates.zw;
    gl_Position = vec4(coords, 0, 1);
}
