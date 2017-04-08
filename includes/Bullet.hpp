
class Bullet
{
public:
	Bullet();
	Bullet(Bullet const &);
	Bullet& operator=(Bullet const &);
	~Bullet();
	


	virtual void	display(/* windows ncurse*/ );
	virtual void	move();
};
