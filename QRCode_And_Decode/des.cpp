#include "des.h"

#include "stdafx.h"

/*-------------------------------
 ��DatIn��ʼ�ĳ���λLenλ�Ķ�����
 ���Ƶ�DatOut��
--------------------------------*/
void BitsCopy(bool *DatOut,bool *DatIn,int Len)//���鸴�� OK 
{
	int i=0;
	for(i=0;i<Len;i++)
	{
		DatOut[i]=DatIn[i];
	}
}

/*-------------------------------
 �ֽ�ת����λ���� 
 ÿ8�λ�һ���ֽ� ÿ��������һλ
 ��1��ȡ���һλ ��64λ 
--------------------------------*/
void ByteToBit(bool *DatOut,const unsigned char *DatIn,int Num)//OK
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=(DatIn[i/8]>>(i%8))&0x01;   
	}                                       
}

/*-------------------------------
 λת�����ֽں���
 �ֽ�����ÿ8����һλ
 λÿ�������� ����һ�λ�   
---------------------------------*/
void BitToByte(unsigned char *DatOut,const bool *DatIn,int Num)//OK
{
	int i=0;
	for(i=0;i<(Num/8);i++)
	{
		DatOut[i]=0;
	} 
	for(i=0;i<Num;i++)
	{
		DatOut[i/8]|=DatIn[i]<<(i%8);	
	}		
}


/*----------------------------------
 ����������ת��Ϊʮ������
 ��Ҫ8���ַ���ʾ
-----------------------------------*/
void BitToHex(unsigned char *DatOut,const bool *DatIn,int Num)
{
	int i=0;
	for(i=0;i<Num/8;i++)
	{
		DatOut[i]=0;
	}
	for(i=0;i<Num/8;i++)
	{
		DatOut[i] = DatIn[i*8]+(DatIn[i*8+1]<<1)+(DatIn[i*8+2]<<2)+(DatIn[i*8+3]<<3)+(DatIn[i*8+4]<<4)+(DatIn[i*8+5]<<5)+(DatIn[i*8+6]<<6)+(DatIn[i*8+7]<<7);
	}
}

/*---------------------------------------------
 ʮ�������ַ�ת������
----------------------------------------------*/
void HexToBit(bool *DatOut,const unsigned char *DatIn,int Num)
{
	int i=0; 
	for(i=0;i<Num;i++)
	{
		DatOut[i]=((DatIn[i/8])>>(i%8))&0x01;   			
	}	
}

//���û�����  OK
void TablePermute(bool *DatOut,const bool *DatIn,const unsigned char *Table,int Num)  
{
	int i=0;
	bool Temp[256]={0};
	for(i=0;i<Num;i++)//NumΪ�û��ĳ��� 
	{
		Temp[i]=DatIn[Table[i]-1];//ԭ�������ݰ���Ӧ�ı��ϵ�λ������ 
	}
	BitsCopy(DatOut,Temp,Num);//�ѻ���Temp��ֵ��� 
} 

//����Կ����λ
void LoopMove(bool *DatIn,int Len,int Num)//ѭ������ Len���ݳ��� Num�ƶ�λ��
{
	bool Temp[256]={0};//����   OK
	BitsCopy(Temp,DatIn,Num);//����������ߵ�Numλ(���Ƴ�ȥ��)����Temp 
	BitsCopy(DatIn,DatIn+Num,Len-Num);//��������߿�ʼ�ĵ�Num����ԭ���Ŀռ�
	BitsCopy(DatIn+Len-Num,Temp,Num); //���������Ƴ�ȥ�����ݼӵ����ұ� 
} 

//��λ���
void Xor(bool *DatA,const bool *DatB,int Num)//�����
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatA[i]=DatA[i]^DatB[i];//��� 
	}
} 

//����48λ ���32λ ��Ri���
void S_Change(bool DatOut[32],const bool DatIn[48])//S�б任
{
	int i,X,Y;//iΪ8��S�� 
	for(i=0,Y=0,X=0;i<8;i++,DatIn+=6,DatOut+=4)//ÿִ��һ��,��������ƫ��6λ 
	{    									   //ÿִ��һ��,�������ƫ��4λ
		Y=(DatIn[0]<<1)+DatIn[5];//af����ڼ���
		X=(DatIn[1]<<3)+(DatIn[2]<<2)+(DatIn[3]<<1)+DatIn[4];//bcde����ڼ���
		ByteToBit(DatOut,&S_Box[i][Y][X],4);//���ҵ��ĵ����ݻ�Ϊ������	
	}
}

//F����
void F_Change(bool DatIn[32],const bool DatKi[48])//F����
{
	bool MiR[48]={0};//����32λͨ��Eѡλ��Ϊ48λ
	TablePermute(MiR,DatIn,E_Table,48); 
	Xor(MiR,DatKi,48);//������Կ���
	S_Change(DatIn,MiR);//S�б任
	TablePermute(DatIn,DatIn,P_Table,32);//P�û������
}

