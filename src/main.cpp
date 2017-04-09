#include "Game.hpp"

int		main(){
	Game game;

	
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

	game.loop();
}
