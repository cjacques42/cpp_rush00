#include "Enemy.hpp"
#include "Game.hpp"

const int Enemy::c_move_ap = 30;
// const int Enemy::c_move_ap = 5;

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
    AGameEntity::operator=(src);
    return *this;
}

Enemy::~Enemy() {
    this->prev->next = this->next;
    this->next->prev = this->prev;
}

void    Enemy::update(Enemy ***map, Game &game){
    if (this->move_ap <= 0) {
        this->move_ap = Enemy::c_move_ap;
        this->move(KEY_LEFT);
    } else {
        this->move_ap--;
    }
    if (this->getX() < 1) {
        game.destroyFirstEnemy(this);
        delete this;
    } else
        map[this->x][this->y] = this;
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
