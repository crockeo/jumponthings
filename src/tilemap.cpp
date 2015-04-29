#include "tilemap.hpp"

//////////////
// Includes //
#include "collidable.hpp"

//////////
// Code //

// A bunch of renders with a pre-defined set of TexableRenders.
BunchOfRenders::BunchOfRenders(std::vector<TexableRender*> renders) :
        renders(renders) { }

// A bunch of renders without a predefined set.
BunchOfRenders::BunchOfRenders() { }

// Destroying this and the set of TexableRenders.
BunchOfRenders::~BunchOfRenders() {
    for (TexableRender* tr: renders)
        delete tr;
}

// Adding a new TexableRender.
void BunchOfRenders::addRender(TexableRender* tr) { renders.push_back(tr); }

// Getting the name of this component.
std::string BunchOfRenders::getName() const { return "bunchOfRenders"; }

// Initializing all of the TexableRenders that exist within this BunchOfRenders.
void BunchOfRenders::init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
    for (TexableRender* tr: renders)
        tr->init(window, ecp, res);
}

// Rendering this BunchOfRenders.
void BunchOfRenders::render() const {
    for (TexableRender* tr: renders)
        tr->render();
}

// Loading a given tile map into the ECP using an ifstream.
void loadTileMap(std::string entityName, clibgame::ECP& ecp, std::istream& in) throw(std::runtime_error) {
    if (ecp.hasEntity(entityName))
        throw std::runtime_error("An entity by the name \"" + entityName + "\" already exists.");

    BunchOfRenders* bor = new BunchOfRenders();
    CollidableSet* cs = new CollidableSet();

    TRType renderType;
    std::string renderTypeStr,
                texablePath, shaderPath;
    float x, y,
          w, h;

    while (!in.eof()) {
        in >> renderTypeStr;
        in >> texablePath;
        in >> shaderPath;
        in >> x;
        in >> y;
        in >> w;
        in >> h;

             if (renderTypeStr == "animation"  ) renderType = TR_ANIMATION;
        else if (renderTypeStr == "texture"    ) renderType = TR_TEXTURE;
        else if (renderTypeStr == "spritesheet") renderType = TR_SPRITESHEET;

        bor->addRender(new TexableRender(renderType, texablePath, shaderPath,
                                         x, y, w, h));

        cs->addCollision(Rectangle(x, y, w, h));
    }

    ecp.addEntity(entityName);
    ecp.getEntity(entityName).addComponent(bor);
    ecp.getEntity(entityName).addComponent(cs);
}

// Loading a givne tile map into the ECP using a path to a file.
void loadTileMap(std::string entityName, clibgame::ECP& ecp, std::string path) throw(std::runtime_error) {
    std::ifstream in(path);
    if (!in.good())
        throw std::runtime_error("Failed to access tile map file on path \"" + path + "\".");

    loadTileMap(entityName, ecp, in);
}
