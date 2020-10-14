#include <iostream>
using namespace std;

int main()
{
	int* arr = new int(10);
	cout << *arr << endl;
	delete arr;
	arr = NULL;

	return 0;
}
