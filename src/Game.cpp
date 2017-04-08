#include "Game.hpp"

Game::Game() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	this->win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);
    wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
}

Game::Game(Game const &) {

}

Game::~Game() {
    endwin();
}

// Game& operator=(Game const &) {
//
// }

int 	Game::ft_min(int a, int b){
	return (a > b ? b : a);
}

int 	Game::ft_max(int a, int b){
	return (a > b ? a : b);
}


WINDOW *Game::actualize_window(WINDOW *old_win) {

	WINDOW	*win = newwin(this->ft_min(50, LINES - 2), COLS - 2 , this->ft_max((LINES - 52) / 2, 1), 1);

	delwin(old_win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	return win;
}

void Game::loop() {
    bool	exit = false;
    std::clock_t start = std::clock();
	double		duration;

    int ch;
	Player	p;
    while(!exit) {
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			exit = true;
		} else if (ch == 410) {
			this->win = actualize_window(this->win);
		} else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT){
			p.move(ch);
		}
		p.display(this->win);
		wrefresh(this->win);
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if (duration < FPS) {
			usleep((FPS - duration) * 1000);
		}
	}
}
