#ifndef BULLET_HPP
# define BULLET_HPP

# include "AGameEntity.hpp"

class Bullet : public AGameEntity
{
public:
	Bullet();
	Bullet(Bullet const &);
	Bullet& operator=(Bullet const &);
	~Bullet();



	virtual void	display(WINDOW * win);
	virtual void	move(int key);
};


#endif
