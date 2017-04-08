#ifndef GAME_HPP
# define GAME_HPP

# include "ft_retro.hpp"

class Game {

public:

    static int const FPS = 20;

	Game(void);
	Game(Game const &);
	// Game& operator=(Game const &);
	~Game();

    void loop(void);

private:

    WINDOW	*win;

    int 	ft_min(int a, int b);
    int 	ft_max(int a, int b);
    WINDOW  *actualize_window(WINDOW *old_win);
};


#endif
