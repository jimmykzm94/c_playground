#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <string.h>

void PrintCommState(DCB dcb)
{
    // Print some of the DCB structure values
    _tprintf(
        TEXT("\nBaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n"),
        dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
}

void PrintErrorMessage()
{
    char lastError[1024];
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        lastError,
        1024,
        NULL);
    printf("Error: %s\n", lastError);
}

int main(int argc, char *argv[])
{
    // Check argument
    if (argc < 2)
    {
        printf("No serial port found\n");
        return 1;
    }
    char port_text[20];
    sprintf(port_text, "\\\\.\\%s", argv[1]);

    //  Open a handle to the specified com port.
    DCB dcb = {0};
    HANDLE hCom;
    TCHAR *port = TEXT(port_text);
    hCom = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                      OPEN_EXISTING, 0, NULL);

    if (hCom == INVALID_HANDLE_VALUE)
    {
        PrintErrorMessage();
        return 1;
    }

    //  Initialize the DCB structure.
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(hCom, &dcb))
    {
        PrintErrorMessage();
        return 1;
    }

    PrintCommState(dcb);

    //  Fill in some DCB values and set the com state:
    //  115200 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = CBR_115200; //  baud rate
    dcb.ByteSize = 8;          //  data size, xmit and rcv
    dcb.Parity = NOPARITY;     //  parity bit
    dcb.StopBits = ONESTOPBIT; //  stop bit

    if (!SetCommState(hCom, &dcb))
    {
        PrintErrorMessage();
        return 1;
    }

    //  Get the comm config again.
    if (!GetCommState(hCom, &dcb))
    {
        PrintErrorMessage();
        return 1;
    }

    PrintCommState(dcb);
    _tprintf(TEXT("Serial port %s successfully reconfigured.\n"), port);

    // Set timeout
    // If got response, ends after 50ms, otherwise no response timeout 2000ms
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 2000;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hCom, &timeouts))
    {
        PrintErrorMessage();
        return 1;
    }

    // Send and read
    const char *writeData = "DATA\n";
    DWORD bytesWrite = 0;
    DWORD bytesRead = 0;
    char response[100] = {0};
    if (!WriteFile(hCom, writeData, strlen(writeData), &bytesWrite, NULL))
    {
        PrintErrorMessage();
    }
    if (!ReadFile(hCom, response, 100, &bytesRead, NULL))
    {
        PrintErrorMessage();
    }
    printf("Response: %s\n", response);

    // Close handler
    CloseHandle(hCom);
    return 0;
}