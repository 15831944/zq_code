#include <iostream>
#include <chrono>
#include <typeinfo>
#include <ratio>
#include <ctime>
#include <iomanip>
using namespace std;
using namespace std::chrono;


int main()
{
	// һ.ʱ������
	// ratio��ʾһ��ʱ�����ڣ�����
	// std::chrono::duration<int, ratio<1, 1>> t1(10)
	// �ʹ���һ��ʱ������Ϊ10�룬������t1.count()���
	// ������Ĵ���ʵ�ֵľ����Ȼ��ϵͳ��ʱ��㣬Ȼ����һ��ʱ������
	// ת����ʱ��㣬Ȼ��time_since_epoch()�������19700101�����ʱ��㾭��
	// ��ʱ�����ڣ�����������������϶���һ����
	using days_type = std::chrono::duration<int, ratio<1, 1>>;
	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
	cout << today.time_since_epoch().count() << endl;
	cout << time(0) << endl;


	// ��.time_point��time_t���໥ת��
	// ʱ��㻹���Խ������㣬������������ǰһ��ͺ�һ��ĵ�����
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// typedef hours = std::chrono::duration<int, ratio<3600>>
	// system_clock::from_time_t��time_t��time_point��ת��
	time_t last = system_clock::to_time_t(now - hours(24));
	time_t next = system_clock::to_time_t(now + hours(24));
	// "%F %T" ���� %Y-%m-%d %X ���� %Y-%m-%d %H.%M.%S  
	cout << "last: " << std::put_time(std::localtime(&last), "%Y-%m-%d %X") << endl;
	cout << "next: " << std::put_time(std::localtime(&next), "%F %T") << endl;


	// ��.��ó������еļ��ʱ��
	// system_clock:��ʵ����Ĺ���ʱ�䣬����ʱ��������ϵͳ
	// steady_clock:���ܱ�������ʱ�ӣ���ȡ�ȶ���ʱ������������Ϊ�޸���ϵͳʱ����ı�
	// high_resolution_clock:�߾���ʱ�ӣ�ʵ������system_clock��steady_clock�ı���
	// ����3�����Ͷ�����ͨ��now()����õ�ǰ��ʱ���
	system_clock::time_point t1 = system_clock::now();
	cout << "hello world" << endl;
	system_clock::time_point t2 = system_clock::now();
	cout << (t2 - t1).count() << endl;
	cout << duration_cast<microseconds>(t2 - t1).count() << endl;
	cout << duration_cast<milliseconds>(t2 - t1).count() << endl;
	cout << duration_cast<seconds>(t2 - t1).count() << endl;
	
				/*std::chrono::system_clock::time_point now_nano = std::chrono::system_clock::now();
			INT64 score = std::chrono::duration_cast<std::chrono::nanoseconds>(now_nano.time_since_epoch()).count();*/
	
#ifdef WIN32
	system("pause");
#endif
	return 0;
}