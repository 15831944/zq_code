#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int x = 1;
int y = 1;
auto add(int a, int b)->decltype(x * y)
{
	return a + b;
}

void main()
{
	//auto�Զ������ƶ�
	//auto�ؼ��������Ӻ�����ʽ�Զ��ɱ������ƶ�ǰ�����������

	//auto a��//����auto��ͨ����ʼ�����ʽ���������Ƶ������û�г�ʼ��
			  //���ʽ�����޷�ȷ��a������
	int b = 1;
	auto c = b;
	vector<int> v;
	auto it = v.begin();
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	//����forѭ��
	//����forѭ����������ظ�����һ�����У����������п������κο����ظ����������У�
	//����begin()��end()���������STL���С����еı�׼������������	
	//�������У�ͬʱ��Ҳͬ��������std::string����ʼ���б�list�������飬�Լ��κ���begin()��end()�������������
	for (auto i : v)
		cout << i << endl;

	map<string, int> m;
	
	m.insert(std::pair<string, int>("a", 1));
	m.insert(std::pair<string, int>("b", 2));
	m.insert(std::pair<string, int>("c", 3));

	for (auto i : m)
		cout << i.first << endl;

	int a[5] = {1,2,3,4,5};
	for (auto i : a)
		cout << i << endl;


	//�෴�أ�decltype��ͨ�����ʽ���������
	int a = 1;
	declytpe(a) b = 1;	//b����int������
	
	//����һ�־��Ǻ�����������
	//���������add����
	cout << add(10, 20) <<endl;

	system("pause");
}