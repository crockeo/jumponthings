#include "game.hpp"

//////////////
// Includes //
#include "texablerender.hpp"
#include "collidable.hpp"
#include "texableset.hpp"
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

    game->getEntity(entityName).addComponent(new clibgame::CPosition(x, y, w, h));
    game->getEntity(entityName).addComponent(new Collidable());
}

// Constructing a new game.
Game::Game() {
    addEntity("player");
    getEntity("player").addComponent(new clibgame::CPosition(0, 0, 128, 256));
    getEntity("player").addComponent(new PlayerController(1200, 6, 10, 0, 0));
    getEntity("player").addComponent(new Collidable());

    TexableSet* ts = new TexableSet("player_standing", "clibgame_position_player",
                                    0, 0, 128, 256);

    ts->addRender("player_standing", TR_TEXTURE, "player_standing", "testshader");
    ts->addRender("player_running", TR_ANIMATION, "player_running", "testshader");
    ts->addRender("player_jumping", TR_TEXTURE, "player_jumping", "testshader");

    getEntity("player").addComponent(ts);

 
    // Registering some extra stuff in the game world.
    registerBlockCollidable(this,
                            "rect",
                            TR_TEXTURE, "dirt", "testshader",
                            0, -10, 50, 490);

    registerBlockCollidable(this,
                            "rect2",
                            TR_TEXTURE, "dirt", "testshader",
                            300, 0, 128, 128);

    registerBlock(this,
                  "background",
                  TR_TEXTURE, "blue_desert", "testshader",
                  0, 0, 1028, 1028);
}
