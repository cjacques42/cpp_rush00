#ifndef SMALLSHIP_HPP
# define SMALLSHIP_HPP

# include "AEnemy.hpp"

class SmallShip: public AEnemy
{
public:
    SmallShip();
	SmallShip(int x, int y);
	SmallShip(int x, int y, AEnemy * first);
    SmallShip(SmallShip const &);
    SmallShip& operator=(SmallShip const &);
    ~SmallShip();


	virtual bool	isDestructible();
	virtual void	display(WINDOW * win);
	virtual void	move(int key);
	virtual bool 	collide(int x, int y);
	virtual	void	update(Game &);

private:

	static const int	c_move_ap;
};
#endif
