#include "renderer.hpp"

//////////
// Code //

// Rendering a single layer.
void Renderer::renderLayer(int layer) const {
    for (auto renderable: renderables[layer])
        renderable->doRender();
}

// Creating a new, empty renderer.
Renderer::Renderer() { clear(); }

// Adding a render on a given layer.
void Renderer::addRender(int layer, const Renderable* renderable) throw(std::logic_error) {
    if (layer < 0 || layer >= Renderer::LAYERS)
        throw std::logic_error("Layer out of bounds.");

    renderables[layer].push_back(renderable);
}

// Rendering everything currently contained in this Renderer.
void Renderer::render() const {
    for (int i = LAYERS - 1; i >= 0; i--)
        renderLayer(i);
}

// Clearing the previous render.
void Renderer::clear() {
    renderables.clear();
    for (int i = 0; i < Renderer::LAYERS; i++)
        renderables.push_back(std::vector<const Renderable*>());
}
