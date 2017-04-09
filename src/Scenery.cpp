
#include "Scenery.hpp"
#include "Game.hpp"


const int Scenery::c_move_ap = 10;

Scenery::Scenery()
{

}

Scenery::Scenery(int x, int y, int second_x, int second_y) :  AEnemy(x, y), second_x(second_x), second_y(second_y) {

}

Scenery::Scenery(int x, int y, int second_x, int second_y, AEnemy * first) : AEnemy(x, y, first), second_x(second_x), second_y(second_y) {

}


Scenery::Scenery(Scenery const &instance){
	*this = instance;
}

Scenery& Scenery::operator=(Scenery const &rhs)
{
	AEnemy::operator=(rhs);
	return *this;
}

Scenery::~Scenery()
{
	
}


bool	Scenery::isDestructible(){
	return false;
}

void	Scenery::display(WINDOW * win){
	int it_x = this->x > this->second_x ? -1 : 1;
	int it_y = this->y > this->second_y ? -1 : 1;

	for (int tmp_x = this->x; tmp_x != this->second_x; tmp_x += it_x){
		for (int tmp_y = this->y; tmp_y != this->second_y; tmp_y += it_y){
			mvwaddch(win, tmp_y, tmp_x, ACS_CKBOARD);
		}

	}
}
void	Scenery::move(int key){
    if (key == KEY_LEFT) {
        this->x--;
        this->second_x--;
    }
}
bool 	Scenery::collide(int x, int y){
	return (((x >= this->x && x < this->second_x) || ((x <= this->x && x > this->second_x))) && ((y >= this->y && y < this->second_y) || ((y <= this->y && y > this->second_y))));
}

void    Scenery::update(Game &game){
    if (this->move_ap <= 0) {
        this->move_ap = Scenery::c_move_ap;
        this->move(KEY_LEFT);
    } else {
        this->move_ap--;
    }
    AEnemy::update(game);
}
