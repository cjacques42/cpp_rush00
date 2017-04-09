
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

Game::Game() : interval(800), player(Player::Player(this)), enemies(NULL), bullets(NULL) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);

	curs_set(0);


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
	if(this->enemies){
		this->enemies->display(win);
		Enemy	* tmp = this->enemies->next;
		while(tmp != this->enemies){
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

void    Game::colide() {
	Enemy * map[COLS][LINES];
	int max_x, max_y;
	int x, y;

	max_x = getmaxx(this->getWindow());
	max_y = getmaxy(this->getWindow());

	if(this->enemies){
		map[this->enemies->getX()][this->enemies->getY()] = this->enemies;
		Enemy *ptr = this->enemies->next;
		while(ptr != this->enemies){
			map[ptr->getX()][ptr->getY()] = ptr;
			ptr = ptr->next;
		}
	}
	if(this->bullets){
		x = this->bullets->getX();
		y = this->bullets->getY();
		if (x <= 1 || x >= max_x - 2 || y <= 1 || y >= max_y - 2 || map[x][y] != NULL) {
//			delete map[x][y];
			delete this->bullets;
		}
		Bullet	* tmp = this->bullets->next;
		while(tmp != this->bullets){
			x = tmp->getX();
			y = tmp->getY();
			if (x <= 1 || x >= max_x - 2 || y <= 1 || y >= max_y - 2 || map[x][y] != NULL) {
//				delete map[x][y];
//				delete tmp;
			}
			tmp = tmp->next;
		}
	}
}

void Game::loop() {
    bool	exit = false;
    std::clock_t start = std::clock();
	double		duration;
	int         fps = 1000 / Game::FPS;
	int			i = 0;

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
		if (this->interval == i++) {
			this->randomEnemy(3);
			this->interval += (this->interval > 120) ? -1 : 0;
			i = 0;
		}
		this->colide();
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
		line = (rand() % 48) + 2;
		col = COLS - 4;

		if (this->enemies){
//			new Enemy(col, line, enemies);
		} else {
//			this->enemies = new Enemy(col, line);
		}
	}
}
