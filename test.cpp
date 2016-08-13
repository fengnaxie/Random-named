#include <iostream>
#include "fullname.h"
#include "fullname.cpp"

int main(int argc, char **argv)
{
    CStyle cs;
    cs.create(0);
    cs.create(1);
    cs.create(2);
    printf("%s\n", cs.get_all_fullname());
    printf("%d\n", cs.del(1));
    printf("%s\n", cs.get_all_fullname());
    return 0;
}
