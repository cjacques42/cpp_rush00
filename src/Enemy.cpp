#include "Enemy.hpp"

Enemy::Enemy() {

}

Enemy::Enemy(int x, int y) : AGameEntity(x, y, 60, 60) {

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

void Enemy::display(WINDOW * win) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvwaddch(win, this->y, this->x, '<');
    attroff(COLOR_PAIR(1));
}

void Enemy::move(int key) {
    (void)key;
    if (this->move_ap == 0) {
        this->move_ap = 60;
        this->x--;
    } else {
        this->move_ap--;
    }
}
