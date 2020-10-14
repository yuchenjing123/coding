#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define max_input 4

/*
brif:
	1.pair is a struct 
	2.pair have two mumber 
	3.the mumber of pair can visited by first and second
*/
void process(vector< pair< string , int >  >* pVector);
typedef void(*pFun)(vector< pair< string , int >  >*);  //声明函数指针类型，注意是类型

int main()
{
	pair<string,int> v_pair;
	v_pair = make_pair("test",1);
	cout<< v_pair.first <<" "<< v_pair.second << endl;

	//pair set relized by vector
	
	vector< pair< string , int >  >* pVector;
	vector< pair< string , int >  > pair_set;
	pVector = &pair_set;

	int arr[max_input]={0 , -6, 6, 0};

	for(int i =0 ; i < max_input ; i++)
	{
		if(i <= 2)
		{	// "\" 用于连接上下行
			arr[i] == 0 ? ((*pVector).push_back(make_pair("arr[0]",i)) ) :\
			  (arr[i]>0) ? ((*pVector).push_back(make_pair("arr[+]",i))) :\
				((*pVector).push_back(make_pair("arr[-]",i)));
		}
		else if(i == 3)
		{
			(*pVector).push_back(make_pair("arr[0]",i));
		}
	}
	//process(pVector);		//直接通过函数调用
	pFun p= process;  //用函数指针类型声明变量
	p(pVector);

	return 0;
}


void process(vector< pair< string , int >  >* pVector)
{
	vector< pair<string, int> >::iterator ite = (*pVector).begin();
	while(ite != ((*pVector).end()))
	{	
		cout << (*ite).first  << "  " << (*ite).second << endl;
		ite++;
	}
}