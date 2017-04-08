#ifndef ENEMEY_HPP
# define ENEMEY_HPP

# include "AGameEntity.hpp"

class Enemy : public AGameEntity
{
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(Enemy const &);
	Enemy& operator=(Enemy const &);
	~Enemy();

	Enemy	*prev;
	Enemy	*next;
	virtual void	display(WINDOW * win);
	virtual void	move(int key);
};


#endif
