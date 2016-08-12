/*
**程序名：		瞎起名工具
**说明：		瞎起名，用作一个库链接使用，使用面向对象重构
**版本：		V0.1
**开发日期：	2016/4/20
**修改日期：	2016/4/20
**作者：		筱枫
*/

#include "fullname.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdarg.h>


CStyle::CStyle(int _name_num)
{
	name_num = _name_num;

    // 默认将所有的错误输出到屏幕上
	open_error_file(NULL, stderr);

	if (name_num <= 0)
    {
        write_error("name_num 不能小于等于 0!\n");
        return;
    }

	list = new struct Fullname[sizeof(struct Fullname)*name_num];

	if (NULL == list)
    {
        write_error("list表申请内存失败！\n");
        return;
    }

	memset(list, 0, sizeof(struct Fullname)*name_num);

	srand(time(NULL));

	for (int i=0; i<4; i++)
       store_buffer[i] = NULL;
}


CStyle::CStyle(const CStyle &cs)
{
    // 拷贝构造函数
    name_num = cs.name_num;

    list = new struct Fullname[sizeof(struct Fullname)*name_num];

    if (NULL == list)
    {
        write_error("list表申请内存失败！\n");
        return;
    }

    for (int i=0; i<name_num; i++)
    {
        list[i] = cs.list[i];
    }

    list = cs.list;
    name = cs.name;

    for (int i=0; i<4; i++)
       store_buffer[i] = NULL;

    if (strcmp(buffer_surname_female, cs.buffer_surname_female))
        set_buffer(cs.buffer_surname_female, _single_surname);
    else if(strcmp(buffer_surname_female2, cs.buffer_surname_female2))
        set_buffer(cs.buffer_surname_female2, _double_surname);
    else if(strcmp(buffer_name_female, cs.buffer_name_female))
        set_buffer(cs.buffer_name_female, _single_name);
    else if(strcmp(buffer_name_female2, cs.buffer_name_female2))
        set_buffer(cs.buffer_name_female2, _double_name);
}

int CStyle::create(struct Fullname *fn, NAME_FLAGS flags)
{
    // 随机生成
    if (_0 == flags)
        flags = NAME_FLAGS(rand()%6);

    if (NULL == fn)
    {
        write_error("生成姓名失败！姓名缓冲区不能为空！\n");
        return -1;
    }

	switch (flags)
	{
		case _11:
			return _fullname(fn);
		break;

		case _12:
			return _fullname2(fn);
		break;

		case _122:
			return _fullname22(fn);
		break;

		case _21:
			return _full2name(fn);
		break;

		case _22:
			return _full2name2(fn);
		break;

		case _222:
			return _full2name22(fn);
		break;

		default:
		break;
	}

	return 0;
}

int CStyle::_fullname(struct Fullname *fn)
{
	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2+1)];
	fn->w[1] = name[rand()%((strlen((char *)name)-1)/2+1)];

	return 0;
}

int CStyle::_fullname2(struct Fullname *fn)
{
	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2+1)];
	fn->w[1] = name[rand()%((strlen((char *)name)-1)/2+1)];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2+1)];

	return 0;
}

int CStyle::_fullname22(struct Fullname *fn)
{
	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female2;

	i = rand()%((strlen((char *)name)-1)/2+1);

    // 确保i为2的倍数
	if (i%2 && i!=0) i--;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2+1)];
	fn->w[1] = name[i];
	fn->w[2] = name[i+1];

	return 0;
}

int CStyle::_full2name(struct Fullname *fn)
{
	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

	i = rand()%((strlen((char*)surname)-1)/2+1);

    // 确保i为2的倍数
	if (i%2 && i!= 0) i--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2+1)];

	return 0;
}

int CStyle::_full2name2(struct Fullname *fn)
{
	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

	i = rand()%((strlen((char*)surname)-1)/2+1);

    // 确保i为2的倍数
	if (i%2 && i!= 0) i--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2+1)];
	fn->w[3] = name[rand()%((strlen((char *)name)-1)/2+1)];

	return 0;
}

