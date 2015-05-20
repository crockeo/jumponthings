#include "texablerender.hpp"

//////////
// Code //

// Generating the set of coordinates for this TexableRender given certain
// specifications of x, y, width, and height.
std::vector<GLfloat> TexableRender::generateCoordinates(float x, float y, float w, float h) const {
    std::vector<GLfloat> tempTexCoords = texable->getTextureCoords();
    std::vector<GLfloat> texCoords;

    if (flipx || flipy) {
        float x, y, ax, ay;

        if (flipx && flipy) {
            x  = tempTexCoords.at(2);
            y  = tempTexCoords.at(5);
            ax = tempTexCoords.at(0);
            ay = tempTexCoords.at(1);
        } else if (flipx) {
            x  = tempTexCoords.at(2);
            y  = tempTexCoords.at(1);
            ax = tempTexCoords.at(0);
            ay = tempTexCoords.at(5);
        } else {
            x  = tempTexCoords.at(0);
            y  = tempTexCoords.at(5);
            ax = tempTexCoords.at(2);
            ay = tempTexCoords.at(1);
        }

        std::vector<GLfloat> evenTemperTexCoords {
            x , y ,
            ax, y ,
            ax, ay,
            x , ay
        };

        texCoords = evenTemperTexCoords;
    } else
        texCoords = tempTexCoords;

    std::vector<GLfloat> realCoords = {
        x    , y    ,
        x + w, y    ,
        x + w, y + h,
        x    , y + h
    };

    if (texCoords.size() == 0)
        return realCoords;

    std::vector<GLfloat> coords;
    for (int i = 0; i < realCoords.size(); i += 2) {
        coords.push_back(realCoords.at(i                       ));
        coords.push_back(realCoords.at(i + 1                   ));
        coords.push_back( texCoords.at(i     % texCoords.size()));
        coords.push_back( texCoords.at(i + 1 % texCoords.size()));
    }

    return coords;
}

// Filling the coordinates with the information as described by the indices.
void TexableRender::fillCoordinates() const {
    std::vector<GLfloat> coords = generateCoordinates(x, y, w, h);

    GLfloat aCoords[coords.size()];
    for (int i = 0; i < coords.size(); i++)
        aCoords[i] = coords.at(i);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aCoords), aCoords, GL_DYNAMIC_DRAW);
}

// Creating a new TexableRender given a TRType, a name of a texable
// resource, and a shader resource. It also takes the name of an event
// source to listen to for clibgame::CPositionEvents.
TexableRender::TexableRender(TRType trType, std::string texablePath, std::string shaderPath, std::string eventPath,
                             float x, float y, float w, float h) :
        trType(trType),
        texablePath(texablePath),
        shaderPath(shaderPath),
        eventPath(eventPath) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    flipx = false;
    flipy = false;

    if (eventPath != "")
        clibgame::ListenerManager::instance().registerListener(this, eventPath);
}

// Creating a new TexableRender given a TRType, a name of a texable
// resource, and a shader resource.
TexableRender::TexableRender(TRType trType, std::string texablePath, std::string shaderPath,
                             float x, float y, float w, float h):
        TexableRender(trType, texablePath, shaderPath, "",
                      x, y, w, h) { }

// Destroying this TexableRender and all of its assets.
TexableRender::~TexableRender() {
    delete texable;
    delete shader;

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

// Attempting to flip the X or Y axis. If done, the engine will assume that
// the texture coordinates are in the shape of a rectangle in the order:
// bottom left, bottom right, top right, top left.
void TexableRender::setFlip(bool flipx, bool flipy) {
    this->flipx = flipx;
    this->flipy = flipy;
}

// Getting the name of this component.
std::string TexableRender::getName() const { return "texableRender"; }

// Initializing this TexableRender.
void TexableRender::init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
    // Setting up the texable.
    switch (trType) {
    case TR_SPRITESHEET:
        texable = new clibgame::TexSheet(res.getTexSheet(texablePath));
        break;
    case TR_ANIMATION:
        texable = new clibgame::Animation(res.getAnimation(texablePath));
        break;
    case TR_TEXTURE:
        texable = new clibgame::Texture(res.getTexture(texablePath));
        break;
    }

    // Setting up the shader.
    shader = new clibgame::Shader(res.getShader(shaderPath));

    // Setting up the VAO & VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Filling the EBO.
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GLuint order[] = { 0, 1, 2, 2, 3, 0 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);
}

// Rendering this TexableRender.
void TexableRender::doRender() const {
    fillCoordinates();

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

    glUseProgram(this->shader->getShaderID());

    // Initializing the coordinates.
    GLint coordAttrib = glGetAttribLocation(this->shader->getShaderID(), "in_coordinates");

    glEnableVertexAttribArray(coordAttrib);
    glVertexAttribPointer(coordAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Initializing the texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texable->getTextureID());
    glUniform1i(glGetUniformLocation(this->shader->getShaderID(), "in_tex"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Rendering this TexableRender.
void TexableRender::render(clibgame::Renderer& cRenderer) const {
    Renderer& renderer = dynamic_cast<Renderer&>(cRenderer);
    renderer.addRender(0, this);
}

// Being alerted to a given event.
void TexableRender::alert(const clibgame::Event&& e) {
    if (e.getEventType() == eventPath) {
        const clibgame::CPositionEvent&& pos = dynamic_cast<const clibgame::CPositionEvent&&>(e);

        x = pos.x;
        y = pos.y;
        w = pos.w;
        h = pos.h;
    }
}
