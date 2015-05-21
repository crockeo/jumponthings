#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>
#include <exception>

//////////
// Code //

const static std::vector<GLuint> STANDARD_ORDER { 0, 1, 2, 2, 3, 0 };

// The information to represent a Render.
struct Render {
    std::vector<GLfloat> coordinates;
    std::vector<GLuint> order;

    clibgame::Texable* texable;
    clibgame::Shader* shader;
};

// The central renderer for this game.
class Renderer : public clibgame::Renderer {
private:
    std::vector<std::vector<Render>> renders;
    GLuint vao, vbo, ebo;

    // Performing a single Render.
    void render(Render) const;

    // Rendering a single layer.
    void renderLayer(int) const;

public:
    const static int LAYERS = 8;

    // Creating a new, empty renderer.
    Renderer();

    // Clearing out the renderer.
    ~Renderer();

    // Adding a render on a given layer.
    void addRender(int, Render) throw(std::logic_error);

    // Initializing the Renderer.
    virtual void init(GLFWwindow*, const clibgame::Res&) override;

    // Rendering everything currently contained in this Renderer.
    virtual void render() const override;

    // Clearing the previous render.
    virtual void clear() override;
};

#endif
