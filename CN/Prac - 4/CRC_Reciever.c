#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h> 

#define CRC8_POLY 0x07
#define MAX_DATA_SIZE 1024

unsigned char calculateCRC(const char *data, int length) {
    unsigned char crc = 0;
    
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRC8_POLY;
            } else {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}


int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
    
    char receivedData[MAX_DATA_SIZE]; // Buffer for received data
    int bytesRead = recv(clientSocket, receivedData, sizeof(receivedData), 0);
    
    if (bytesRead > 0) {
        int dataLength = bytesRead - 1;
        unsigned char receivedCRC = receivedData[dataLength];
        unsigned char calculatedCRC = calculateCRC(receivedData, dataLength);
        
        if (receivedCRC == calculatedCRC) {
            printf("Received data is valid.\n");
        } else {
            printf("Received data has errors.\n");
        }
    }
    close(clientSocket);
    close(serverSocket);
    
    return 0;
}