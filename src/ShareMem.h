#ifndef ShareMem_H
#define ShareMem_H
#include <windows.h>
using namespace std;
class ShareMem
{
    public:
        ShareMem(TCHAR*);
        ShareMem(TCHAR*,int);
        void     freeMem();
        void     writeMem(void*);
        void*    readMem();
        int      getBufferSize();
        TCHAR*   getName();
        HANDLE hMapFile;
        void* pBuf;
    private:
        int buffer_size;
        TCHAR* name;


};

#endif
