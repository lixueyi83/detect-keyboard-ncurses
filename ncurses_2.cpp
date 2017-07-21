#include <ncurses.h>

int main()
{
	int ch;

	initscr();	/*start curses mode*/
	raw();		/*Line buffering disabled*/
	keypad(stdscr, TRUE);	/* we get F1, F2 etc...*/
	noecho();		/*Don't echo() while we do getch */
	printw("Type any character to see it in bold, type 'q' to quit the program.\n");

	while(1)	
	{
		ch = getch();  		/* If raw() hadn't been called, we have to press enter before it gets the program */

		if(ch == KEY_F(1))	/*Without keypad enabled this will not get to us either*/
			printw("F1 Key pressed");  /*Without noecho() some ugly escape characters might have been printed on screen*/
		else
		{
			printw("The pressed key is ");
			attron(A_BOLD);
			printw("%c\n", ch);
			attroff(A_BOLD);
		}

        if(ch == 'q') return 0;
		refresh();	/*print it on to the real screen*/
	}
	endwin();		/*end curses mode*/

	return 0;
}
