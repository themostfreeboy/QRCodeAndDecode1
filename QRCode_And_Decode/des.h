/*
des�㷨���ܽ���
Electronic Codebook (ECB)ģʽ
��Ϣ���ģʽ��PKCS5Padding(88888888 @7777777 @@666666 @@@55555 @@@@4444 @@@@@333 @@@@@@22 @@@@@@@1)
�ܳ״���ģʽ������MD5�㷨
*/

#pragma once

#ifndef __DES_H
#define __DES_H

#include <stdio.h>
#include "md5.h"

/*�û���*/

//������ִ��IP�û��õ�L0,R0 ��L��32λ,R��32λ��               [���Ĳ���]
const unsigned char IP_Table[64]={             
	58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
	62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
	57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
	61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7 
};

//�Ե������L16,R16ִ��IP���û�,�������
const unsigned char IPR_Table[64]={              
	40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25	
};

/*--------------------------- �������� ----------------------------*/ 

//F����,32λ��R0����E�任,��Ϊ48λ��� (R1~R16)        [����A]  [���Ĳ���]
const unsigned char E_Table[48]={
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13,12,13,14,15,16,17,
    16,17,18,19,20,21,20,21,22,23,24,25,
    24,25,26,27,28,29,28,29,30,31,32, 1
};

//����ԿK(i)�Ļ�ȡ ��ԿΪK ������6,16,24,32,40,48,64λ          [��Կ����]
//��PC1ѡλ ��Ϊ ǰ28λC0,��28λD0 ������
const unsigned char PC1_Table[56]={
	57,49,41,33,25,17, 9, 1,58,50,42,34,26,18,
	10, 2,59,51,43,35,27,19,11, 3,60,52,44,36,
	63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
	14, 6,61,53,45,37,29,21,13, 5,28,20,12, 4
};

//��C0,D0�ֱ��������,��16��,����λ���������Ӧ                 [��Կ����]
const unsigned char Move_Table[16]={
	 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

//C1,D1Ϊ��һ�����ƺ�õ�,����PC2ѡλ,�õ�48λ���K1   [����B]   [��Կ����]  
const unsigned char PC2_Table[48]={
	14,17,11,24, 1, 5, 3,28,15, 6,21,10,
	23,19,12, 4,26, 8,16, 7,27,20,13, 2,
	41,52,31,37,47,55,30,40,51,34,33,48,
	44,49,39,56,34,53,46,42,50,36,29,32	
};

/*------------- F���� ����A�ͱ���B ��� �õ�48λ��� ---------------*/ 

//����Ľ��48λ��Ϊ8��,ÿ��6λ,��Ϊ8��S�е�����             [��ϲ���]
//S����6λ��Ϊ����(8��),4λ��Ϊ���(4*(8��)=32λ)
//S����ԭ�� ��������ΪA=abcdef ,��bcde�����������0-15֮���
//һ������Ϊ X=bcde ,af�������0-3֮���һ����,��Ϊ Y=af
//��S1��X��,Y���ҵ�һ����Value,����0-15֮��,�����ö����Ʊ�ʾ
//����Ϊ4bit (��32λ)
const unsigned char S_Box[8][4][16]={
	//S1
	14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
	 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
	 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,
	//S2
	15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
	 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
	 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
	13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,
	//S3
	10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
	13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
	 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,
	//S4
	 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
	13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
	10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
	 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,
	//S5
	 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
	14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
	 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
	11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,
	//S6
	12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
	10,15, 4, 2, 7,12, 0, 5, 6, 1,13,14, 0,11, 3, 8,
	 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
   	 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,
	//S7
	 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
	13, 0,11, 7, 4, 0, 1,10,14, 3, 5,12, 2,15, 8, 6,
	 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
	 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,
	//S8
	13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
	 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
	 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
	 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
};

//F���� ���ڶ���,��S�������32����P�û�                     [��ϲ���]
//�����ֵ����һ�ε���:
//L(i)=R(i-1)
//R(i)=L(i-1)^f(R(i-1),K(i)) ���
const unsigned char P_Table[32]={
	16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
	 2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
};

/*��������*/
void BitsCopy(bool *DatOut,const bool *DatIn,int Len);//���鸴��

void ByteToBit(bool *DatOut,const unsigned char *DatIn,int Num);//�ֽڵ�λ
void BitToByte(unsigned char *DatOut,const bool *DatIn,int Num);//λ���ֽ�

void BitToHex(unsigned char *DatOut,const bool *DatIn,int Num);//�����Ƶ�ʮ������ 64λ to 4*16�ַ�
void HexToBit(bool *DatOut,const unsigned char *DatIn,int Num);//ʮ�����Ƶ�������

void TablePermute(bool *DatOut,const bool *DatIn,const unsigned char *Table,int Num);//λ���û�����
void LoopMove(bool *DatIn,int Len,int Num);//ѭ������ Len���� Num�ƶ�λ��
void Xor(bool *DatA,const bool *DatB,int Num);// �����

void S_Change(bool DatOut[32],const bool DatIn[48]);//S�б任
void F_Change(bool DatIn[32],const bool DatKi[48]);//F����                                

void SetKey(unsigned char KeyIn[8],bool SubKey[16][48]);//������Կ
void PlayDes(unsigned char MesOut[8],const unsigned char MesIn[8],bool SubKey[16][48]);//ִ��DES����
void KickDes(unsigned char MesOut[8],const unsigned char MesIn[8],bool SubKey[16][48]);//ִ��DES����

void des_code_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char coded_message[8]);//des�㷨����(��Ϣ���ܳ׾���64λ)
void des_decode_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char decoded_message[8]);//des�㷨����(��Ϣ���ܳ׾���64λ)
void des_print(const unsigned char* message, int length);//��16������ʽ��ʾ���ܺ����ܺ����Ϣ
int des_code_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* coded_message, long* coded_message_length);//des�㷨����(�����г���������Ϣ)
int des_decode_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* decoded_message, long* decoded_message_length);//des�㷨����(�����г���������Ϣ)
int des_code_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* coded_filename);//des�㷨����(�����д�С�ļ�����)
int des_decode_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* decoded_filename);//des�㷨�ӽ���(�����д�С�ļ�����)
long des_MyGetFileSize(const char* filename);//��ȡ�ļ���С�����ô˺���ʱ���ļ����봦��δ�򿪶�д״̬

#endif