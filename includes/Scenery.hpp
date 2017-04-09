#ifndef SCENERY_HPP
# define SCENERY_HPP

# include "AEnemy.hpp"

class Scenery: public AEnemy
{
public:
    Scenery();
	Scenery(int x, int y, int second_x, int second_y);
	Scenery(int x, int y, int second_x, int second_y, AEnemy * first);
    Scenery(Scenery const &);
    Scenery& operator=(Scenery const &);
    ~Scenery();


	virtual bool	isDestructible();
	virtual void	display(WINDOW * win);
	virtual void	move(int key);
	virtual bool 	collide(int x, int y);
	virtual	void	update(Game &);

private:

	int		second_x;
	int		second_y;

	static const int	c_move_ap;
};
#endif