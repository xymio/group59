

#include <iostream>
#include <windows.h>

#include"AES.h";

using namespace std;
string gen_key()
{
	string str;
	int c;


	for (int i = 0; i < 16; i++)
	{

		c = rand() % 9;
		str += to_string(c);
	}
	return str;
}

void AES_TimeTest()
{

	DWORD Start, End;


	string n = "89891481487171262618718701117174242252252193193129129898924624620420411611618018024524517171851851521520662182188989179179202202245245169169193193115115202202207207197197";
	Start = GetTickCount();
	string k = gen_key();
	End = GetTickCount();

	cout << "AES密钥生成时间：" << End - Start << "ms" << endl;

	Start = GetTickCount();
	string a = AES_enc(n, k);
	End = GetTickCount();
	cout << "AES加密时间：" << End - Start << "ms" << endl;

	Start = GetTickCount();
	string b = AES_enc(a,k);
	End = GetTickCount();

	cout << "AES解密时间：" << End - Start << "ms" << endl;

}

int main()
{
	
	AES_TimeTest();
	return 0;


}
