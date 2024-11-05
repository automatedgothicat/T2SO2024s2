#include <iostream>

using namespace std;

//************* MACROS MUDANCA COR DE TEXTO, ANSI ESCAPE CODES ****
#define COR_RESET       "\033[0m"
#define COR_VERDE       "\033[32m"
#define COR_VERMELHO    "\033[31m"
#define COR_AMARELO     "\033[38;5;11m"
#define COR_MAGENTA     "\033[38;5;207m"
#define COR_CIANO       "\033[36m"
#define COR_MUSGO       "\033[38;5;64m"
#define COR_LARANJADO   "\033[38;5;202m"
#define COR_ROXO        "\033[38;5;91m"
#define COR_MARROM      "\033[38;5;189m"
#define COR_AZUL        "\033[38;5;39m"
#define COR_BRANCO      "\033[38;5;15m"
#define COR_MESA        "\033[38;5;101m"
// para usar um texto de uma cor use: cout << COR_MUSGO << "O" << COR_RESET;

void colorline(char* color, char* msg){
    cout << color << msg << COR_RESET << endl;
}

//maybe if we create a function that return a string like "color << msg << COR_RESET"
//and then use it like cout << funcolor << int << "something" << endl

int main(){
    cout << "Funcionou de primeira hehehe" << endl;
    colorline(COR_VERMELHO,"Aviso");
    return 0;
}