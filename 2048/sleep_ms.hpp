#include <iostream>
#include <stdio.h>
#include <sys/select.h>

using namespace std;
static void sleep_ms(unsigned int secs)
{

    struct timeval tval;

    tval.tv_sec = secs / 1000;
    tval.tv_usec = (secs * 1000) % 1000000;

    select(0, NULL, NULL, NULL, &tval);
}
