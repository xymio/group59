
#include <iostream>
#include <string>
#include <cmath>
#include"SM3.h""
#include<Windows.h>
using namespace std;


//������
#define max_num 65536
//���
string inlist[max_num];
string outlist[max_num];

void rho_attack() {
	string str;
	string result;
	string paddingValue;
	int start = 0;
	int rho = 0;
	for (int i = 0; i < max_num; outlist[i++] = result) {
		if (rho != -1) {
			rho = 2 * rho + 1;	//rho���Ʊ��ʽ	
		}
		else {
			//����int���ޣ���һ����ʼֵ���¿�ʼ
			rho = ++start;
		}
		cout << "Ŀǰ���ȣ�" << i << endl;
		str = to_string(rho);
		inlist[i] = str;
		paddingValue = padding(str);
		result = iteration(paddingValue);
		//���Ѱ������ײ
		for (int j = 0; j < i; j++) {
			if (outlist[j].substr(0, 4) == result.substr(0, 4) && str != inlist[j]) {
				cout << endl;
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
				cout << outlist[j].substr(0, 8) << "  ";
				cout << outlist[j].substr(8, 8) << "  ";
				cout << outlist[j].substr(16, 8) << "  ";
				cout << outlist[j].substr(24, 8) << "  ";
				cout << outlist[j].substr(32, 8) << "  ";
				cout << outlist[j].substr(40, 8) << "  ";
				cout << outlist[j].substr(48, 8) << "  ";
				cout << outlist[j].substr(56, 8) << "  ";
				cout << endl << "finding num in all:  " << i;
				return;
			}
		}
	}
	cout << "rho attack failed!";
}

int main() {

	DWORD start_time = GetTickCount();
	rho_attack();
	DWORD end_time = GetTickCount();
	cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;
	return 0;
	
	
}
