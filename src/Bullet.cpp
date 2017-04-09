
#include "Bullet.hpp"
#include "Game.hpp"

int Bullet::bulletNb = 0;
const int Bullet::c_move_ap = 1;

Bullet::Bullet() : AGameEntity(0, 0, -1, -1) {
}

Bullet::Bullet(int x, int y, Bullet * first) : AGameEntity(x, y, Bullet::c_move_ap, -1) {
	this->next = first;
	this->prev = first->prev;
	first->prev = this;
	this->prev->next = this;
	Bullet::bulletNb++;
}

Bullet::Bullet(int x, int y) : AGameEntity(x, y, Bullet::c_move_ap, -1), next(this), prev(this) {
	Bullet::bulletNb++;
}


Bullet::Bullet(Bullet const &instance){
	*this = instance;
}

Bullet& Bullet::operator=(Bullet const &rhs){
	AGameEntity::operator=(rhs);
	return *this;
}

Bullet::~Bullet(){
	this->prev->next = this->next;
	this->next->prev = this->prev;
	Bullet::bulletNb--;
}

int	Bullet::getBulletNb(){
	return Bullet::bulletNb;
}

void	Bullet::update(Enemy ***map, Game &game){
	int max_x;

	if (this->move_ap <= 0){
		this->move_ap = Bullet::c_move_ap;
		this->move(KEY_RIGHT);
	} else {
		this->move_ap--;
	}
	max_x = game.width;
	if (this->getX() >= max_x - 1 || map[this->x][this->y]) {
		if (!(this->getX() >= max_x - 1) &&  map[this->x][this->y]) {
			game.destroyFirstEnemy(map[this->x][this->y]);
			game.score += 10;
			delete map[this->x][this->y];
			map[this->x][this->y] = NULL;
		}
		game.destroyFirstBullet(this);
		delete this;
	}
}

void	Bullet::display(WINDOW * win){
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	mvwaddch(win, this->y, this->x, '-');
	attroff(COLOR_PAIR(1));
}

void	Bullet::move(int key){
	if (key == KEY_RIGHT){
		this->x++;
	}
}
