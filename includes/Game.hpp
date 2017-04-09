#ifndef GAME_HPP
# define GAME_HPP

# include "Bullet.hpp"
# include "Player.hpp"
# include "ft_retro.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Bullet.hpp"

class Game {

public:

    static int const FPS = 120;
    bool    exit;
    Enemy   *enemies;
    Bullet	*bullets;
    int     width;
    int     height;
    int     score;
    int     life;
    char    timer[5];

	Game(void);
	Game(Game const &);
	Game& operator=(Game const &);
	~Game();


    void    display();
    void    loop(void);
    WINDOW *getWindow() const;
    void    newBullet(int x, int y);
    void    update();
    void    destroyFirstBullet(Bullet *);
    void    destroyFirstEnemy(Enemy *);

private:
    int     interval;
    WINDOW	*win;
    Player  player;

    int 	ft_min(int a, int b);
    int 	ft_max(int a, int b);
    WINDOW  *actualize_window(WINDOW *old_win);
    void    randomEnemy(int);
    void    colide(void);

};

#endif