int CStyle::_full2name22(struct Fullname *fn)
{
	int i, j;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female2;

	i = rand()%((strlen((char*)surname)-1)/2+1);
	j = rand()%((strlen((char*)name)-1)/2+1);

    // 确保i与j为2的倍数
	if (i%2 && i!=0) i--;
	if (j%2 && j!=0) j--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[j];
	fn->w[3] = name[j+1];

	return 0;
}

int CStyle::print(const struct Fullname *print)
{
    if (NULL == print)
    {
        write_error("需打印的姓名不存在！\n");
        return -1;
    }

    printf("%c%c", print->w[0].w[0], print->w[0].w[1]);
    printf("%c%c", print->w[1].w[0], print->w[1].w[1]);
    printf("%c%c", print->w[2].w[0], print->w[2].w[1]);
    printf("%c%c", print->w[3].w[0], print->w[3].w[1]);
    printf("\n");
    return 0;
}

int CStyle::set_buffer(const char *src, SETNAME_FLAGS flags)
{
    static char *buffer = NULL;

	if (NULL == src)
    {
        write_error("待设置的缓冲区不存在！\n");
    }

    // 这段代码防止取余0错误
    if ((strlen(src)-1)/2 == 0)
    {
        buffer = new char[strlen(src)*2];
        strcpy(buffer, src);
        strcat(buffer, src);
    }
    else
    {
        buffer = new char[strlen(src)];
        strcpy(buffer, src);
    }

	switch (flags)
	{
    case _single_surname:
        store_buffer[0] = buffer_surname_female;
        buffer_surname_female = buffer;
        break;

    case _double_surname:
        store_buffer[1] = buffer_surname_female2;
        buffer_surname_female2 = buffer;
        break;

    case _single_name:
        store_buffer[2] = buffer_name_female;
        buffer_name_female = buffer;
        break;

    case _double_name:
        store_buffer[3] = buffer_name_female2;
        buffer_name_female2 = buffer;
        break;

    default:
        break;
	}
	return 0;
}

int CStyle::rest_buffer(SETNAME_FLAGS flags)
{
    switch (flags)
    {
    case _single_surname:
        if (NULL == store_buffer[0])
            return -1;

        delete [] buffer_surname_female;
        buffer_surname_female = store_buffer[0];
        break;

    case _double_surname:
        if (NULL == store_buffer[1])
            return -1;

        delete [] buffer_surname_female2;
        buffer_surname_female2 = store_buffer[1];
        break;


    case _single_name:
        if (NULL == store_buffer[2])
            return -1;

        delete [] buffer_name_female;
        buffer_name_female = store_buffer[2];
        break;

    case _double_name:
        if (NULL == store_buffer[3])
            return -1;

        delete [] buffer_name_female2;
        buffer_name_female2 = store_buffer[3];
        break;

    default:
        break;
    }
    return 0;
}

int CStyle::open_error_file(const char *filename, FILE *fp)
{
    if (error_fp)
        close_error_file();

    if (fp)
    {
        error_fp = fp;
    }
    else
    {
        error_fp = fopen(filename, "w");

        if (NULL == error_fp)
        {
            fprintf(stderr, "打开错误记录文件：%s 失败！\n", filename);
            return -1;
        }
    }

    return 0;
}

int CStyle::write_error(const char *str, ...)
{
    if (NULL == error_fp)
    {
        fprintf(stderr, "错误文件指针不存在，请先打开错误文件！\n");
        return -1;
    }

    char buffer[1024];
    va_list args;

    // 初始化可变参数并使用vsprintf输出到buffer中
    va_start(args, str);
    vsprintf(buffer, str, args);
    va_end(args);

    fprintf(error_fp, buffer);

    // 刷新输出流
    fflush(error_fp);

    return 0;
}

int CStyle::close_error_file(void)
{
    if (error_fp)
    {
        fclose(error_fp);
        error_fp = NULL;
    }

    return 0;
}

CStyle CStyle::clone(void)
{
    // 该函数复制自身并返回新的对象
    return CStyle(*this);
}

CStyle::~CStyle()
{
    if (name_num > 0)
        delete [] list;

    close_error_file();
}
