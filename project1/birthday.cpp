
#include <iostream>
#include <string>
#include <cmath>
#include"SM3.h""

#include<Windows.h>
using namespace std;


#define max_num 65536
//查表
string inlist[max_num];
string hashset[max_num];

void birthday_attack() {
	string str;
	string result;
	string paddingValue;
	for (int i = 0; i < max_num; i++) {
		//cout << "目前进度：" << i << endl;
		str = to_string(i);
		inlist[i] = str;
		paddingValue = padding(str);
		result = iteration(paddingValue);

		hashset[i]=result;
		
		//查表寻找碰撞
		for (int j = 0; j < i; j++) {
			if (hashset[j].substr(0, 4) == result.substr(0, 4)) {
				cout << "birthday attack sucess！";
				cout << "collision string input 1 :" + str << endl << endl;
				cout << "collision hash value 1:" << endl;
				cout << result.substr(0, 8) << "  ";
				cout << result.substr(8, 8) << "  ";
				cout << result.substr(16, 8) << "  ";
				cout << result.substr(24, 8) << "  ";
				cout << result.substr(32, 8) << "  ";
				cout << result.substr(40, 8) << "  ";
				cout << result.substr(48, 8) << "  ";
				cout << result.substr(56, 8) << "  ";
				cout << endl;
				cout << "collision string input 2 :" + inlist[j] << endl << endl;
				cout << "collision hash value 2:" << endl;
				cout << hashset[j].substr(0, 8) << "  ";
				cout << hashset[j].substr(8, 8) << "  ";
				cout << hashset[j].substr(16, 8) << "  ";
				cout << hashset[j].substr(24, 8) << "  ";
				cout << hashset[j].substr(32, 8) << "  ";
				cout << hashset[j].substr(40, 8) << "  ";
				cout << hashset[j].substr(48, 8) << "  ";
				cout << hashset[j].substr(56, 8) << "  ";
				cout << endl << "finding num in all:  " << i;
				return;
			}
		}
	}
	cout << "birthday attack failed!";
}


int main()
{
	
	DWORD start_time = GetTickCount();
	birthday_attack();
	DWORD end_time = GetTickCount();
	cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;
	return 0;
}
