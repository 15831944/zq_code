#ifndef _COMPRESS_H_
#define _COMPRESS_H_

//���p2Ϊ0���򱾺�����ͨ��len2����ѹ��֮����ڴ����ֽ���
//���p2��Ϊ���򱾺����Ὣѹ��֮������ݷ��뵽p2ָ����ڴ���
void RLE_Compress(const void* p1, //������ڴ�
				  int len1, //������ڴ����ֽ���
				  void* p2, //������ڴ�
				  int* len2); //������ڴ����ֽ���

#endif