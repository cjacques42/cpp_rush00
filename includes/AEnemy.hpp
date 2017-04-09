#ifndef ENEMEY_HPP
# define ENEMEY_HPP

# include "AGameEntity.hpp"

class Game;

class AEnemy : public AGameEntity
{
public:
	AEnemy();
	AEnemy(int x, int y);
	AEnemy(int x, int y, AEnemy * first);
	AEnemy(AEnemy const &);
	AEnemy& operator=(AEnemy const &);
	virtual ~AEnemy();



	AEnemy	*prev;
	AEnemy	*next;
	virtual	bool	isDestructible() = 0;
	virtual	void	update(Game &game);
	virtual void	display(WINDOW * win);
	virtual void	move(int key);
	virtual bool 	collide(int x, int y) = 0;

private:

	static const int	c_move_ap;
};


#endif
