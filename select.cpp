/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

#include <iostream>
using namespace std;

int _kbhit() 
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) 
    {
        /* Use termios to turn off line buffering */
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

/* Simple demo of _kbhit() */

#include <unistd.h>

int main(int argc, char** argv) 
{
    printf("Press any key for fun\n");
    while (!_kbhit()) 
    {
        cout << " - you just pressed " << (char)getchar() << endl;
        //fflush(stdout);
        //usleep(1000);
    }
    printf("\nDone.\n");

    return 0;
} 
