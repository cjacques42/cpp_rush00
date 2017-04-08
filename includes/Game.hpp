#ifndef GAME_HPP
# define GAME_HPP

# include "Bullet.hpp"
# include "Player.hpp"
# include "ft_retro.hpp"

class Game {

public:

    static int const FPS = 120;

	Game(void);
	Game(Game const &);
	Game& operator=(Game const &);
	~Game();


    void    display();
    void    loop(void);
    WINDOW *getWindow() const;
    void    newBullet(int x, int y);

    void    update();

    Bullet * bullets;

private:

    WINDOW	*win;

    Player  player;


    int 	ft_min(int a, int b);
    int 	ft_max(int a, int b);
    WINDOW  *actualize_window(WINDOW *old_win);
};


#endif