void SetKey(unsigned char KeyIn[8],bool SubKey[16][48])//������Կ ��ȡ����ԿKi 
{
	int i=0;
	bool KeyBit[64]={0};//��Կ�����ƴ洢�ռ� 
	bool *KiL=&KeyBit[0],*KiR=&KeyBit[28];//ǰ28,��28��56
	ByteToBit(KeyBit,KeyIn,64);//����ԿתΪ�����ƴ���KeyBit 
	TablePermute(KeyBit,KeyBit,PC1_Table,56);//PC1���û� 56��
	for(i=0;i<16;i++)
	{
		LoopMove(KiL,28,Move_Table[i]);//ǰ28λ���� 
		LoopMove(KiR,28,Move_Table[i]);//��28λ���� 
	 	TablePermute(SubKey[i],KeyBit,PC2_Table,48); 
	 	//��ά���� SubKey[i]Ϊÿһ����ʼ��ַ 
	 	//ÿ��һ��λ����PC2�û��� Ki 48λ 
	}		
}

void PlayDes(unsigned char MesOut[8],const unsigned char MesIn[8],bool SubKey[16][48])//ִ��DES����
{                                           //�ֽ����� Bin���� Hex��� 
	int i=0;
	bool MesBit[64]={0};//���Ķ����ƴ洢�ռ� 64λ
	bool Temp[32]={0};
	bool *MiL=&MesBit[0],*MiR=&MesBit[32];//ǰ32λ ��32λ 
	ByteToBit(MesBit,MesIn,64);//�����Ļ��ɶ����ƴ���MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);//IP�û� 
	for(i=0;i<16;i++)//����16�� 
	{
		BitsCopy(Temp,MiR,32);//��ʱ�洢
		F_Change(MiR,SubKey[i]);//F�����任
		Xor(MiR,MiL,32);//�õ�Ri 
		BitsCopy(MiL,Temp,32);//�õ�Li 
	}					
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToHex(MesOut,MesBit,64);
}

void KickDes(unsigned char MesOut[8],const unsigned char MesIn[8], bool SubKey[16][48])//ִ��DES����
{												//Hex���� Bin���� �ֽ���� 
	int i=0;
	bool MesBit[64]={0};//���Ķ����ƴ洢�ռ� 64λ
	bool Temp[32]={0};
	bool *MiL=&MesBit[0],*MiR=&MesBit[32];//ǰ32λ ��32λ
	HexToBit(MesBit,MesIn,64);//�����Ļ��ɶ����ƴ���MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);//IP�û� 
	for(i=15;i>=0;i--)
	{
		BitsCopy(Temp,MiL,32);
		F_Change(MiL,SubKey[i]);
		Xor(MiL,MiR,32);
		BitsCopy(MiR,Temp,32);
	}	
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToByte(MesOut,MesBit,64);		
}

void des_code_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char coded_message[8])//des�㷨����(��Ϣ���ܳ׾���64λ)
{
	unsigned char set_key[8];
	for(int i=0;i<8;i++)
	{
		set_key[i]=key[i];
	}

    bool SubKey[16][48]={0};//16������ԿK(1~16)
	SetKey(set_key,SubKey);//������Կ �õ�����ԿKi
	PlayDes(coded_message,origin_message,SubKey);//ִ��DES����
}

void des_decode_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char decoded_message[8])//des�㷨����(��Ϣ���ܳ׾���64λ)
{
	unsigned char set_key[8];
	for(int i=0;i<8;i++)
	{
		set_key[i]=key[i];
	}

	bool SubKey[16][48]={0};//16������ԿK(1~16)
	SetKey(set_key,SubKey);//������Կ
	KickDes(decoded_message,origin_message,SubKey);//���������decoded_message
}

void des_print(const unsigned char* message, int length)//��16������ʽ��ʾ���ܺ����ܺ����Ϣ
{
	printf("des:");
	for (int i = 0; i < length; i++)
	{
		printf("%02x ", message[i]);
	}
	printf("\n");
}

int des_code_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* coded_message, long* coded_message_length)//des�㷨����(�����г���������Ϣ)
{
	//��ԭ��Ϣ���в����ַ����
	*coded_message_length=(origin_message_length/8+1)*8;
	unsigned char origin_message_new[1000];
	for(int i=0;i<origin_message_length;i++)
	{
		origin_message_new[i]=origin_message[i];
	}
	for(int i=origin_message_length;i<*coded_message_length;i++)//�����ַ����
	{
		origin_message_new[i]=*coded_message_length-origin_message_length;
	}

	//ת��key��64λ(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//����ԭkey��md5ת��Ϊ128λ(16 byte)
	for(int i=0;i<8;i++)//��һ��ת��key��64λ(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	//����des�㷨����
	for(int i=0;i<*coded_message_length/8;i++)
	{
		des_code_for64bit((const unsigned char*)&(origin_message_new[8*i]),(const unsigned char*)key_new,&(coded_message[8*i]));
	}
	return 1;//���ܳɹ�
}

