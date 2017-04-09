
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <iostream>

Game::Game() : exit(false), map(NULL), enemies(NULL), bullets(NULL), interval(800), player(Player::Player(this)) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	curs_set(0);

	this->width = COLS - 2;
	this->height = this->ft_min(50, LINES - 2);
	this->map = new Enemy**[this->width];
	for (int i = 0; i < this->width; i++) {
		this->map[i] = new Enemy*[this->height];
		for (int j = 0; j < this->height; j++) {
			this->map[i][j] = NULL;
		}
	}
	this->win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);
	wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
	srand((unsigned int)time(NULL));
}


Game::Game(Game const &src) {
	*this = src;
}

Game::~Game() {
	Enemy *tmp;
	Bullet *ptr;
	while (this->enemies) {
		tmp = this->enemies;
		this->destroyFirstEnemy(tmp);
        delete tmp;
	}
	while (this->bullets) {
		ptr = this->bullets;
		this->destroyFirstBullet(ptr);
        delete ptr;
	}
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

void	Game::update(){
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			this->map[i][j] = NULL;
		}
	}

	if(this->enemies){
		this->enemies->update(this->map, *this);
		if (this->enemies){
			Enemy	* tmp = this->enemies->next;
			while(tmp != this->enemies){
				tmp->update(this->map, *this);
				tmp = tmp->next;
			}
		}
	}
	this->player.update(this->map, *this);
	if(this->bullets){
		this->bullets->update(this->map, *this);
		if (this->bullets){
			Bullet	* tmp = this->bullets->next;
			while(tmp != this->bullets){
				tmp->update(this->map, *this);
				tmp = tmp->next;
			}
		}

	}
}

void	Game::newBullet(int x, int y) {
	if (x < this->width && y < this->height){
		if (this->bullets != NULL){
			new  Bullet(x, y, this->bullets);
		} else {
			this->bullets = new Bullet(x, y);
		}
	}
}


WINDOW *Game::actualize_window(WINDOW *old_win) {
	this->width = COLS - 2;
	this->height = this->ft_min(50, LINES - 2);
	this->map = new Enemy**[this->width];
	for (int i = 0; i < this->width; i++) {
		this->map[i] = new Enemy*[this->height];
		for (int j = 0; j < this->height; j++) {
			this->map[i][j] = NULL;
		}
	}
	WINDOW	*win = newwin(this->height, this->width, this->ft_max((LINES - 52) / 2, 1), 1);

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
	if(this->enemies){
		this->enemies->display(win);
		Enemy	* tmp = this->enemies->next;
		while(tmp != this->enemies){
			tmp->display(this->win);
			tmp = tmp->next;
		}
	}

	wrefresh(this->win);

}

void    Game::destroyFirstBullet(Bullet *toDel) {
	if (this->bullets == toDel) {
		this->bullets = toDel->prev;
		if (this->bullets == toDel)
			this->bullets = NULL;
	}
}

void    Game::destroyFirstEnemy(Enemy *toDel) {
	if (this->enemies == toDel) {
		this->enemies = toDel->prev;
		if (this->enemies == toDel)
			this->enemies = NULL;
	}
}

void Game::loop() {
	std::clock_t start = std::clock();
	double		duration;
	int         fps = 1000 / Game::FPS;
	int			i = 0;

	int ch;
	while(!this->exit) {
		start = std::clock();
		ch = getch();

		if (ch == 4 || ch == 3 || ch == 27){
			this->exit = true;
		} else if (ch == 410) {
			this->win = this->actualize_window(this->win);
		} else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT){
			this->player.move(ch);
		}
		this->update();
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
		line = (rand() % (this->height - 2)) + 1;
		col = this->width - 2;

		if (this->enemies != NULL){
			new Enemy(col, line, this->enemies);
		} else {
			this->enemies = new Enemy(col, line);
		}
	}
}
