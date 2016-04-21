#include "fullname.h"

int main(int argc, char **argv)
{
    CStyle cs(10);
    cs.fullname(&cs.list[0], _0);
    cs.fullname_print(&cs.list[0]);

    cs.setname("ÄãºÃ");
    cs.fullname(&cs.list[1]);
    cs.fullname_print(&cs.list[1]);
    cs.restname(_single_surname);

    for (int i=2; i<10; i++)
    {
        cs.fullname(&cs.list[i], _0);
        cs.fullname_print(&cs.list[i]);
    }

    return 0;
}