int des_decode_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* decoded_message, long* decoded_message_length)//des�㷨����(�����г���������Ϣ)
{
	//ת��key��64λ(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//����ԭkey��md5ת��Ϊ128λ(16 byte)
	for(int i=0;i<8;i++)//��һ��ת��key��64λ(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	if (origin_message_length%8!=0)//���������ݴ���
	{
		return -1;//���������ݴ���
	}

	//���岿�ֱ���
	unsigned char decoded_message_temp[1000];

	//����des�㷨����
	for(int i=0;i<origin_message_length/8;i++)
	{
		des_decode_for64bit((const unsigned char*)&(origin_message[8*i]),(const unsigned char*)key_new,&(decoded_message_temp[8*i]));
	}
	
	//ȥ������ʱ������ַ�
	*decoded_message_length=origin_message_length-decoded_message_temp[origin_message_length-1];
	for(int i=0;i<*decoded_message_length;i++)
	{
		decoded_message[i]=decoded_message_temp[i];
	}
	return 1;//���ܳɹ�
}

int des_code_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* coded_filename)//des�㷨����(�����д�С�ļ�����)
{
	//���origin_filename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -1;//�ļ���ʧ��
	}
	fclose(fp_read);

	//origin_filename�ļ�����
	errno_t err_write;
	FILE *fp_write = NULL;

	//ת��key��64λ(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//����ԭkey��md5ת��Ϊ128λ(16 byte)
	for(int i=0;i<8;i++)//��һ��ת��key��64λ(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	long origin_filesize=des_MyGetFileSize(origin_filename);//��ȡԭ�ļ���С
	unsigned char temp_in[8];
	unsigned char temp_out[8];
	long read_time=origin_filesize/8+1;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -2;//�ļ���ʧ��
	}
	err_write = fopen_s(&fp_write, coded_filename, "wb");
	if (err_write != 0)
	{
		return -3;//�ļ���ʧ��
	}
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<8;j++)
		{
			fscanf(fp_read,"%c",&(temp_in[j]));
		}
		des_code_for64bit(temp_in,key_new,temp_out);
		for(int j=0;j<8;j++)
		{
			fprintf(fp_write,"%c",temp_out[j]);
		}
	}	
	for(int i=0;i<origin_filesize%8;i++)
	{
		fscanf(fp_read,"%c",&(temp_in[i]));
	}
	for(int i=origin_filesize%8;i<8;i++)
	{
		temp_in[i]=8-origin_filesize%8;
	}
	des_code_for64bit(temp_in,key_new,temp_out);
	for(int i=0;i<8;i++)
	{
		fprintf(fp_write,"%c",temp_out[i]);
	}
	fclose(fp_read);
	fclose(fp_write);
	return 1;//���ܳɹ�
}

int des_decode_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* decoded_filename)//des�㷨�ӽ���(�����д�С�ļ�����)
{
	//���origin_filename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -1;//�ļ���ʧ��
	}
	fclose(fp_read);

	//origin_filename�ļ�����
	errno_t err_write;
	FILE *fp_write = NULL;

	//ת��key��64λ(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//����ԭkey��md5ת��Ϊ128λ(16 byte)
	for(int i=0;i<8;i++)//��һ��ת��key��64λ(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	long origin_filesize=des_MyGetFileSize(origin_filename);//��ȡԭ�ļ���С
	if(origin_filesize%8!=0)//�������ļ�����
	{
		return -2;//�������ļ�����
	}
	unsigned char temp_in[8];
	unsigned char temp_out[8];
	long read_time=origin_filesize/8;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -3;//�ļ���ʧ��
	}
	err_write = fopen_s(&fp_write, decoded_filename, "wb");
	if (err_write != 0)
	{
		return -4;//�ļ���ʧ��
	}
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<8;j++)
		{
			fscanf(fp_read,"%c",&(temp_in[j]));
		}
		des_decode_for64bit(temp_in,key_new,temp_out);
		for(int j=0;j<8;j++)
		{
			fprintf(fp_write,"%c",temp_out[j]);
		}
	}
	for(int i=0;i<8;i++)
	{
		fscanf(fp_read,"%c",&(temp_in[i]));
	}
	des_decode_for64bit(temp_in,key_new,temp_out);
	for(int i=0;i<8-temp_out[7];i++)
	{
		fprintf(fp_write,"%c",temp_out[i]);
	}
	fclose(fp_read);
	fclose(fp_write);
	return 1;//���ܳɹ�
}

long des_MyGetFileSize(const char* filename)//��ȡ�ļ���С�����ô˺���ʱ���ļ����봦��δ�򿪶�д״̬
{
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp, filename, "rb");
	if (err != 0)
	{
		return -1;//�ļ���ʧ��
	}
    fseek(fp,0,SEEK_SET);
    fseek(fp,0,SEEK_END);
    long filesize=ftell(fp);
    rewind(fp);
	fclose(fp);
	return filesize;
}