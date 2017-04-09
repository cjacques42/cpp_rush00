
#include "Player.hpp"
#include "Bullet.hpp"
# include "Game.hpp"

const int Player::c_shoot_ap = 70;

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

void	Player::update(Game &game) {
	if (this->shoot_ap <= 0){
		this->shoot_ap = Player::c_shoot_ap;
		this->game->newBullet(this->x, this->y);
		this->shoot_ap = Player::c_shoot_ap;
	} else {
		this->shoot_ap--;
	}
	AEnemy *tmp = game.enemies;
	if (tmp){
		if (tmp->collide(this->x, this->y)){
			if (!tmp->isDestructible()){
				game.exit = true;
			}
			if (game.life <= 0)
				game.exit = true;
			else {
				game.life -= 1;
				game.destroyFirstAEnemy(tmp);
		        delete tmp;
		        tmp = NULL;
			}
		}
		if (tmp){
			tmp = tmp->next;
			while (tmp && tmp != game.enemies){
				if (tmp->collide(this->x, this->y)){
					if (!tmp->isDestructible()){
						game.exit = true;
					}
					if (game.life <= 0)
						game.exit = true;
					else {
						game.life -= 1;
						game.destroyFirstAEnemy(tmp);
				        delete tmp;
				        tmp = NULL;
					}
				}
				if (tmp)
					tmp = tmp->next;
			}
		}
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
