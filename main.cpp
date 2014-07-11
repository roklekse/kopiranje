#include <iostream>
#include <fstream>
//potrebno za windows.h
#define WIN32_WINNt 0x0500
#define WINVER 0x0500
#include <windows.h>

#define GB 1073741824

using namespace std;

//arrays bytov, uporabljen za kopiranje
char *c;
//dolzina c
long long writingSize;

//datoteke
string filename = "q.wma";
ifstream inputFile;
ofstream outputFile;


/*
  Ta funkcija ugotovi, koliko je prostega spomina v racunalniku.
  Nato naredi char array, ki je velik 95% od najvec kolikor je mogoce

*/
//link: http://msdn.microsoft.com/en-us/library/windows/desktop/aa366589(v=vs.85).aspx
void alokacijaRAM()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);

    cout << "Total memory: "<< (float)statex.ullAvailVirtual/GB << endl;
    for (long long i = statex.ullAvailVirtual; i>0; i-=1000)
    {
        if ((c = (char*)malloc(i)) != NULL)
        {
            cout << "All memory for allocation: "<< (float)i/GB <<endl;
            writingSize = (long long)(0.95*i);
            cout << "Used memory for allocation: "<< (float)writingSize/GB << endl;
            delete[] c;
            c = new char[writingSize];
            break;
        }
    }
}


/*
  Ta funkcija prebere binarno datoteko.
*/
void binarnoBranje()
{
    //odpiranje datoteke
    inputFile.open(filename.c_str(), ios::binary|ios::in);
    //ugotavljanje velikosti datoteke:
    inputFile.seekg(0,inputFile.end);
    long long fileSize = inputFile.tellg();
    //pointer nazaj na zacetek datoteke
    inputFile.seekg(0,inputFile.beg);

    //preracunanje koliko je koncnih bytov, za katere bo treba prilagoditi char array in stevilo iteracij
    long long endBytes = fileSize % writingSize, pos = 0, iterations = fileSize/writingSize;
    //branje
    while (iterations--)
    {
        inputFile.read(c, writingSize);
        pos+=writingSize;
        inputFile.seekg(pos, ios::beg);
    }
    //koncni byti
    delete[] c;
    c = new char[endBytes];
    inputFile.read(c, endBytes);
    //velikost c nastavimo nazaj na zacetek
    delete[] c;
    c = new char[writingSize];
}

/*
  Ta funkcija zapiše binarno datoteko
*/
void binarnoPisanje()
{

}

/*
  Sprehajanje se po trenutnem direktoriju (pot) in vseh poddirektorijih
*/
void sprehod(string pot)
{

}

int main()
{
    alokacijaRAM();
    binarnoBranje();
    return 0;
}
