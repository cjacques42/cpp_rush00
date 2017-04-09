#ifndef BULLET_HPP
# define BULLET_HPP

# include "ft_retro.hpp"
# include "AGameEntity.hpp"

class AEnemy;
class Game;

class Bullet : public AGameEntity
{
public:
	Bullet(int x, int y, Bullet * first);
	Bullet(int x, int y);
	Bullet(Bullet const &);
	Bullet& operator=(Bullet const &);
	virtual ~Bullet();

	void	update(Game &game);

	virtual void	display(WINDOW * win);
	virtual void	move(int key);

	int			getBulletNb();

	Bullet *	next;
	Bullet *	prev;


private:
	Bullet();


	static int	bulletNb;
	static int const c_move_ap;
};


#endif
