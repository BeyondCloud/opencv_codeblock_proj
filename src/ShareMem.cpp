#include "ShareMem.h"
#include <windows.h>
#include <iostream>
#define MAX_BUF_SIZE 0xFFFFF

using namespace std;

//Create memory constructor
ShareMem::ShareMem(TCHAR* n,int size)
{
    if(size > MAX_BUF_SIZE)
        cout << "except smaller size (<0xFFFFF)";

    name        = n;
    buffer_size = size;
    // create a file mapping object with CreateFileMapping first
    hMapFile    = CreateFileMapping(
                  INVALID_HANDLE_VALUE,    // use paging file
                  NULL,                    // default security
                  PAGE_READWRITE,          // read/write access
                  0,                       // maximum object size (high-order DWORD( upper 32 bit unsigned int))
                  MAX_BUF_SIZE,                // maximum object size (low 32 bit DWORD)
                  name);                 // name of mapping object

   if (hMapFile != NULL)
   {

        // create a pointer to the actual data with MapViewOfFile

        pBuf = (PVOID) MapViewOfFile(
                            hMapFile,   // handle to map object
                            FILE_MAP_ALL_ACCESS, // read/write permission
                            0,
                            0,
                            MAX_BUF_SIZE);

        if (pBuf == NULL)
            cout<<"Could not map view of file\n";
   }
   else
            cout<<"Could not open file mapping object\n";
}
//Access memory constructor
ShareMem::ShareMem(TCHAR* n)
{
    name     = n;
    hMapFile = OpenFileMapping(
                    FILE_MAP_ALL_ACCESS,   // read/write access
                    FALSE,                 // do not inherit the name
                    name);               // name of mapping object
    if (hMapFile == NULL)
    {
          cout<<"Could not create file mapping object \n";

    }
    pBuf     = (void *)MapViewOfFile(
                    hMapFile,   // handle to map object
                    FILE_MAP_ALL_ACCESS, // read/write permission
                    0,
                    0,
                    MAX_BUF_SIZE);
    if (pBuf == NULL)
    {
        cout<<"Could not map view of file\n";


           CloseHandle(hMapFile);

    }

    else
        cout<<"Could not open file mapping object\n";
}
void ShareMem::freeMem(){
   UnmapViewOfFile(pBuf);
   CloseHandle(hMapFile);
   cout<<"Close Shared Memory-----"<<name<<endl;
}

void ShareMem::writeMem(void *ptr){
    CopyMemory((PVOID)pBuf, ptr,buffer_size);
}

void* ShareMem::readMem(){
    if(pBuf != NULL)
        return pBuf;
}

int ShareMem::getBufferSize(){
    return buffer_size;
}

TCHAR* ShareMem::getName(){
    return name;
}

