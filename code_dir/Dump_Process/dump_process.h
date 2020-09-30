
#ifndef DUMP_PROCESS_H
#define DUMP_PROCESS_H

#include "data_process.h"

typedef struct node
{
    long time;
    list<float> row_list;
    bool operator<(node &b)
    {
        return time < b.time;
    }
} CSVLINE;

typedef enum
{
    INVILAD_NAME,
    FRAME,
    GYRO,
    OIS,
} DUMP_FILE_NAME;

class DumpProcess : public DataProcess
{
private:
    RESPONSE *m_response;
    list<CSVLINE> m_list;

public:
    bool ishave_title(string filename);
    DUMP_FILE_NAME file_type(string filename);
    
public:
    DumpProcess();
    ~DumpProcess();

    virtual RESPONSE* process(string &filename);
};

#endif
