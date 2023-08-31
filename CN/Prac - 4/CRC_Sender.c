#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <winsock2.h>


#define CRC8_POLY 0x07

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
    // Create and configure client socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Change to your desired port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to server IP
    
    // Connect to the server
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    char data[] = "1101001"; // Data to send
    int dataLength = sizeof(data) - 1;
    
    // Calculate CRC and append it to the data
    unsigned char crc = calculateCRC(data, dataLength);
    data[dataLength] = crc;
    
    // Send the data over the socket
    send(clientSocket, data, dataLength + 1, 0);
    
    // Close the socket
    close(clientSocket);
    
    return 0;
}