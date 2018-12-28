/*
Shared memory connection study using: https://docs.microsoft.com/en-us/windows/desktop/memory/creating-named-shared-memory

this is P1
*/


#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>


#define BUF_SIZE 8

TCHAR szServerName[]=TEXT("Global\\ServerMemoryP1");
//TCHAR szClientName[]=TEXT("Global\\ClientMemoryP2");

double szMsg2P2 = 12.0;


int main() {
    
    std::cout << "program has started, initiating...." << std::endl;
    
    
    std::string receivedData = "i don't need it";
    double data2send = 1.0;

    HANDLE hMapFile;
    double* pBuf;

    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, szServerName);

    if(hMapFile == NULL){
        _tprintf(TEXT("Could not create shared memory object (%d)"), GetLastError());
        _getch();
        return 1; // exit
    }

    pBuf = (double*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);

    if (pBuf == NULL){
        _tprintf(TEXT("Could not map view of file (%d).\n"),GetLastError());
        CloseHandle(hMapFile); // close the handle and exit
        _getch();
        return 1;
    }

    
    *pBuf = szMsg2P2;

    if(*pBuf != szMsg2P2){
        std::cout << "\n the shared memory wasn't assigned properly, the current value is: " << *pBuf;
        _getch();
        return 1;
    }



    //CopyMemory((PVOID)pBuf, szMsg2P2, sizeof(********));
    
    
    //_getch();

    std::cout << "\n the p1 server memory is shared, the current value is: " << *pBuf << ", waiting on clients.. \n\n";

// check for p2's memory
    while (1){
        std::cin >> data2send;

        if(data2send == 0.0){
            break;
        }
        data2send += 1;
        *pBuf = data2send;
        std::cout << "\n the current value is modified: " << *pBuf << ", waiting on clients.. \n\n";



    }

    

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}