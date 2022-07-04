#include "GameStructures/TNTNewServerSelectWidget2.h"
#include "GameStructures/TCharacterSelectWidget.h"
#include <Windows.h>
#include <string>

int main()
{
    const int BUFFER_SIZE = 2;
    const char* pipeName = "\\\\.\\pipe\\GflessClient";
    int language, server, channel, character;
    HANDLE hPipe;
    DWORD dwMode;
    BOOL fSuccess;
    std::string message;
    char readBuffer[BUFFER_SIZE];
    TNTNewServerSelectWidget2* newServerSelectWidget = nullptr;
    TCharacterSelectWidget* characterSelectWidget = nullptr;

    while (newServerSelectWidget == nullptr || characterSelectWidget == nullptr) 
    {
        newServerSelectWidget = TNTNewServerSelectWidget2::getInstance();
        characterSelectWidget = TCharacterSelectWidget::getInstance();
        Sleep(500);
    }

    // Set up a pipe to communicate with the Gfless Client
    // and receive the values for the language server,
    // the server, the channel and the character slot
    hPipe = CreateFileA(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE)
        if (!WaitNamedPipeA(pipeName, 20000))
            return EXIT_FAILURE;

    dwMode = PIPE_READMODE_BYTE | PIPE_WAIT;
    fSuccess = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    // Send the server language message
    message = "ServerLanguage";
    fSuccess = WriteFile(hPipe, message.c_str(), message.size(), NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);
    fSuccess = ReadFile(hPipe, readBuffer, BUFFER_SIZE, NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    language = readBuffer[0] - 0x30;

    // Send the server message
    message = "Server";
    fSuccess = WriteFile(hPipe, message.c_str(), message.size(), NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);
    fSuccess = ReadFile(hPipe, readBuffer, BUFFER_SIZE, NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    server = readBuffer[0] - 0x30;

    // Send the channel message
    message = "Channel";
    fSuccess = WriteFile(hPipe, message.c_str(), message.size(), NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);
    fSuccess = ReadFile(hPipe, readBuffer, BUFFER_SIZE, NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    channel = readBuffer[0] - 0x30;

    // Send the character message
    message = "Character";
    fSuccess = WriteFile(hPipe, message.c_str(), message.size(), NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    ZeroMemory(readBuffer, BUFFER_SIZE);
    fSuccess = ReadFile(hPipe, readBuffer, BUFFER_SIZE, NULL, NULL);

    if (!fSuccess)
        return EXIT_FAILURE;

    character = readBuffer[0] - 0x30;
    character = character - 1;

    // Wait for the login widget to be visible
    // and log into the desired server and channel
    while (!newServerSelectWidget->isVisible()) 
        Sleep(500);

    newServerSelectWidget->selectLanguage(language);
    Sleep(3000);

    while (!newServerSelectWidget->isVisible()) 
        Sleep(500);

    newServerSelectWidget->selectServer(server);
    Sleep(1000);
    newServerSelectWidget->selectChannel(channel);
    Sleep(1000);

    while (!characterSelectWidget->isVisible())
        Sleep(500);

    if (character >= 0)
    {
        characterSelectWidget->clickCharacterButton(character);
        Sleep(1000);
        characterSelectWidget->clickStartButton();
    }

    return EXIT_SUCCESS;
}

DWORD WINAPI DllStart(LPVOID param)
{
    FreeLibraryAndExitThread((HMODULE)param, main());
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    HANDLE hThread;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        hThread = CreateThread(NULL, NULL, DllStart, hModule, NULL, NULL);
        if (hThread != NULL) CloseHandle(hThread);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

