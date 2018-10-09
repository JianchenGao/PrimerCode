#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int rw_file_test();
int main()
{

	cout << "default bool values: " << true << " " << false 
		<< "\nalpha bool values: " << boolalpha
		<< true << " " << false << endl;

	cout << noboolalpha << true << endl;
	cout << hexfloat << 1.1 << endl;
	cout << defaultfloat << 1.1 << endl;

	rw_file_test();
	cout << "hello word!" << endl;
}

int rw_file_test()
{
	//�Զ�д��ʽ���ļ��������嵽�ļ�β
	//�ļ�ģʽ�����μ�P286
	fstream inOut("copyOut.txt", fstream::ate | fstream::in | fstream::out);
	if (!inOut) {
		cerr << "Unable to open file!" << endl;
		return EXIT_FAILURE;
	}
	//inOut��ateģʽ�򿪣����һ��ʼ�Ͷ��嵽���ļ�β
	auto end_mark = inOut.tellg();	//��סԭ�ļ�βλ��
	inOut.seekg(0, fstream::beg);	//�ض�λ���ļ���ʼ
	size_t cnt = 0;	//�ֽ����ۼ���
	string line;	//���������е�ÿ��
	//������ȡ����������δ���������һ��ڶ�ȡԭ����
	while (inOut && inOut.tellg() != end_mark
		&& getline(inOut, line)) {
		cnt += line.size() + 1;	//��1��ʾ���з�
		auto mark = inOut.tellg();	//��ס��ȡλ��
		inOut.seekp(0, fstream::end);	//��д����ƶ����ļ�β
		inOut << cnt;	//����ۼƵĳ���
		//����������һ�У���ӡһ���ָ���
		if (mark != end_mark) inOut << " ";
		inOut.seekg(mark);	//�ָ���λ��
	}
	inOut.seekp(0, fstream::end);	//��λ���ļ�β
	inOut << "\n";
	return 0;

}