#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <exception>
#include <stdexcept>

#include "basename.h"

using namespace std;

CBasename::CBasename(const char *str)
{
    srand(time(NULL));
    setNameBuffer(str);
}

CBasename::CBasename(CBasename &cb)
{
    cb.buffer_len = buffer_len;

    static char *temp_buffer = nullptr;

    if (buffer_len > 0)
    {
        // 给予新的内存，防止原有引用被删除
        static char *temp_buffer = new char[buffer_len*char_size];

        memcpy(temp_buffer, name_buffer, buffer_len*char_size);
    }

    cb.name_buffer = (struct Word*)temp_buffer;
}

struct Name CBasename::getName(const int step, const int group_count)
{
    if (step > buffer_len)
        throw "步进值超过缓冲区长度！";

    if (step <= 0 || group_count <= 0)
        throw "参数错误！";

    struct Name ret;
    static struct Word *name = new struct Word[step];

    int start = buffer_len;

    // 确保不会数组越界
    while (start + step > buffer_len)
        start = random(0, (buffer_len - step)/group_count);

    int i = 0;

    // 复制名字的数据
    // 例如将"南宫司马" 中的 "南宫"给复制过去
    // group用于分组，例如有时你不想要宫司...
    while (i < step)
    {
        name[i] = name_buffer[start*group_count+i];
        i++;
    }

    ret.name = name;
    ret.len = step;

    return ret;
}

struct Name CBasename::getRandomName(const int count)
{
    if (buffer_len <= 0)
        throw "缓冲区中没有数据！";

    struct Name ret;
    static struct Word *name = new struct Word[count];

    int i = 0;

    // 随机复制名字的数据
    // 例如将"南宫司马" 中的 "南马"给复制过去
    while (i < count)
    {
        name[i] = name_buffer[random(0, buffer_len)];
        i++;
    }

    ret.name = name;
    ret.len = count;

    return ret;
}

char *CBasename::getStr(struct Name name)
{
    char *buffer = new char[name.len*char_size];

    for (int i=0; i<name.len; i++)
    {
        int start = i*char_size;
        buffer[start] = name.name[i].w[0];
        buffer[start+1] = name.name[i].w[1];

        #ifdef FILE_UTF_8
            buffer[start+2] = name.name[i].w[2];
        #endif
    }

    return buffer;
}

int CBasename::setNameBuffer(const char *str)
{
    if (buffer_len > 0)
        delete []name_buffer;

    buffer_len = strlen(str) / char_size;

    if (buffer_len <= 0)
        throw "字符串中没有数据！";

    static char *temp_buffer = new char[buffer_len*char_size];

    memcpy(temp_buffer, str, buffer_len*char_size);

    // 强制转换，将多余的数据给丢掉
    name_buffer = (struct Word *)temp_buffer;

    return buffer_len;
}

int CBasename::random(const int start, const int end)
{
    if (end <= start)
        throw "结束范围不能小于等于开始范围！";

    return (rand() % (end-start+1)) + start;
}


