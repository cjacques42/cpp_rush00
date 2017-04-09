
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <iostream>


Game::Game() : exit(false), enemies(NULL), bullets(NULL), score(0), life(3), interval(800), player(Player::Player(this)) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	curs_set(0);

	this->width = COLS - 2;
	this->height = this->ft_min(50, LINES - 2);
	this->win = newwin(ft_min(50, LINES - 2), COLS - 2 , ft_max((LINES - 52) / 2, 1), 1);
	wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
	srand((unsigned int)time(NULL));
}


Game::Game(Game const &src) {
	*this = src;
}

Game::~Game() {
	AEnemy *tmp;
	Bullet *ptr;
	while (this->enemies) {
		tmp = this->enemies;
		this->destroyFirstAEnemy(tmp);
        delete tmp;
	}
	while (this->bullets) {
		ptr = this->bullets;
		this->destroyFirstBullet(ptr);
        delete ptr;
	}
	endwin();
	std::cout << "GAME OVER" << std::endl;
	std::cout << "Score : " << this->score << std::endl;
	std::cout << "Timer : " << this->timer << std::endl;
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
	if(this->enemies){
		this->enemies->update(*this);
		if (this->enemies){
			AEnemy	* tmp = this->enemies->next;
			AEnemy	* tmp_tmp;
			while(tmp != this->enemies){
				tmp_tmp = tmp->next;
				tmp->update(*this);
				tmp = tmp_tmp;
			}
		}
	}
	this->player.update(*this);
	if(this->bullets){
		this->bullets->update(*this);
		if (this->bullets){
			Bullet	* tmp = this->bullets->next;
			Bullet	* tmp_tmp;
			while(tmp != this->bullets){
				tmp_tmp = tmp->next;
				tmp->update(*this);
				tmp = tmp_tmp;
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
	WINDOW	*win = newwin(this->height, this->width, this->ft_max((LINES - 52) / 2, 1), 1);

	delwin(old_win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	return win;
}

void	Game::display(){

	werase(this->win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
	mvprintw(LINES - 2, COLS - 30, "Score : %d", this->score);
	mvprintw(LINES - 2, COLS - 60, "Live : %d", this->life);
	mvprintw(LINES - 2, COLS - 90, "Time : %.5s", this->timer);
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
		AEnemy	* tmp = this->enemies->next;
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

void    Game::destroyFirstAEnemy(AEnemy *toDel) {
	if (this->enemies == toDel) {
		this->enemies = toDel->prev;
		if (this->enemies == toDel)
			this->enemies = NULL;
	}
}

void Game::loop() {
	std::clock_t start = std::clock();
	std::time_t t = std::time(NULL);
	double		duration;
	int         fps = 1000 / Game::FPS;
	int			i = 799;

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
			this->randomAEnemy(5);
			this->interval += (this->interval > 120) ? -1 : 0;
			i = 0;
		}
		this->display();
		std::time_t e = std::time(NULL) - t;
		sprintf(this->timer, "%.2ld:%.2ld", e / 60, e % 60);
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if (duration < fps) {
			usleep((fps - duration) * 1000);
		}
	}
}

WINDOW *Game::getWindow() const {
	return this->win;
}

void Game::randomAEnemy(int nbr) {
	int line;
	int col;
	int type;

	for (int i = 0; i < nbr; i++) {

		type = rand() % 2;
		line = (rand() % (this->height - 2)) + 1;
		col = this->width - 2;

		if (this->enemies != NULL){
			if (type == 0)
				new SmallShip(col, line, this->enemies);
			if (type == 1)
				new Scenery(col, line, col + (rand() % 10 + 1) , line + (rand() % 10 + 1) , this->enemies);
		} else {
			if (type == 0)
				this->enemies = new SmallShip(col, line);
			if (type == 1)
				this->enemies = new Scenery(col, line, col + (rand() % 10 + 1) , line + (rand() % 10 + 1) );
		}
	}
}
