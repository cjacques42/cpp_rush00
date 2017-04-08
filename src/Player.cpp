
#include "Player.hpp"

Player::Player() : AGameEntity(3, 25, -1, 50){
}

Player::Player(Player const &instance){
	*this = instance;
}

Player& Player::operator=(Player const &rhs){
	AGameEntity::operator=(rhs);
	return *this;
}

Player::~Player(){
}

void	Player::display(WINDOW * win){
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	mvwaddch(win, this->x, this->y, '>');
	attroff(COLOR_PAIR(1));
}

void	Player::move(int key){
	if (key == KEY_DOWN){
		this->y--;
	} else if (key == KEY_UP){
		this->y++;
	} else if (key == KEY_LEFT){
		this->x--;
	}else if (key == KEY_RIGHT){
		this->x++;
	}
}
