#include "Enemy.hpp"

const int Enemy::c_move_ap = 40;

Enemy::Enemy() {

}

Enemy::Enemy(int x, int y) : AGameEntity(x, y, 40, 70), prev(this), next(this) {
}

Enemy::Enemy(int x, int y, Enemy * first) : AGameEntity(x, y, 40, 70){
    this->next = first;
    this->prev = first->prev;
    first->prev = this;
    this->prev->next = this;
}


Enemy::Enemy(Enemy const &src) {
    *this = src;
}

Enemy& Enemy::operator=(Enemy const &src) {
    if (this != &src) {
    	this->x = src.getX();
        this->y = src.getY();
        this->move_ap = src.getMoveAP();
        this->shoot_ap = src.getShootAP();
    }
    return *this;
}

Enemy::~Enemy() {

}

void    Enemy::update(){
    if (this->move_ap <= 0) {
        this->move_ap = Enemy::c_move_ap;
        this->move(KEY_LEFT);
    } else {
        this->move_ap--;
    }
}

void Enemy::display(WINDOW * win) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvwaddch(win, this->y, this->x, '<');
    attroff(COLOR_PAIR(1));
}

void Enemy::move(int key) {
    if (key == KEY_LEFT) {
        this->x--;
    }
}
