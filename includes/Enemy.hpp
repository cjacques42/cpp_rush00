#ifndef ENEMEY_HPP
# define ENEMEY_HPP

# include "ft_retro.hpp"

class Enemy : public AGameEntity
{
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(Enemy const &);
	Enemy& operator=(Enemy const &);
	~Enemy();

	virtual void	display(WINDOW * win);
	virtual void	move(int key);
};


#endif
