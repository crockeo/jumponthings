//////////////
// Includes //
#include <clibgame.hpp>
#include <exception>
#include <iostream>

#include "game.hpp"

//////////
// Code //

// Entry point.
int main(int argc, char** argv) {
    // Configuring the game.
    clibgame::EngineConfig cfg;

    cfg.title = "Jump On Things!!!";
    cfg.ups = 240;
    cfg.rps = 120;

    // Starting the game.
    try {
        Game game;
        clibgame::startEngine(cfg, game, "res/assetspec.txt");
    } catch (std::runtime_error& e) {
        std::cout << "Failed to start game: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
