#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct ChiFeature2AnchorPickOutputInfo
{
    vector<int> outputOrder;                   ///< output order
};



int main(){

	ChiFeature2AnchorPickOutputInfo* pAnchorPickOutputInfo = new ChiFeature2AnchorPickOutputInfo;
	int i =1;
	while(i <= 10){
		pAnchorPickOutputInfo->outputOrder.push_back(i);
		i++;
	}
	vector<int>::iterator ite = pAnchorPickOutputInfo->outputOrder.begin();
	while(ite != pAnchorPickOutputInfo->outputOrder.end()){
		cout<< *ite << endl;
		ite++;
	}
	
	swap(pAnchorPickOutputInfo->outputOrder[3],pAnchorPickOutputInfo->outputOrder[4]);
	ite = pAnchorPickOutputInfo->outputOrder.begin();
	while(ite != pAnchorPickOutputInfo->outputOrder.end()){
		cout<< *ite << endl;
		ite++;
	}
	return 0;
}
