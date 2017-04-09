
#include "Player.hpp"
#include "Bullet.hpp"
# include "Game.hpp"

const int Player::c_shoot_ap = 70;

Player::Player() : AGameEntity(3, 25, -1, Player::c_shoot_ap){
}

Player::Player(Game * game) : AGameEntity(30, 25, -1, Player::c_shoot_ap), game(game){
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

void	Player::update(Enemy ***map, Game &game) {
	if (this->shoot_ap <= 0){
		this->shoot_ap = Player::c_shoot_ap;
		this->game->newBullet(this->x, this->y);
		this->shoot_ap = Player::c_shoot_ap;
	} else {
		this->shoot_ap--;
	}
	if (this->x > game.width){
		this->x = game.width - 2;
	}
	if (this->y > game.height){
		this->y = game.height - 2;
	}
	if (map[this->x][this->y]) {
		game.exit = true;
	}
}

void	Player::display(WINDOW * win){
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	mvwaddch(win, this->y, this->x, '>');
	attroff(COLOR_PAIR(1));
}

void	Player::move(int key){
	int max_x, max_y;


	max_x = this->game->width;
	max_y = this->game->height;

	if (key == KEY_DOWN && this->y < max_y - 2){
		this->y++;
	} else if (key == KEY_UP && this->y > 1){
		this->y--;
	} else if (key == KEY_LEFT && this->x > 1){
		this->x--;
	}else if (key == KEY_RIGHT && this->x < max_x - 2){
		this->x++;
	}
}
