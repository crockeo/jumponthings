#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>
#include <exception>

//////////
// Code //

// An interface to define a type that can be rendered.
struct Renderable { virtual void doRender() const = 0; };

// The central renderer for this game.
class Renderer : public clibgame::Renderer {
private:
    std::vector<std::vector<const Renderable*>> renderables;

    // Rendering a single layer.
    void renderLayer(int) const;

public:
    const static int LAYERS = 8;

    // Creating a new, empty renderer.
    Renderer();

    // Adding a render on a given layer.
    void addRender(int, const Renderable*) throw(std::logic_error);

    // Rendering everything currently contained in this Renderer.
    virtual void render() const override;

    // Clearing the previous render.
    virtual void clear() override;
};

#endif
