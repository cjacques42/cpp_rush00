
#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "AGameEntity.hpp"

class Player : public AGameEntity
{
public:
	Player();
	Player(Player const &);
	Player& operator=(Player const &);
	~Player();


	virtual void	display(WINDOW * win);
	virtual void	move(int key);
};


#endif
