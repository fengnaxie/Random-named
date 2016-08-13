# fullname

### 1.概述
  欢迎来到本页面，这是一个用于随机生成中文名称的类，可生成单姓单名、单姓双名、复姓单名、复姓双名等
  
### 2.使用方法
最简单的一个程序如下：
```
CStyle cs;
printf("%s\n", cs.create());
```

这将直接输出随机的名字，使用内建的一些姓、名

### 3.函数详情
#### public:
##### `CStyle(const int _name_num = -1)`

构造函数，用于建立内部姓名存储空间, 默认不建立

##### `CStyle(const CStyle &cs);`

拷贝构造函数

##### `~CStyle()`
析构函数

##### `virtual char *create(const int index = -1, NAME_FLAGS flags = _0)`
用于生成姓名，NAME_FLAGS是一个枚举类型，可控制生成的姓名，默认随机生成；index默认不保存本次生成结果

返回值：生成的姓名

##### `int set_buffer(const char *src, SETNAME_FLAGS flags = _single_surname)`
设置内部生成用的缓冲区，SETNAME_FLAGS是一个枚举类型，默认设置单姓的缓冲区

返回值：0表明成功，-1表明缓冲区不存在或者并非2的倍数

##### `int rest_buffer(SETNAME_FLAGS flags)`
重置缓冲区为内部默认缓冲区

返回值：0表明成功，-1表明缓冲区已经为默认的缓冲区

##### `int print(const int index = -1)`
打印出指定索引的姓名

返回值：0表明成功，-1表明索引超出范围或者内部缓冲区不存在

##### `int insert(NAME_FLAGS flags = _0)`
随机生成一个姓名并插入到内部缓冲区中的空闲位置
返回值：返回生成姓名的索引

##### `int del(const int index)`
删除指定索引位置的姓名
返回值：返回删除姓名的索引

##### `char *get_all_fullname(void)`
返回内部缓冲区中的所有姓名

##### `int get_name_num(void)`
返回内部缓冲区已存储多少个姓名

##### `int open_error_file(const char *filename, FILE *fp = NULL);`
打开一个错误记录文件，指定fp将忽略filename

##### `int write_error(const char *str, ...)`
输出错误消息

##### `int close_error_file(void)`
关闭错误记录文件

##### `int random(void)`
随机函数

##### `CStyle clone(void)`
复制自身并返回
