#include <curses.h>

int		main(){
	bool	exit = false;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	nodelay(stdscr, TRUE);
	int ch;

	while(!exit) {
		ch = getch();

		if (ch == 4 || ch == 3){
			exit = true;
		} else if (ch != ERR){
			printw("%d", ch);
		} 

	}


	endwin();
}