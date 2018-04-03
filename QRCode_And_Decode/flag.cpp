#include "flag.h"

#include "stdafx.h"

int WriteFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1)//д��һ��ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",char_1);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1)//У��һ��ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempchar_1;
	fscanf(fp_read,"%c",&tempchar_1);

	if(tempchar_1!=char_1)
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_One_Int(const char* readfilename, const char* writefilename, int int_1)//д��һ�������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_One_Int(const char* readfilename, const char* writefilename, int int_1)//У��һ�������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempInt_1;
	fscanf(fp_read,"%c",&tempInt_1);

	if(tempInt_1!=(int_1&(0xff)))
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2)//д������ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",char_1);
	fprintf(fp_write,"%c",char_2);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2)//У������ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempchar_1,tempchar_2;
	fscanf(fp_read,"%c%c",&tempchar_1,&tempchar_2);

	if(tempchar_1!=char_1 || tempchar_2!=char_2)
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2)//д�����������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));
	fprintf(fp_write,"%c",(int_2)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2)//У�����������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempInt_1,tempInt_2;
	fscanf(fp_read,"%c%c",&tempInt_1,&tempInt_2);

	if(tempInt_1!=(int_1&(0xff)) || tempInt_2!=(int_2&(0xff)))
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3)//д������ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",char_1);
	fprintf(fp_write,"%c",char_2);
	fprintf(fp_write,"%c",char_3);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3)//У������ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempchar_1,tempchar_2,tempchar_3;
	fscanf(fp_read,"%c%c%c",&tempchar_1,&tempchar_2,&tempchar_3);

	if(tempchar_1!=char_1 || tempchar_2!=char_2 || tempchar_3!=char_3)
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3)//д�����������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));
	fprintf(fp_write,"%c",(int_2)&(0xff));
	fprintf(fp_write,"%c",(int_3)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3)//У�����������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempInt_1,tempInt_2,tempInt_3;
	fscanf(fp_read,"%c%c%c",&tempInt_1,&tempInt_2,&tempInt_3);

	if(tempInt_1!=(int_1&(0xff)) || tempInt_2!=(int_2&(0xff)) || tempInt_3!=(int_3&(0xff)))
	{
		fclose(fp_read);
		return -1;//��־У��ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[])//д��number��ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	for(int i=0;i<number;i++)
	{
		fprintf(fp_write,"%c",char_Multi[i]);
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[])//У��number��ASC2�����ַ��ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempchar_Multi;
	for(int i=0;i<number;i++)
	{
		fscanf(fp_read,"%c",&tempchar_Multi);
		if(tempchar_Multi!=char_Multi[i])
	    {
		    fclose(fp_read);
		    return -1;//��־У��ʧ��
	    }
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}

int WriteFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[])//д��number�������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	for(int i=0;i<number;i++)
	{
		fprintf(fp_write,"%c",(int_Multi[i])&(0xff));
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־д��ɹ�
}

int CheckFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[])//У��number�������ı�־
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename�ļ���ʧ��
	}

	char tempInt_Multi;
	for(int i=0;i<number;i++)
	{
		fscanf(fp_read,"%c",&tempInt_Multi);
		if(tempInt_Multi!=int_Multi[i])
	    {
		    fclose(fp_read);
		    return -1;//��־У��ʧ��
	    }
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename�ļ���ʧ��
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//��־У��ɹ�
}