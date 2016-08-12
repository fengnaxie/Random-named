/*
**程序名：		瞎起名工具
**说明：		瞎起名，用作一个库链接使用，使用面向对象重构
**版本：		V0.1
**开发日期：	2016/4/20
**修改日期：	2016/4/20
**作者：		筱枫
*/

#ifndef _STYLE_NAME_H_
#define _STYLE_NAME_H_

enum NAME_FLAGS
{
	_11,
	_12,
	_21,
	_22,
	_122,
	_222,
	_0
};

enum SETNAME_FLAGS
{
    _single_surname,
    _double_surname,
    _single_name,
    _double_name
};

struct Word
{
	char w[2];
};

struct Fullname
{
	struct Word w[4];
};

class CStyle
{
private:
	int name_num;

	// 定义数据指针
	struct Word *surname = (struct Word *)buffer_surname_female;
	struct Word *name = (struct Word *)buffer_name_female;
	char *store_buffer[4];
	FILE *error_fp = NULL;

	// 单姓
	char *buffer_surname_female = {"赵钱孙李周吴郑王冯陈楮卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜戚谢邹喻柏水窦章云苏潘葛奚范彭郎鲁韦昌马苗凤花方俞任袁柳酆鲍史唐费廉岑薛雷贺倪汤滕殷罗毕郝邬安常乐于时傅皮卞齐康伍余元卜顾孟平黄和穆萧尹姚邵湛汪祁毛禹狄米贝明臧计伏成戴谈宋茅庞熊纪舒屈项祝董梁杜阮蓝闽席季麻强贾路娄危江童颜郭梅盛林刁锺徐丘骆高夏蔡田樊胡凌霍虞万支柯昝管卢莫经房裘缪干解应宗丁宣贲邓郁单杭洪包诸左石崔吉钮龚程嵇邢滑裴陆荣翁荀羊於惠甄麹家封芮羿储靳汲邴糜松井段富巫乌焦巴弓牧隗山谷车侯宓蓬全郗班仰秋仲伊宫宁仇栾暴甘斜厉戎祖武符刘景詹束龙叶幸司韶郜黎蓟薄印宿白怀蒲邰从鄂索咸籍赖卓蔺屠蒙池乔阴郁胥能苍双闻莘党翟谭贡劳逄姬申扶堵冉宰郦雍郤璩桑桂濮牛寿通边扈燕冀郏浦尚农温别庄晏柴瞿阎充慕连茹习宦艾鱼容向古易慎戈廖庾终暨居衡步都耿满弘匡国文寇广禄阙东欧殳沃利蔚越夔隆师巩厍聂晁勾敖融冷訾辛阚那简饶空曾毋沙乜养鞠须丰巢关蒯相查后荆红游竺权逑盖益桓公"};

	// 复姓,必须能够被2整除
	char *buffer_surname_female2 = {
		"司马南宫"
	};

	// 单名女
	char *buffer_name_female = {"一二三四五六七八九十嘉琼桂娣叶璧璐娅琦晶妍茜秋珊莎锦黛青倩婷姣婉娴瑾颖露瑶怡婵雁蓓纨仪荷丹蓉眉君琴蕊薇菁梦岚苑婕馨瑗琰韵融园艺咏卿聪澜纯毓悦昭冰爽琬茗羽希宁欣飘育滢馥筠柔竹霭凝晓欢霄枫芸菲寒伊亚宜可姬舒影荔枝思丽秀娟英华慧巧美娜静淑惠珠翠雅芝玉萍红娥玲芬芳燕彩春菊勤珍贞莉兰凤洁梅琳素云莲真环雪荣爱妹霞香月莺媛艳筠柔竹霭凝晓欢霄枫芸菲寒伊亚宜可姬舒影荔枝思丽秀娟英华慧巧美娜静淑惠珠翠雅芝玉萍红娥玲芬芳燕彩春菊勤珍贞莉兰凤洁梅琳素云莲真环雪荣爱妹霞香月莺媛艳瑞凡佳嘉琼桂娣叶璧璐娅琦晶妍茜秋珊莎锦黛青倩婷姣婉娴瑾颖露瑶怡婵雁蓓纨仪荷丹蓉眉君琴蕊薇菁梦岚苑婕馨瑗琰韵融园艺咏卿聪澜纯毓悦昭冰爽琬茗羽希宁欣飘育滢馥楠"};

	// 双名女,必须能够被2整除
	char *buffer_name_female2 = {
		"一二三四五六"
	};

	// 单名男
	char *buffer_name_male = {"一二三四五六七八九十瑞凡佳涛昌进林有坚和彪博诚先敬震振壮会群豪心邦承乐绍功松善厚庆磊民友裕河哲江超浩亮政谦亨奇固之轮翰朗伯宏言若鸣朋斌梁栋维启克伦翔旭鹏泽晨辰士以建家致树炎德行时泰盛雄琛钧冠策腾伟刚勇毅俊峰强军平保东文辉力明永健世广志义兴良海山仁波宁贵福生龙元全国胜学祥才发成康星光天达安岩中茂武新利清飞彬富顺信子杰楠榕风航弘"};



	int _fullname(struct Fullname *fn);
	int _fullname2(struct Fullname *fn);
	int _fullname22(struct Fullname *fn);
	int _full2name(struct Fullname *fn);
	int _full2name2(struct Fullname *fn);
	int _full2name22(struct Fullname *fn);

public:
    struct Fullname *list;

	CStyle(const int _name_num = 1);
	CStyle(const CStyle &cs);
	~CStyle();

	int print(const struct Fullname *print);
	int create(struct Fullname *fn, NAME_FLAGS flags = _11);
	int set_buffer(const char *src, SETNAME_FLAGS flags = _single_surname);
	int rest_buffer(SETNAME_FLAGS flags);

	// 错误处理函数
	int open_error_file(const char *filename, FILE *fp = NULL);
	int write_error(const char *str, ...);
	int close_error_file(void);

    CStyle clone(void);
};

#endif
