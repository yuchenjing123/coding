#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
    char pSrc[] = "-1,-2,-3,-4";
    char* pToken = NULL;
    char* pSave = NULL;
    char* pDelimiter = ",";
    pToken = strtok_r(pSrc, pDelimiter, &pSave);
    while(pToken)
    {
        cout<<"ptoken is " << pToken<< "pSave is " << pSave<<endl;
        pToken = strtok_r(NULL, pDelimiter, &pSave);
    }
    return 0;
}