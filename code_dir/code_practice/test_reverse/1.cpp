#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
int main()
{
	vector<int> v = {1,2,3,4,5,6,7,8,9,10};
	reverse(v.begin(),v.end()-1);
	vector<int>::iterator ite = v.begin();
	while(ite != v.end())
	{
		cout << *ite << endl;
		ite++;
	}
	

	return 0;
}
