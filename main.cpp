#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

#define nfilosofos 5
int garfos[nfilosofos] = { -1,-1,-1,-1,-1 };

HANDLE MutexGarfos[nfilosofos];
HANDLE MutexPrint;

void jantar(int filo_id);
void comer(int filo_id);
void meditar(int filo_id);

int main() {
    /* -------------------- multithread -------------------- */ 
    for (int i = 0; i < nfilosofos; i++) {
		MutexGarfos[i] = CreateMutex(NULL, FALSE, NULL);
	}
	MutexPrint = CreateMutex(NULL, FALSE, NULL); 

	HANDLE vetorthreads[nfilosofos];
	for (int i = 0; i < nfilosofos; i++) {
		vetorthreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)jantar, (void*)i, 0, NULL);
	}

	WaitForMultipleObjects(nfilosofos, vetorthreads, TRUE, INFINITE);

	for (int i = 0; i < nfilosofos; i++) {
		CloseHandle(vetorthreads[i]);
		CloseHandle(MutexGarfos[i]);
	}
	CloseHandle(MutexPrint);
    
    cout << "Fim do problema" << endl;
    return 0;
}

void jantar(int filo_id){
    while(true) {
        comer(filo_id);
        meditar(filo_id);
    }
}

void comer(int filo_id){
    int esquerdo = filo_id;
    int direito = (filo_id + 1) % nfilosofos;
    int tempo = rand() % 10000; //tempo aleatorio entre 10s

    while(true) {
        WaitForSingleObject(MutexGarfos[esquerdo],INFINITE);
        if(garfos[esquerdo] == -1){
            garfos[esquerdo] = filo_id;
            WaitForSingleObject(MutexPrint,INFINITE);
            cout << filo_id << " filosofo pegou o garfo esquerdo" << endl;
            ReleaseMutex(MutexPrint);

            WaitForSingleObject(MutexGarfos[direito],1000); // tenta pegar por 1s
            if(garfos[direito] == -1 && garfos[esquerdo] == filo_id){
                garfos[direito] = filo_id;
                WaitForSingleObject(MutexPrint,INFINITE);
                cout << filo_id << " filosofo pegou o garfo direito" << endl;
                cout << filo_id << " filosofo esta comendo por " << tempo << "ms" << endl;
                ReleaseMutex(MutexPrint);

                Sleep(tempo);

                garfos[direito] = -1;
                ReleaseMutex(MutexGarfos[direito]);
                WaitForSingleObject(MutexPrint,INFINITE);
                cout << filo_id << " filosofo soltou o garfo direito" << endl;
                ReleaseMutex(MutexPrint);
                
                garfos[esquerdo] = -1;
                ReleaseMutex(MutexGarfos[esquerdo]);
                WaitForSingleObject(MutexPrint,INFINITE);
                cout << filo_id << " filosofo soltou o garfo esquerdo" << endl;
                ReleaseMutex(MutexPrint);

                return;
            }
            garfos[esquerdo] = -1;
            WaitForSingleObject(MutexPrint,INFINITE);
            cout << filo_id << " filosofo soltou o garfo esquerdo" << endl;
            ReleaseMutex(MutexPrint);
            ReleaseMutex(MutexGarfos[direito]);
        }
        ReleaseMutex(MutexGarfos[esquerdo]);
        Sleep(rand() % 1000); //espera um tempo antes de tentar de novo
    }
}

void meditar(int filo_id){
    int tempo = rand() % 10000; //tempo aleatorio entre 10s
    WaitForSingleObject(MutexPrint,INFINITE);
    cout << "Filosofo " << filo_id << " vai meditar por " << tempo << "ms" << endl;
    ReleaseMutex(MutexPrint);
    Sleep(tempo);
}