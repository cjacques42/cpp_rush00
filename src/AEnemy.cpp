#include "AEnemy.hpp"
#include "Game.hpp"

const int AEnemy::c_move_ap = 25;

AEnemy::AEnemy() {

}

AEnemy::AEnemy(int x, int y) : AGameEntity(x, y, 40, 70), prev(this), next(this) {

}

AEnemy::AEnemy(int x, int y, AEnemy * first) : AGameEntity(x, y, 40, 70){
    this->next = first;
    this->prev = first->prev;
    first->prev = this;
    this->prev->next = this;
}


AEnemy::AEnemy(AEnemy const &src) {
    *this = src;
}

AEnemy& AEnemy::operator=(AEnemy const &src) {
    AGameEntity::operator=(src);
    return *this;
}

AEnemy::~AEnemy() {
    this->prev->next = this->next;
    this->next->prev = this->prev;
}

void    AEnemy::update(Game &game){
    if (this->getX() < 1) {
        game.destroyFirstAEnemy(this);
        delete this;
    }
}

void AEnemy::display(WINDOW * win) {

    attron(COLOR_PAIR(1));
    mvwaddch(win, this->y, this->x, '<');
    attroff(COLOR_PAIR(1));
}

void AEnemy::move(int key) {
    if (key == KEY_LEFT) {
        this->x--;
    }
}
