/*
**程序名：		基础支持类
**说明：		基础支持类，提供底层数据访问的接口
**版本：		V0.1
**开发日期：	2018/3/14
**修改日期：	2018/3/14
**作者：		筱枫
*/

#ifndef _BASE_NAME_H_
#define _BASE_NAME_H_

#ifdef FILE_UTF_8
    const int char_size = 3;
#else
    const int char_size = 2;
#endif

struct Word
{
	char w[char_size];
};

struct Name
{
    struct Word *name;
    int len;
};

// 抽象基类
class _CBasename
{
public:
    virtual struct Name getName(const int step = 1, const int group_count = 1) = 0;
};

// 基础名称支持类
class CBasename : _CBasename
{
public:
    CBasename(const char *str);

    // 拷贝构造函数
    CBasename(CBasename &cb);

    // 获取名字
    // step 表示在buffer中以多少个单名组成
    // group_count 表明分组引用 例如 "司马南宫"  你可能只想要司马或者南宫，而不是马南
    // 这时候将group_count设置为2即可
    struct Name getName(const int step = 1, const int group_count = 1);

    // 获取随机生成的名字
    // count 表示由几个单名组成
    struct Name getRandomName(const int count = 1);

    // 将Name数据结构转换为字符串
    char *getStr(struct Name name);

    // 设置缓冲区
    // str 表示缓冲区内容
    int setNameBuffer(const char *str);

private:
    struct Word *name_buffer = nullptr;
    int buffer_len = 0;

    // 随机数生成器
    // 生成在[start, end]范围内的整数
    int random(const int start, const int end);

    

};

#endif