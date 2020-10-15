
#include <map>
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
void process(map<string, int>* pmap);
typedef void(*pFun)(map<string, int>* pmap);  //声明函数指针类型，注意是类型

int main()
{
	map<string,int> v_map;
	map<string,int>* pMap;
	pMap = &v_map;
	int arr[max_input] = {0,-6,6,0};
	for(int i =0 ;i < max_input ; i++)
	{
		if(i<=2)
		{
			arr[i] == 0 ? ((*pMap)["arr[0]"] = i) :\
			  (arr[i]>0) ? ((*pMap)["arr[+]"] = i) :\
				(((*pMap)["arr[-]"] = i));
		}
		else if(i == 3)
		{
			(*pMap)["brightening"] = i;
		}
	}

	pFun p= process;  //用函数指针类型声明变量
	p(pMap);

	return 0;
}


void process(map<string, int>* pmap)
{
	map<string,int>::iterator ite = (*pmap).begin();
	while(ite != (*pmap).end())
	{
		cout<< (*ite).first <<" "<< (*ite).second << endl;
		ite++;
	}
}