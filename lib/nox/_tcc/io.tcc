#ifdef linux

char nox::_getch()
{
    char ch;

    struct termios old;
    struct termios new_t;

    tcgetattr(0, &old);
    new_t = old;
    new_t.c_lflag &= ~ICANON;
    new_t.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_t);
    ch = (char)getchar();
    tcsetattr(0, TCSANOW, &old);

    return ch;
}

char nox::getch(unsigned int __max_wait_time) 
{
    char ch = (char)0;

    fd_set rfds;
    struct timeval tv;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    tv.tv_sec = 0;
    tv.tv_usec = __max_wait_time *10;

    int has_input = select(1, &rfds, NULL, NULL, &tv);

    if (has_input == 1)
    {
        ch = nox::_getch();
    }

    return ch;
}
#elif defined(_WIN32)



#else

char nox::_getch()
{
    return 0;
}

char nox::getch(usnigned int __max_wait_time)
{
    return nox::_getch();
}

#endif

