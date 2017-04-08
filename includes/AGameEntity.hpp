#ifndef AGAMEENTITY_HPP
# define AGAMEENTITY_HPP

# include "ft_retro.hpp"

class AGameEntity
{
public:
	AGameEntity();
	AGameEntity(int x, int y, int move_ap, int shoot_ap);
	AGameEntity(AGameEntity const &);
	AGameEntity& operator=(AGameEntity const &);
	~AGameEntity();

	virtual void	display(WINDOW * win) = 0;
	virtual void	move(int key) = 0;

	int		getX();
	int		getY();
	int		getMoveAP();
	int		getShootAP();

protected:
	int	x;
	int	y;
	int	move_ap;
	int	shoot_ap;

	
};

#endif



