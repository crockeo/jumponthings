#ifndef _TILE_MAP_HPP_
#define _TILE_MAP_HPP_

//////////////
// Includes //
#include <clibgame.hpp>
#include <fstream>

#include "texablerender.hpp"


//////////
// Code //

class BunchOfRenders : public clibgame::Component {
private:
    std::vector<TexableRender*> renders;

public:
    // A bunch of renders with a pre-defined set of TexableRenders.
    BunchOfRenders(std::vector<TexableRender*>);

    // A bunch of renders without a predefined set.
    BunchOfRenders();

    // Destroying this and the set of TexableRenders.
    ~BunchOfRenders();

    // Adding a new TexableRender.
    void addRender(TexableRender*);

    // Getting the name of this component.
    virtual std::string getName() const override;

    // Initializing all of the TexableRenders that exist within this BunchOfRenders.
    virtual void init(GLFWwindow*, const clibgame::ECP&, const clibgame::Res&) override;

    // Rendering this BunchOfRenders.
    virtual void render() const override;
};

// Loading a given tile map into the ECP using an ifstream.
void loadTileMap(std::string, clibgame::ECP&, std::istream&) throw(std::runtime_error);

// Loading a givne tile map into the ECP using a path to a file.
void loadTileMap(std::string, clibgame::ECP&, std::string) throw(std::runtime_error);

#endif
