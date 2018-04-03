#pragma once

#ifndef __FLAG_H
#define __FLAG_H

#include <stdio.h>

/*
��������ֵ˵����
1��д���־��У���־�ɹ�
-1��У���־ʧ��
-2��readfilename�ļ���ʧ��
-3��writefilename�ļ���ʧ��
*/

int WriteFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1);//д��һ��ASC2�����ַ��ı�־
int CheckFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1);//У��һ��ASC2�����ַ��ı�־
int WriteFlag_One_Int(const char* readfilename, const char* writefilename, int int_1);//д��һ�������ı�־
int CheckFlag_One_Int(const char* readfilename, const char* writefilename, int int_1);//У��һ�������ı�־

int WriteFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2);//д������ASC2�����ַ��ı�־
int CheckFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2);//У������ASC2�����ַ��ı�־
int WriteFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2);//д�����������ı�־
int CheckFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2);//У�����������ı�־

int WriteFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3);//д������ASC2�����ַ��ı�־
int CheckFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3);//У������ASC2�����ַ��ı�־
int WriteFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3);//д�����������ı�־
int CheckFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3);//У�����������ı�־

int WriteFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[]);//д��number��ASC2�����ַ��ı�־
int CheckFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[]);//У��number��ASC2�����ַ��ı�־
int WriteFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[]);//д��number�������ı�־
int CheckFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[]);//У��number�������ı�־

#endif