
#include "./dump_process.h"

int main()
{
    DumpProcess* pDumpProcess = NULL;
    pDumpProcess = new DumpProcess;
    string filename = "frame.csv";
    pDumpProcess->process(filename);
    return 0;
}