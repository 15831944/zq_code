#ifndef _FIND_PATH_H_
#define _FIND_PATH_H_

//��ͼΪchar����,<=0Ϊ�ϰ�,>0Ϊͨ·

class CFindPath
{
	template <typename T>
	class CCSqList
	{
		int m_S;
		int m_L;
		T* m_P;
	public:
		CCSqList();
		~CCSqList();
		CCSqList(const CCSqList& that);
		CCSqList& operator = (const CCSqList& that);
		void Push(T d);
		bool Erase(int p);
		void Clear();
		T* Get(int p);
		int Length();
		T* Locate(T d, int b = 1);
	};

	//������
	static CCSqList<int> m_BeGone;
	static bool _FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen, CCSqList<int>* pBeGone);

	//������
	static CCSqList<int> m_F;
	static CCSqList<int> m_Z;
	static void Inverse(int* p, int c);

	//A�����
	struct _ASN
	{
		int f, z, g, h;
		bool operator == (const _ASN& that)
		{
			return z == that.z;
		}
	};
	static CCSqList<_ASN> m_Open;
	static CCSqList<_ASN> m_Close;
	static int _ABS(int i);
	static int _GetH(int i1, int i2, int w);
	static int _GetMinFIndex(CCSqList<_ASN>* m_pOpen);
	static void _GetChild(const char* map, int w, int h, const _ASN* f, int e, _ASN* child, int* childlen);

public:

	//����trueֵ���ҵ�·,·�����뵽pPath��,pPath����ӦΪ��ͼ��С
	//����false��δ�ҵ�·
	
	//4����(˳��Ϊ��������)
	static bool FindPathD(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);

	//4����
	static bool FindPathW(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);

	//8����
	static bool FindPathA(const char* map, int w, int h, int b, int e, int* pPath, int* pPathLen);
};

#endif