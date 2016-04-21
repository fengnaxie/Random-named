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


CStyle::CStyle(int _name_num)
{
	name_num = _name_num;

	if (name_num <= 0)
		return;

	list = (struct Fullname *)malloc(sizeof(struct Fullname)*name_num);

	if (NULL == list)
		return;

	memset(list, 0, sizeof(struct Fullname)*name_num);

	srand(time(NULL));

    for (int i=0; i<4; i++)
        store_buffer[0] = NULL;
}

int CStyle::fullname(struct Fullname *fn, NAME_FLAGS flags)
{
	if (name_num <= 0)
		return -2;

    // 随机生成
    if (_0 == flags)
        flags = NAME_FLAGS(rand()%6);

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
	if (NULL == fn)
		return -1;

	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2)];
	fn->w[1] = name[rand()%((strlen((char *)name)-1)/2)];

	return 0;
}

int CStyle::_fullname2(struct Fullname *fn)
{
	if (NULL == fn)
		return -1;

	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2)];
	fn->w[1] = name[rand()%((strlen((char *)name)-1)/2)];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2)];

	return 0;
}

int CStyle::_fullname22(struct Fullname *fn)
{
	if (NULL == fn)
		return -1;

	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female2;

	i = rand()%((strlen((char *)name)-1)/2);

	if (i%2 && i!=0) i--;

	fn->w[0] = surname[rand()%((strlen((char *)surname)-1)/2)];
	fn->w[1] = name[i];
	fn->w[2] = name[i+1];

	return 0;
}

int CStyle::_full2name(struct Fullname *fn)
{
	if (NULL == fn)
		return -1;

	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

	i = rand()%((strlen((char*)surname)-1)/2);

	if (i%2 && i!= 0) i--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2)];

	return 0;
}

int CStyle::_full2name2(struct Fullname *fn)
{
	if (NULL == fn)
		return -1;

	int i;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

	i = rand()%((strlen((char*)surname)-1)/2);

	if (i%2 && i!= 0) i--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[rand()%((strlen((char *)name)-1)/2)];
	fn->w[3] = name[rand()%((strlen((char *)name)-1)/2)];

	return 0;
}

int CStyle::_full2name22(struct Fullname *fn)
{
	if (NULL == fn)
		return -1;

	int i, j;

	// 重定向
	surname = (struct Word *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female2;

	i = rand()%((strlen((char*)surname)-1)/2);
	j = rand()%((strlen((char*)name)-1)/2);

	if (i%2 && i!=0) i--;
	if (j%2 && j!=0) j--;

	fn->w[0] = surname[i];
	fn->w[1] = surname[i+1];
	fn->w[2] = name[j];
	fn->w[3] = name[j+1];

	return 0;
}

int CStyle::fullname_print(const struct Fullname *print)
{
    if (NULL == print)
        return -1;

    printf("%c%c%", print->w[0].w[0], print->w[0].w[1]);
    printf("%c%c%", print->w[1].w[0], print->w[1].w[1]);
    printf("%c%c%", print->w[2].w[0], print->w[2].w[1]);
    printf("%c%c%", print->w[3].w[0], print->w[3].w[1]);
    printf("\n");
    return 0;
}

int CStyle::setname(char *src, SETNAME_FLAGS flags)
{
	if (NULL == src)
		return -1;

	switch (flags)
	{
    case _single_surname:
        store_buffer[0] = buffer_surname_female;
        buffer_surname_female = src;
        break;

    case _double_surname:
        store_buffer[1] = buffer_surname_female2;
        buffer_surname_female2 = src;
        break;

    case _single_name:
        store_buffer[2] = buffer_name_female;
        buffer_name_female = src;
        break;

    case _double_name:
        store_buffer[3] = buffer_name_female2;
        buffer_name_female2 = src;
        break;

    default:
        break;
	}
	return 0;
}

int CStyle::restname(SETNAME_FLAGS flags)
{
    switch (flags)
    {
    case _single_surname:
        if (NULL == store_buffer[0])
            return -1;

        free(buffer_surname_female);
        buffer_surname_female = store_buffer[0];
        break;

    case _double_surname:
        if (NULL == store_buffer[1])
            return -1;

        free(buffer_surname_female2);
        buffer_surname_female2 = store_buffer[1];
        break;


    case _single_name:
        if (NULL == store_buffer[2])
            return -1;

        free(buffer_name_female);
        buffer_name_female = store_buffer[2];
        break;

    case _double_name:
        if (NULL == store_buffer[3])
            return -1;

        free(buffer_name_female2);
        buffer_name_female2 = store_buffer[3];
        break;

    default:
        break;
    }
    return 0;
}

CStyle::~CStyle()
{
    if (name_num > 0)
        free(list);
}
