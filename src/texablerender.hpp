#ifndef _TEXABLE_RENDER_HPP_
#define _TEXABLE_RENDER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>

//////////
// Code //

// TRType is an enum to distinctly represent the quantized states of the type of
// a TexableRender.
enum TRType {
    TR_SPRITESHEET,
    TR_ANIMATION,
    TR_TEXTURE
};

// TexableRender is a renderer for any given texable.
class TexableRender : public clibgame::Component,
                      public clibgame::Listener {
private:
    const TRType trType;
    const std::string texablePath, shaderPath, eventPath;
    float x, y, w, h;
    bool flipx, flipy;

    clibgame::Texable* texable;
    clibgame::Shader* shader;
    GLuint vao, vbo, ebo;

    // Generating the set of coordinates for this TexableRender given certain
    // specifications of x, y, width, and height.
    std::vector<GLfloat> generateCoordinates(float, float, float, float) const;

    // Filling the coordinates with the information as described by the indices.
    void fillCoordinates() const;

public:
    // Creating a new TexableRender given a TRType, a name of a texable
    // resource, and a shader resource. It also takes the name of an event
    // source to listen to for clibgame::CPositionEvents.
    TexableRender(TRType, std::string, std::string, std::string,
                  float, float, float, float);

    // Creating a new TexableRender given a TRType, a name of a texable
    // resource, and a shader resource.
    TexableRender(TRType, std::string, std::string,
                  float, float, float, float);

    // Destroying this TexableRender and all of its assets.
    ~TexableRender();

    // Removing the copy constructor & assignment operator.
    TexableRender(const TexableRender&) = delete;
    TexableRender& operator=(const TexableRender&) = delete;

    // Attempting to flip the X or Y axis. If done, the engine will assume that
    // the texture coordinates are in the shape of a rectangle in the order:
    // bottom left, bottom right, top right, top left.
    void setFlip(bool, bool);

    // Getting the name of this component.
    virtual std::string getName() const override;

    // Initializing this TexableRender.
    virtual void init(GLFWwindow*, const clibgame::ECP&, const clibgame::Res&) override;

    // Rendering this TexableRender.
    virtual void render() const override;

    // Being alerted to a given event.
    virtual void alert(const clibgame::Event&&) override;
};

#endif
