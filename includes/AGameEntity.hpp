#


class AGameEntity
{
public:
	AGameEntity();
	AGameEntity(AGameEntity const &);
	AGameEntity& operator=(AGameEntity const &);
	~AGameEntity();
	virtual void	display(/* windows ncurse*/ ) = 0;
	virtual void	move(/* windows ncurse*/ ) = 0;

protected:
	int	x;
	int	y;
	int move_ap;
	int	shoot_ap;

	
};
