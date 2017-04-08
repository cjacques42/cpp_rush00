
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

Game::Game() : bullets(NULL), player(Player::Player(this)) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	this->player = Player(this);
	this->win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);
    wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
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
    return *this;
}

int 	Game::ft_min(int a, int b){
	return (a > b ? b : a);
}

int 	Game::ft_max(int a, int b){
	return (a > b ? a : b);
}

void	Game::update(){
	this->player.update();

	if(this->bullets){
		this->bullets->update();
		Bullet	* tmp = this->bullets->next;
		while(tmp != this->bullets){
			tmp->update();
			tmp = tmp->next;
		}
	}
}

void	Game::newBullet(int x, int y) {
	if (this->bullets != NULL){
		new  Bullet(x, y, this->bullets);
	} else {
		this->bullets = new Bullet(x, y);
	}
}


WINDOW *Game::actualize_window(WINDOW *old_win) {

	WINDOW	*win = newwin(this->ft_min(50, LINES - 2), COLS - 2 , this->ft_max((LINES - 52) / 2, 1), 1);

	delwin(old_win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	return win;
}

void	Game::display(){

	werase(this->win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	this->player.display(this->win);
	if(this->bullets){
		this->bullets->display(win);
		Bullet	* tmp = this->bullets->next;
		while(tmp != this->bullets){
			tmp->display(this->win);
			tmp = tmp->next;
		}
	}

	wrefresh(this->win);

}

void Game::loop() {
    bool	exit = false;
    std::clock_t start = std::clock();
	double		duration;
	int         fps = 1000 / Game::FPS;

    int ch;

    while(!exit) {
    	start = std::clock();
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			exit = true;
		} else if (ch == 410) {
			this->win = this->actualize_window(this->win);
		} else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT){
			this->player.move(ch);
		}
		this->update();
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
