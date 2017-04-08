#ifndef GAME_HPP
# define GAME_HPP

# include "ft_retro.hpp"

class Game {

public:

    static int const FPS = 60;

	Game(void);
	Game(Game const &);
	Game& operator=(Game const &);
	~Game();


    void    display();
    void    loop(void);
    WINDOW *getWindow() const;

private:
    int     interval;
    int     score;
    WINDOW	*win;
    Player  player;
    // Enemy   *enemies;

    int 	ft_min(int a, int b);
    int 	ft_max(int a, int b);
    WINDOW  *actualize_window(WINDOW *old_win);
    void    randomEnemy(int);
    void    move(void);
    void    colide(void);

};

#endif
