#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int calculateCRC8(unsigned char *data, int length)
{
    int crc = 0;
    int poly = 0x07; // CRC-8 polynomial

    for (int i = 0; i < length; i++)
    {
        crc ^= data[i]; // XOR with the byte

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
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrSize = sizeof(clientAddr);

    char buffer[100];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    // Bind the socket
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("Server listening...\n");

    recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &addrSize);

    int dataLength = strlen(buffer);
    int receivedCRC = buffer[dataLength]; // Extract received CRC

    buffer[dataLength] = '\0'; // Remove CRC from the buffer

    int calculatedCRC = calculateCRC8((unsigned char *)buffer, dataLength);

    if (receivedCRC == calculatedCRC)
    {
        printf("Received data: %s\n", buffer);
    }
    else
    {
        printf("Error detected\n");
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
