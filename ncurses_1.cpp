#include <ncurses.h>

char _key_detected;

int main()
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while (true) 
    {
	_key_detected = getch();

        if(_key_detected == 'g') 
        {
           printw("You pressed g\n");
        }
	else if(_key_detected == 'a') 
        {
           printw("You pressed a\n");
        }
	napms(5); //sleep 5ms
    }
}
