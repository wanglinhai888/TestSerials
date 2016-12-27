// TestSerials.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Serialize.h"

using namespace std;
struct MyStruct
{
public:
	void toString(string &str)
	{
		CSerialize serial;
		serial << a << b << _char << str1 << vec_ini << vec_vec_int;
		str = serial.buffer();
	}

	void unString(const string &str)
	{
		CSerialize serial(str);
		serial >> a >> b >> _char >> str1 >> vec_ini >> vec_vec_int;
	}

	//打印
	void print()
	{
		cout << "-----------------------------------------" << endl;
		cout << "a:" << a << endl;
		cout << "b:" << b << endl;
		cout << "_char: " << _char << endl;
		cout << "str: " << str1 << endl;
		cout << "vec_ini" << endl;
		for ( auto i = vec_ini.begin(); i != vec_ini.end(); i++ )
		{
			cout << *i << endl;
		}
		cout << "vec_vec_int " << endl;
		for each ( auto var in vec_vec_int )
		{
			for each ( auto i in var )
			{
				cout << i << endl;
			}
		}
	    cout << "-----------------------------------------"<<endl;
        
	}
public:
	int a;
	int b;
	char  _char;
	string str1 ;
	vector<int> vec_ini;
	vector<vector<int>> vec_vec_int;
};


int _tmain(int argc, _TCHAR* argv[])
{

	MyStruct test;
	test.a = 1;
	test.b = 2;
	test._char = 'c';
	test.str1 = "fafafasf";
	test.vec_ini.push_back(1);
	test.vec_ini.push_back(2);
	test.vec_vec_int.push_back(test.vec_ini);
	test.vec_vec_int.push_back(test.vec_ini);
	test.print();
	string str;
	test.toString(str);

//--------------------------------------------------------------------------------------------
	MyStruct test1;
	test1.unString(str);
	test1.print();
	getchar();
	return 0; 
}

