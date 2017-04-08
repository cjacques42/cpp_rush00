


class Enemy : public AGameEntity
{
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(Enemy const &);
	Enemy& operator=(Enemy const &);
	~Enemy();


	virtual void	display(/* windows ncurse*/ );
	virtual void	move();
};
