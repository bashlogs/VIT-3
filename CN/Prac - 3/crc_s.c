#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int sender(unsigned char *data, int length)
{
    int crc = 0;
    int poly = 0x07;

    for (int i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (int j = 0; j < 8; j++)
        {
            if ((crc & 1) != 0)
            {
                crc = (crc >> 1) ^ poly;
            }
            else
            {
                crc = crc >> 1;
            }
        }
    }

    return crc & 0xFF;
}

int main()
{
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    int addrSize = sizeof(serverAddr);

    char buffer[100];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serverAddr.sin_port = htons(12345);
    printf("Enter data to send: ");
    scanf("%s", buffer);

    int dataLength = strlen(buffer);
    int crc = sender((unsigned char *)buffer, dataLength);

    buffer[dataLength] = crc;

    sendto(clientSocket, buffer, dataLength + 1, 0, (struct sockaddr *)&serverAddr, addrSize);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
