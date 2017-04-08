#ifndef ENEMEY_HPP
# define ENEMEY_HPP

# include "AGameEntity.hpp"

class Enemy : public AGameEntity
{
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(int x, int y, Enemy * first);
	Enemy(Enemy const &);
	Enemy& operator=(Enemy const &);
	virtual ~Enemy();



	Enemy	*prev;
	Enemy	*next;
	void	update();
	virtual void	display(WINDOW * win);
	virtual void	move(int key);

private:

	static const int	c_move_ap;
};


#endif
