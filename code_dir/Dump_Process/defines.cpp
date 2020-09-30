#include "data_process.h"

pthread_mutex_t g_mutex;

queue<RESPONSE*>  g_TaskQueue;
