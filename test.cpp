#include <iostream>
#include "fullname.h"
#include "fullname.cpp"

int main(int argc, char **argv)
{
    CStyle cs(10);

    cs.set_buffer("中国");
    cs.open_error_file("error.txt");
    cs.write_error("123%d", 1000);
    cs.create(&cs.list[1]);
    cs.print(&cs.list[1]);
    cs.rest_buffer(_single_surname);
    return 0;
}

