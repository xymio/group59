
#include <iostream>
#include <string>
#include <cmath>
#include"SM3_op.h"
#include<Windows.h>
using namespace std;


int main() {//主函数
	string str;
	str = "202100460103ljx";
	cout << "输入消息为字符串: " + str << endl;
	cout << endl;


	DWORD start_time = GetTickCount();
	string paddingValue = padding(str);
	cout << "填充后的消息为：" << endl;
	
	for (int i = 0; i < paddingValue.size() / 64; i++) {
		for (int j = 0; j < 8; j++) {
			cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	
	string result = iteration(paddingValue);
	cout << "杂凑值：" << endl;
	for (int i = 0; i < 8; i++) {
		cout << result.substr(i * 8, 8) << "  ";
	}
	
	cout << endl;
	cout << endl;
	DWORD end_time = GetTickCount();
	cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;
	system("pause");
	return 0;
}
