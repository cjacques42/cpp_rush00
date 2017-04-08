
class Player : public AGameEntity
{
public:
	Player();
	Player(Player const &);
	Player& operator=(Player const &);
	~Player();
	

	virtual void	display(/* windows ncurse*/ );
	virtual void	move(/* windows ncurse*/ );
};
