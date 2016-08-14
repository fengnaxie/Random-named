/*
**程序名：		瞎起名工具
**说明：		瞎起名，用作一个库链接使用，使用面向对象重构
**版本：		V0.1
**开发日期：	2016/4/20
**修改日期：	2016/8/13
**作者：		筱枫
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdarg.h>

#include "fullname.h"


CStyle::CStyle(int _name_num)
{
	name_num = _name_num;

    // 默认将所有的错误输出到屏幕上
	open_error_file(NULL, stderr);

	if (name_num <= 0)
    {
        list = NULL;
    }
	else
	{
		list = new struct Fullname[sizeof(struct Fullname)*name_num];

		if (NULL == list)
		{
			write_error("list表申请内存失败！\n");
			return;
		}

		memset(list, 0, sizeof(struct Fullname)*name_num);
	}

	srand(time(NULL));

	for (int i=0; i<4; i++)
       store_buffer[i] = NULL;
}


CStyle::CStyle(const CStyle &cs)
{
    // 拷贝构造函数
    name_num = cs.name_num;
	if (name_num <= 0)
	{
		list = NULL;
	}
	else
	{
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
	}

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

char *CStyle::create(const int index, NAME_FLAGS flags)
{
    struct Fullname *fn;
    // 随机生成
    if (_0 == flags)
        flags = NAME_FLAGS(random()%6);

    // index小于0表明临时生成，不保存数据
    if (index < 0)
    {
        struct Fullname fn_temp;
        memset(&fn_temp, 0, sizeof(struct Fullname));
        fn = &fn_temp;
    }
    else
    {
        if (index >= name_num)
        {
            struct Fullname *new_list = new struct Fullname[sizeof(struct Fullname)*(index+1)];

            if (NULL == new_list)
            {
                write_error("申请更大的内存失败！请查看索引是否过大！\n");
                return NULL;
            }

            // 拷贝数据到新的内存中
            memset(new_list, 0, sizeof(struct Fullname)*(index+1));

            if (NULL != list)
            {
                memcpy(new_list, list, sizeof(struct Fullname)*name_num);
                delete[] list;
            }

            // 指向新数据
            name_num = index+1;
            list = new_list;
        }

        fn = &list[index];
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

	return NULL;
}

char *CStyle::_fullname(struct Fullname *fn)
{
	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	if (!check((char *)surname) || !check((char *)name))
    {
        write_error("校验内部缓冲区失败！\n");
        return NULL;
    }

	fn->w[0] = surname[random()%((strlen((char *)surname)-1)/sizeof(struct Word)+1)];
	fn->w[1] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];

	return fullToString(fn);
}

char *CStyle::_fullname2(struct Fullname *fn)
{
	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Word *)buffer_name_female;

	if (!check((char *)surname) || !check((char *)name))
    {
        write_error("校验内部缓冲区失败！\n");
        return NULL;
    }

	fn->w[0] = surname[random()%((strlen((char *)surname)-1)/sizeof(struct Word)+1)];
	fn->w[1] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];
	fn->w[2] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];

	return fullToString(fn);
}

char *CStyle::_fullname22(struct Fullname *fn)
{
	struct Doublename temp;
	struct Doublename *name;

	// 重定向
	surname = (struct Word *)buffer_surname_female;
	name = (struct Doublename *)buffer_name_female2;

	if (!check((char *)surname) || !check((char *)name))
    {
        write_error("校验内部缓冲区失败！\n");
        return NULL;
    }

	temp = name[random()%((strlen((char *)name)-1)/sizeof(struct Doublename)+1)];

	fn->w[0] = surname[random()%((strlen((char *)surname)-1)/sizeof(struct Word)+1)];
	fn->w[1] = temp.w[0];
	fn->w[2] = temp.w[1];

	return fullToString(fn);
}

char *CStyle::_full2name(struct Fullname *fn)
{
    struct Doublename temp;
    struct Doublename *surname;

	// 重定向
	surname = (struct Doublename *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

	if (!check((char *)surname) || !check((char *)name))
    {
        write_error("校验内部缓冲区失败！\n");
        return NULL;
    }

	temp = surname[random()%((strlen((char*)surname)-1)/sizeof(struct Doublename)+1)];

	fn->w[0] = temp.w[0];
	fn->w[1] = temp.w[1];
	fn->w[2] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];

	return fullToString(fn);
}

char *CStyle::_full2name2(struct Fullname *fn)
{
	struct Doublename temp;
	struct Doublename *surname;

	// 重定向
	surname = (struct Doublename *)buffer_surname_female2;
	name = (struct Word *)buffer_name_female;

    temp = surname[random()%((strlen((char*)surname)-1)/sizeof(struct Doublename)+1)];

	fn->w[0] = temp.w[0];
	fn->w[1] = temp.w[1];
	fn->w[2] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];
	fn->w[3] = name[random()%((strlen((char *)name)-1)/sizeof(struct Word)+1)];

	return fullToString(fn);
}

char *CStyle::_full2name22(struct Fullname *fn)
{
	struct Doublename temp_surname;
	struct Doublename temp_name;
	struct Doublename *surname;
	struct Doublename *name;

	// 重定向
	surname = (struct Doublename *)buffer_surname_female2;
	name = (struct Doublename *)buffer_name_female2;

    temp_surname = surname[random()%((strlen((char*)surname)-1)/sizeof(struct Doublename)+1)];
    temp_name = name[random()%((strlen((char*)name)-1)/sizeof(struct Doublename)+1)];

	fn->w[0] = temp_surname.w[0];
	fn->w[1] = temp_surname.w[1];
	fn->w[2] = temp_name.w[0];
	fn->w[3] = temp_name.w[1];

	return fullToString(fn);
}

char *CStyle::fullToString(const struct Fullname *fn)
{
	if (NULL == fn)
	{
		write_error("fullToString 错误！ 参数不能为NULL!");
		return NULL;
	}

	// 使用static关键字防止buffer指针因生存期结束而被销毁
	static char buffer[sizeof(struct Fullname)+1];
	memset(buffer, '\0', sizeof(struct Fullname)+1);

    for (unsigned int i=0, j=0; i<sizeof(struct Fullname); i += sizeof(struct Word), j++)
    {
        buffer[i] = fn->w[j].w[0];
        buffer[i+1] = fn->w[j].w[1];

        #ifdef FILE_UTF_8
        buffer[i+2] = fn->w[j].w[2];
        #endif
    }

	return buffer;
}

int CStyle::print(const int index)
{
    struct Fullname *print;

    if (index < 0 || index > name_num)
    {
        write_error("索引超出范围！\n");
        return -1;
    }

    if (NULL == list)
    {
    	write_error("内部缓冲区不存在！\n");
    	return -1;
    }

    print = &list[index];

    printf("%s\n", fullToString(print));
    return 0;
}

int CStyle::set_buffer(const char *src, SETNAME_FLAGS flags)
{
    static char *buffer = NULL;

	if (NULL == src || !check(src))
    {
        write_error("待设置的缓冲区错误！\n");
        return -1;
    }

    // 这段代码防止取余0错误
    if ((strlen(src)-1)/sizeof(struct Word) == 0)
    {
        buffer = new char[strlen(src)*sizeof(struct Word)];
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

int CStyle::reset_buffer(SETNAME_FLAGS flags)
{
    switch (flags)
    {
    case _single_surname:
        if (NULL == store_buffer[0])
            return -1;

        delete [] buffer_surname_female;
        buffer_surname_female = store_buffer[0];
		store_buffer[0] = NULL;
        break;

    case _double_surname:
        if (NULL == store_buffer[1])
            return -1;

        delete [] buffer_surname_female2;
        buffer_surname_female2 = store_buffer[1];
		store_buffer[1] = NULL;
        break;


    case _single_name:
        if (NULL == store_buffer[2])
            return -1;

        delete [] buffer_name_female;
        buffer_name_female = store_buffer[2];
		store_buffer[2] = NULL;
        break;

    case _double_name:
        if (NULL == store_buffer[3])
            return -1;

        delete [] buffer_name_female2;
        buffer_name_female2 = store_buffer[3];
		store_buffer[3] = NULL;
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

char *CStyle::get_all_fullname(void)
{
    static char *buffer = new char[sizeof(struct Fullname)*(name_num+1)];
    memset(buffer, '\0', sizeof(struct Fullname)*(name_num+1));

    for (int i=0; i<name_num; i++)
    {
        strcat(buffer, fullToString(&list[i]));
        strcat(buffer, "\n");
    }

    // 去掉最后面的一个"\n"
    buffer[strlen(buffer)-1] = '\0';

    return buffer;
}

int CStyle::insert(NAME_FLAGS flags)
{
    if (NULL == list)
    {
        create(0, flags);
        return 0;
    }
    int i=0;

    for (i=0; i<name_num; i++)
    {
        if (0 == list[i].w[0].w[0] || 0 == list[i].w[0].w[1])
        {
            create(i, flags);
            return i;
        }
    }

    // 到这里表明在list表中没有寻找到空位，只能在列表最后的位置新增
    create(i, flags);
    return i;
}

int CStyle::del(const int index)
{
    if (index < 0 || index >= name_num)
    {
        write_error("del()错误！索引超出范围！\n");
        return -1;
    }

    for (int i=index; i<name_num-1; i++)
    {
        // 顺序前移
        list[i] = list[i+1];
    }

    name_num -= 1;

    return index;
}

int CStyle::random(void)
{
    return rand();
}

int CStyle::get_name_num(void)
{
    return name_num;
}

int CStyle::check(const char *src)
{
    return (0 == (strlen(src)%sizeof(struct Word)));
}

CStyle::~CStyle()
{
    if (name_num > 0)
        delete [] list;

    for (int i=0; i<4; i++)
    {
        if (NULL != store_buffer[i])
        {
			reset_buffer(SETNAME_FLAGS(i));
        }
    }

    close_error_file();
}
