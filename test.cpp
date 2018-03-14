#include "basename.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    const char *str = "你好世界";

    CBasename *cb = new CBasename(str);

    auto temp = cb->getName(2);

    try 
    {
        printf("%s", cb->getStr(temp));
    }
    catch (const char *msg)
    {
        printf("%s", msg);
    }
}