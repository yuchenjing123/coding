#include <iostream>
using namespace std;
#include <mutex>
#include <thread>
static std::mutex g_mutex;


class Singleton
{
 public:
    static Singleton *getInstance()
    {
        if(pInstance == NULL)
        {
            g_mutex.lock();
            if(pInstance == NULL) //线程的切换
                pInstance = new Singleton;
                cout<< "getinstance" <<endl;
            g_mutex.unlock();
        }
 
        return pInstance;
    }
private:
    Singleton() { }
 
    static Singleton *pInstance;
};

Singleton *Singleton::pInstance = NULL;

int main()
{
    Singleton* Instance = Singleton::getInstance();
    if(Instance)
    {
        cout << "getinstance success" << endl;
    }



    return 0; 
}