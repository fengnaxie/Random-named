/*
**��������		Ϲ��������
**˵����		Ϲ����������һ��������ʹ�ã�ʹ����������ع�
**�汾��		V0.1
**�������ڣ�	2016/4/20
**�޸����ڣ�	2016/4/20
**���ߣ�		���
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

class _CFullname
{
public:
    virtual int random(void) = 0;
};

class CStyle : public _CFullname
{
private:
	int name_num;

	// ��������ָ��
	struct Word *surname = (struct Word *)buffer_surname_female;
	struct Word *name = (struct Word *)buffer_name_female;
	char* store_buffer[4];
	FILE* error_fp = NULL;
	struct Fullname *list;

	// ����
	char *buffer_surname_female = {"��Ǯ��������֣��������������������������ʩ�ſײ��ϻ���κ�ս���л������ˮ��������˸��ɷ�����³Τ������ﻨ������Ԭ��ۺ��ʷ�Ʒ����Ѧ�׺����������ޱϺ�����������ʱ��Ƥ���뿵����Ԫ������ƽ�ƺ�������Ҧ��տ����ë����ױ���갼Ʒ��ɴ�̸��é���ܼ�������ף������������ϯ����ǿ��·¦Σ��ͯ�չ�÷ʢ�ֵ�����������Ĳ��﷮���������֧���ù�¬Ī�������Ѹɽ�Ӧ�ڶ����ڵ��������������ʯ�޼�ť�������ϻ���½��������춻����L�ҷ����ഢ���������ɾ��θ����ڽ��͹�����ɽ�ȳ������ȫۭ�����������������ﱩ��б�������������ղ����Ҷ��˾��۬�輻��ӡ�ް׻���ۢ�Ӷ����̼���׿�����ɳ����������ܲ�˫��ݷ����̷�����̼������Ƚ��۪Ӻ�S�ɣ���ţ��ͨ�����༽ۣ����ũ�±�ׯ�̲����ֳ�Ľ����ϰ�°���������������������߾Ӻⲽ�����������Ŀܹ�»�ڶ�ŷ�����εԽ��¡ʦ�������˹��������������Ǽ��Ŀ�����ɳؿ������ᳲ�������󾣺�����Ȩ�ϸ��滸��"};

	// ����,�����ܹ���2����
	char *buffer_surname_female2 = {
		"˾���Ϲ�"
	};

	// ����Ů
	char *buffer_name_female = {"һ�����������߰˾�ʮ������Ҷ�������������ɺɯ������ٻ�������ӱ¶������������Ǻɵ���ü������ޱݼ���Է�ܰ�������԰��ӽ�������ع���ѱ�ˬ������ϣ����Ʈ�����������������������ܿ�ƺ������˿ɼ���Ӱ��֦˼�����Ӣ���������Ⱦ���������֥��Ƽ�����ҷ���ʴ����������������÷���������滷ѩ�ٰ���ϼ����ݺ����������������������ܿ�ƺ������˿ɼ���Ӱ��֦˼�����Ӣ���������Ⱦ���������֥��Ƽ�����ҷ���ʴ����������������÷���������滷ѩ�ٰ���ϼ����ݺ�����𷲼Ѽ�����Ҷ�������������ɺɯ������ٻ�������ӱ¶������������Ǻɵ���ü������ޱݼ���Է�ܰ�������԰��ӽ�������ع���ѱ�ˬ������ϣ����Ʈ������"};

	// ˫��Ů,�����ܹ���2����
	char *buffer_name_female2 = {
		"һ����������"
	};

	// ������
	const char *buffer_name_male = {"һ�����������߰˾�ʮ�𷲼��β������м�ͱ벩���Ⱦ�����׳��Ⱥ���İ�����ܹ����ƺ���������ԣ���ܽ���������ǫ�����֮�ֺ��ʲ����������������ά�������������󳿳�ʿ�Խ��������׵���ʱ̩ʢ��衾��ڲ���ΰ�����㿡��ǿ��ƽ�����Ļ�������������־��������ɽ�ʲ���������Ԫȫ��ʤѧ��ŷ��ɿ��ǹ���ﰲ����ï��������ɱ�˳���ӽ���ŷ纽��"};

	char *_fullname(struct Fullname *fn);
	char *_fullname2(struct Fullname *fn);
	char *_fullname22(struct Fullname *fn);
	char *_full2name(struct Fullname *fn);
	char *_full2name2(struct Fullname *fn);
	char *_full2name22(struct Fullname *fn);

    char *fullToString(const struct Fullname *fn);

public:
	CStyle(const int _name_num = -1);
	CStyle(const CStyle &cs);
	~CStyle();

	virtual char *create(const int index = -1, NAME_FLAGS flags = _0);
	int set_buffer(const char *src, SETNAME_FLAGS flags = _single_surname);
	int rest_buffer(SETNAME_FLAGS flags);
	int print(const int index = -1);

	int insert(NAME_FLAGS flags = _0);
	int del(const int index);

	char *get_all_fullname(void);
	int get_name_num(void);

	// ��������
	int open_error_file(const char *filename, FILE *fp = NULL);
	int write_error(const char *str, ...);
	int close_error_file(void);

	int random(void);

    CStyle clone(void);
};

#endif
