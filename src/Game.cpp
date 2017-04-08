#include "Game.hpp"

Game::Game() : interval(800), score(0), enemies(NULL), player(Player::Player()) {
	(void)this->score;
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	curs_set(0);
	this->player = Player();
	this->win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);
    wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
	srand((unsigned int)time(NULL));
}


Game::Game(Game const &src) {
	*this = src;
}

Game::~Game() {
    endwin();
}

Game& Game::operator=(Game const &src) {
    if (this != &src) {
    	this->player = src.player;
        this->win = src.getWindow();
    }
	srand((unsigned int)time(NULL));
    return *this;
}

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

void	Game::display(){

	this->player.display(this->win);
	wrefresh(this->win);

}

void Game::loop() {
    bool	exit = false;
    std::clock_t start = std::clock();
	double		duration;
	int         fps = 1000 / Game::FPS;
	int			i = 0;

    int ch;
    while(!exit) {
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			exit = true;
		} else if (ch == 410) {
			this->win = this->actualize_window(this->win);
		} else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT){
			this->player.move(ch);
		}
		if (this->interval == i++) {
			this->randomEnemy(3);
			this->interval += (this->interval > 120) ? -1 : 0;
			i = 0;
		}
		this->display();
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if (duration < fps) {
			usleep((fps - duration) * 1000);
		}
	}
}

WINDOW *Game::getWindow() const {
    return this->win;
}

void Game::randomEnemy(int nbr) {
	int line;
	int col;

	for (int i = 0; i < nbr; i++) {
		line = (rand() % 49) + 1;
		col = COLS - 4;

		Enemy *tmp;
		Enemy *prev = NULL;
		Enemy *enemy = new Enemy(col, line);
		if (this->enemies == NULL) {
			this->enemies = enemy;
		} else {
			tmp = this->enemies;
			while (this->enemies->next) {
				prev = tmp;
				tmp = tmp->next;
			}
			tmp->next = enemy;
			enemy->prev = prev;
		}
	}
}
