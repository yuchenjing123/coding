
#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H

#include <string>
#include <queue>
#include <pthread.h>
#include <algorithm>
#include "./data_process.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"
{

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
}
#endif

typedef enum class __RESULT__
{
    SUCCESS,
    INVALID_FILE,
    INVALID_PROCESS,
    INVALID_TYPE,
} RESULT;

typedef enum class __TYPE__
{
    DUMP,
    VIDEO,
    INVALID
} TYPE;

typedef enum  __DUMPTYPE__
{
    //dump_type is frame.csv
        frame_id    =0,                                                        
        active_sensor_idx   =1,                                   
        frame_time  =2,
        sensor_rolling_shutter_skew =3,
        exposure_time   =4,
        sof =5,
        focus_distance  =6,
        eis_pre_crop_vIN_fullWidth  =7,
        eis_pre_crop_vIN_fullHeight =8,
        eis_pre_crop_vIN_windowLeft =9,
        eis_pre_crop_vIN_windowTop  =10,
        eis_pre_crop_vOUT_fullWidth =11,
        eis_pre_crop_vOUT_fullHeight    =12,
        eis_pre_crop_vOUT_windowWidth   =13,
        eis_pre_crop_vOUT_windowHeight  =14,
        eis_pre_crop_vOUT_windowLeft    =15,
        eis_pre_crop_vOUT_windowTop =16,
        output_crop_fov_fullWidth   =17,
        output_crop_fov_fullHeight  =18,
        output_crop_fov_windowWidth =19,
        output_crop_fov_windowHeight    =20,
        output_crop_fov_windowLeft  =21,
        output_crop_fov_windowTop   =22,
        ife_zoom    = 23,
        ipe_zoom    =24,
        total_zoom  = 25,
        //dump_type is gyro.csv 
        gyro_frameid    =26,
        gyro_time   =27,
        gyro_x  =28,
        gyro_y  =29,
        gyro_z  =30,
        //dump_type is ois.csv
        ois_frameid =31,
        ois_time    =32,
        ois_x   =33,
        ois_y   =34,
} DUMP_TYPE;

typedef struct __VALUE__{
	list<float> col_list;
}VALUE;

typedef struct __RESPONSE__
{
    TYPE type;
    RESULT result;
    map<DUMP_TYPE,VALUE*>* pDumpMap;	
} RESPONSE;

extern queue<RESPONSE*>  g_TaskQueue;

extern pthread_mutex_t g_mutex;
//*brif 互斥量的使用方法
// pthread_mutex_t g_mutex; 
// pthread_mutex_init(&g_mutex, NULL);
// pthread_mutex_lock(&g_mutex);		
// pthread_mutex_unlock(&g_mutex);	
// pthread_mutex_destroy(&g_mutex); 

class DataProcess
{
private:
public:
    DataProcess(){}
    ~DataProcess(){}

    virtual RESPONSE* process(string &filename) = 0;
};

#endif
