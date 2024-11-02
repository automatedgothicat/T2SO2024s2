#include <iostream>
#include <Windows.h>
#include <process.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#define filosofos 5
int garfos[filosofos] = { -1,-1,-1,-1,-1 };

HANDLE MutexGarfos[filosofos];
HANDLE Mutex2;

int main() {
    cout << "Hello World" << endl;
    return 0;
}