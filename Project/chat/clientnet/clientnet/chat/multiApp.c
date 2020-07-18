#include <stdlib.h> /* atoi */
#include "multi.h"

int main(int argc, char const *argv[])
{
    Multicast* newMulti = MultiCreate(atoi(argv[1]), argv[2], atoi(argv[3]));
    MultiRun(newMulti);
    return 0;
}
/*1500 224.0.0.80 0 */



