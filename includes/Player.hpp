
#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "AGameEntity.hpp"
class Game;
class Enemy;

class Player : public AGameEntity
{
public:
	Player();
	Player(Game * game);
	Player(Player const &);
	Player& operator=(Player const &);
	~Player();

	void	update(Enemy ***map, Game &game);

	virtual void	display(WINDOW * win);
	virtual void	move(int key);

	static const int	c_shoot_ap;

	Game *	game;
};


#endif
