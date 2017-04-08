
#include "Player.hpp"
#include "Bullet.hpp"
# include "Game.hpp"

const int Player::c_shoot_ap = 20;

Player::Player() : AGameEntity(3, 25, -1, Player::c_shoot_ap){
}

Player::Player(Game * game) : AGameEntity(3, 25, -1, Player::c_shoot_ap), game(game){
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

void	Player::update() {
	if (this->shoot_ap <= 0){
		this->shoot_ap = Player::c_shoot_ap;
		this->game->newBullet(this->x, this->y);
		this->shoot_ap = Player::c_shoot_ap;
	} else {
		this->shoot_ap--;
	}
}

void	Player::display(WINDOW * win){
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	mvwaddch(win, this->y, this->x, '>');
	attroff(COLOR_PAIR(1));
}

void	Player::move(int key){
	if (key == KEY_DOWN){
		this->y++;
	} else if (key == KEY_UP){
		this->y--;
	} else if (key == KEY_LEFT){
		this->x--;
	}else if (key == KEY_RIGHT){
		this->x++;
	}
}
