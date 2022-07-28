#include <iostream>   
#include <thread>
#include <future>
using namespace std;

void f(int i)
{
	cout << i << endl;
}

int main() 
{
	//��C11���������̣߳�һ����������ô�õģ�
	thread thr(f, 10);
	thr.join();

	//���ǣ��������Ҫ����̷߳��ص������أ���û���쵽��
	//��C11���ṩ������ĸ��̵߳����Ƶ��첽�ӿ�:std::async,
	//std::async���Զ�����һ���߳�ȥ�����̺߳�����������һ��std::future�����future�д洢���̺߳������صĽ��
	//�ڽ���async�����÷��Լ�ΪʲôҪ��std::async�����̵߳Ĵ���֮ǰ
	//������˵һ˵std::future��std::promise��std::packaged_task

	//std::futureα����
	//deferred���첽������û��ʼ
	//ready���첽�����Ѿ����
	//timeout���첽������ʱ
	//std::future_status status;
	//do {
	//	status = future.wait_for(std::chrono::seconds(1));
	//	if (status == std::future_status::deferred) {
	//		std::cout << "deferred\n";
	//	}
	//	else if (status == std::future_status::timeout) {
	//		std::cout << "timeout\n";
	//	}
	//	else if (status == std::future_status::ready) {
	//		std::cout << "ready!\n";
	//	}
	//} while (status != std::future_status::ready);

	//std::promise
	//std::promiseΪ��ȡ�̺߳����е�ĳ��ֵ�ṩ���������̺߳����и����洫������promise��ֵ
	//���̺߳���ִ�����֮��Ϳ���ͨ��promis��ȡ��ֵ��
	//ֵ��ע�����ȡֵ�Ǽ�ӵ�ͨ��promise�ڲ��ṩ��future����ȡ�ģ����Ļ����÷���
	//std::promise<int> pr;
	//std::thread t([](std::promise<int>& p){ p.set_value_at_thread_exit(9); }, std::ref(pr));
	//std::future<int> f = pr.get_future();
	//auto r = f.get();

	//std::packaged_task
	//std::packaged_task����װ��һ���ɵ��õ�Ŀ��(��function, lambda expression, bind expression,or another function object) 
	//�Ա��첽���ã�����promise��ĳ�̶ֳ����е���promise������һ������״̬��ֵ
	//��packaged_task�������һ�����������Ļ����÷���
	//std::packaged_task<int()> task([](){ return 7; });
	//std::thread t1(std::ref(task));
	//std::future<int> f1 = task.get_future();
	//auto r1 = f1.get();

	//���������ߵĹ�ϵ��������:std::future�ṩ��һ�������첽��������Ļ��ƣ������߳���һ����������ڵͲ�εĶ���
	//����֮�ϸ�һ�����std::packaged_task��std::promise�������ڲ�����future�Ա�����첽�������
	//std::packaged_task��װ����һ���첽��������std::promise��װ����һ��ֵ������Ϊ�˷����첽������
	//��Ϊ��ʱ����Ҫ��ȡ�߳��е�ĳ��ֵ����ʱ����std::promise
	//����ʱ����Ҫ��һ���첽�����ķ���ֵ����ʱ����std::packaged_task

	//�������������÷���
	//std::launch::async���ڵ���async�Ϳ�ʼ�����̡߳�
	//std::launch::deferred���ӳټ��ط�ʽ�����̡߳�����asyncʱ�������̣߳�ֱ��������future��get����waitʱ�Ŵ����̡߳�
	std::future<int> f1 = std::async(std::launch::async, [](){
		return 8;
	});

	cout << f1.get() << endl; //output: 8

	std::future<void> f2 = std::async(std::launch::deferred, [](){
		cout << 8 << endl;
	});

	f2.wait(); //output: 8

	std::future<int> future = std::async(std::launch::async, [](){
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "waiting...\n";
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout\n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!\n";
		}
	} while (status != std::future_status::ready);

	std::cout << "result is " << future.get() << '\n';

	std::getchar();
	return 0;
}