#include "NewServerSelectWidget.h"
#include <string>


int main()
{
    const int BUFFER_SIZE = 2;
    const char* pipeName = "\\\\.\\pipe\\GflessClient";
    int language, server, channel;
    HANDLE hPipe;
    DWORD dwMode, bytesRead;
    BOOL fSuccess;
    std::string message;
    char readBuffer[BUFFER_SIZE];
    NewServerSelectWidget newServerSelectWidget;

    // Set up a pipe to communicate with the Gfless Client
    // and receive the values for the language server,
    // the server and the channel
    while (true)
    {
        hPipe = CreateFileA(
            pipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );

        if (hPipe != INVALID_HANDLE_VALUE)
            break;

        if (GetLastError() != ERROR_PIPE_BUSY)
            return EXIT_FAILURE;

        if (!WaitNamedPipeA(pipeName, 20000))
            return EXIT_FAILURE;
    }

    dwMode = PIPE_READMODE_BYTE | PIPE_WAIT;
    fSuccess = SetNamedPipeHandleState(
        hPipe,
        &dwMode,
        NULL,
        NULL
    );

    if (!fSuccess)
        return EXIT_FAILURE;

    message = "ServerLanguage";
    fSuccess = WriteFile(
        hPipe,
        message.c_str(),
        message.size(),
        NULL,
        NULL
    );

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);
    
    do
    {
        fSuccess = ReadFile(
            hPipe,
            readBuffer,
            BUFFER_SIZE,
            NULL,
            NULL
        );

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
            break;

    } while (!fSuccess);

    if (!fSuccess)
        return EXIT_FAILURE;

    language = readBuffer[0] - 0x30;

    message = "Server";
    fSuccess = WriteFile(
        hPipe,
        message.c_str(),
        message.size(),
        NULL,
        NULL
    );

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);

    do
    {
        fSuccess = ReadFile(
            hPipe,
            readBuffer,
            BUFFER_SIZE,
            NULL,
            NULL
        );

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
            break;

    } while (!fSuccess);

    if (!fSuccess)
        return EXIT_FAILURE;

    server = readBuffer[0] - 0x30;

    message = "Channel";
    fSuccess = WriteFile(
        hPipe,
        message.c_str(),
        message.size(),
        NULL,
        NULL
    );

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);

    do
    {
        fSuccess = ReadFile(
            hPipe,
            readBuffer,
            BUFFER_SIZE,
            NULL,
            NULL
        );

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
            break;

    } while (!fSuccess);

    if (!fSuccess)
        return EXIT_FAILURE;

    channel = readBuffer[0] - 0x30;

    // Wait for the login widget to be visible
    // and log into the desired server and channel
    while (!newServerSelectWidget.isVisible()) 
        Sleep(500);

    newServerSelectWidget.selectLanguage(language);
    Sleep(3000);

    while (!newServerSelectWidget.isVisible()) 
        Sleep(500);

    newServerSelectWidget.selectServer(server);
    Sleep(1000);
    newServerSelectWidget.selectChannel(channel);;

    return EXIT_SUCCESS;
}

DWORD WINAPI DllStart(LPVOID param)
{
    FreeLibraryAndExitThread((HMODULE)param, main());
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(NULL, NULL, DllStart, hModule, NULL, NULL));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
