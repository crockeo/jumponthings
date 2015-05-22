#include "renderer.hpp"

//////////////
// Includes //
#include <iostream>

#include "config.hpp"

//////////
// Code //

int callCount = 0;

// Performing a single Render.
void Renderer::render(Render render) const {
    // Binding the proper information.
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Buffering the coordinate info.
    GLfloat coordinates[render.coordinates.size()];
    for (int i = 0; i < render.coordinates.size(); i++)
        coordinates[i] = render.coordinates.at(i);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_DYNAMIC_DRAW);

    // Buffering the order info.
    GLuint order[render.order.size()];
    for (int i = 0; i < render.order.size(); i++)
        order[i] = render.order.at(i);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_DYNAMIC_DRAW);

    glUseProgram(render.shader->getShaderID());

    // Initializing the coordinates.
    GLint coordAttrib = glGetAttribLocation(render.shader->getShaderID(), "in_coordinates");

    glEnableVertexAttribArray(coordAttrib);
    glVertexAttribPointer(coordAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Initializing the texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render.texable->getTextureID());
    glUniform1i(glGetUniformLocation(render.shader->getShaderID(), "in_tex"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    callCount++;
}

// Rendering a single layer.
void Renderer::renderLayer(int layer) const {
    for (auto render: renders[layer])
        this->render(render);
}

// Creating a new, empty renderer.
Renderer::Renderer() {
    callCount = 0;
    clear();
}

// Clearing out the renderer.
Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

// Adding a render on a given layer.
void Renderer::addRender(int layer, Render render) throw(std::logic_error) {
    if (layer < 0 || layer >= Renderer::LAYERS)
        throw std::logic_error("Layer out of bounds.");

    renders[layer].push_back(render);
}

// Initializing the Renderer.
void Renderer::init(GLFWwindow* window, const clibgame::Res& res) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

// Rendering everything currently contained in this Renderer.
void Renderer::render() const {
    for (int i = LAYERS - 1; i >= 0; i--)
        renderLayer(i);
}

// Clearing the previous render.
void Renderer::clear() {
    if (callCount != 0 && DEBUG) {
        std::cout << "Render call count: " << callCount << std::endl;
        callCount = 0;
    }

    renders.clear();
    for (int i = 0; i < Renderer::LAYERS; i++)
        renders.push_back(std::vector<Render>());
}
