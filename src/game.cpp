#include "game.hpp"

//////////////
// Includes //
#include "texablerender.hpp"
#include "collidable.hpp"
#include "texableset.hpp"
#include "tilemap.hpp"
#include "player.hpp"

//////////
// Code //

// Registering a static object at a given position with a render.
void registerBlock(Game* game,
                   std::string entityName,
                   TRType type, std::string texableName, std::string shaderName,
                   float x, float y, float w, float h) {
    game->addEntity(entityName);
    game->getEntity(entityName).addComponent(new TexableRender(type, texableName, shaderName, x, y, w, h));
}

// Registering a static object at a given position with a render, a position,
// and a collision box.
void registerBlockCollidable(Game* game,
                             std::string entityName,
                             TRType type, std::string texableName, std::string shaderName,
                             float x, float y, float w, float h) {
    registerBlock(game, entityName, type, texableName, shaderName, x, y, w, h);

    game->getEntity(entityName).addComponent(new clibgame::CPosition(x, y, w, h, true));
}

// Constructing a new game.
Game::Game() {
    addEntity("player");
    getEntity("player").addComponent(new clibgame::CPosition(64, 64, 64, 128, true));
    getEntity("player").addComponent(new PlayerController(800, 12, 5, 0, 0));
    getEntity("player").addComponent(new Collidable());

    TexableSet* ts = new TexableSet("player_standing", "clibgame_position_player",
                                    64, 64, 64, 128);

    ts->addRender("player_standing", TR_TEXTURE, "player_standing", "testshader");
    ts->addRender("player_running", TR_ANIMATION, "player_running", "testshader");
    ts->addRender("player_jumping", TR_TEXTURE, "player_jumping", "testshader");

    getEntity("player").addComponent(ts);

    loadTileMap("tilemap", *this, "res/tilemap.txt");
 
    // Registering some extra stuff in the game world.

    registerBlock(this,
                  "background",
                  TR_TEXTURE, "blue_desert", "testshader",
                  0, 0, 1028, 1028);
}
