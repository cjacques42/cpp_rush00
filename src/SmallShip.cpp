#include "SmallShip.hpp"


const int SmallShip::c_move_ap = 2;

SmallShip::SmallShip(){

}

SmallShip::SmallShip(int x, int y) :  AEnemy(x, y){

}
SmallShip::SmallShip(int x, int y, AEnemy * first) :  AEnemy(x, y, first){
}

SmallShip::SmallShip(SmallShip const &instance){
	*this = instance;
}
SmallShip& SmallShip::operator=(SmallShip const & instance){
	AEnemy::operator=(instance);
	return *this;
}

SmallShip::~SmallShip(){
}


bool	SmallShip::isDestructible(){
	return true;
}

void	SmallShip::display(WINDOW * win){

    attron(COLOR_PAIR(1));
    mvwaddch(win, this->y, this->x, '<');    
    attroff(COLOR_PAIR(1));
}

void	SmallShip::move(int key){
    if (key == KEY_LEFT) {
        this->x--;
    }
}
bool 	SmallShip::collide(int x, int y){
	return (x == this->x && y == this->y);
}

void    SmallShip::update(Game &game){
    if (this->move_ap <= 0) {
        this->move_ap = SmallShip::c_move_ap;
        this->move(KEY_LEFT);
    } else {
        this->move_ap--;
    }
    AEnemy::update(game);

}