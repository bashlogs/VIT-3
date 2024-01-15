#include <stdio.h>
#include <winsock2.h>

#define PORT 12345

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    SOCKET receiverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (receiverSocket == INVALID_SOCKET) {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(PORT);
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(receiverSocket, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR) {
        perror("bind() failed");
        closesocket(receiverSocket);
        WSACleanup();
        return 1;
    }

    char buffer[1024];
    int expectedSeqNum = 0;

    while (1) {
        int addrLen = sizeof(receiverAddr);
        int bytesReceived = recvfrom(receiverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&receiverAddr, &addrLen);
        if (bytesReceived == SOCKET_ERROR) {
            perror("recvfrom() failed");
            break;
        }

        buffer[bytesReceived] = '\0';
        printf("Received: %s\n", buffer);

        // Check sequence number and acknowledge
        int seqNum = atoi(buffer + 7); // Extract the sequence number from the received packet
        if (seqNum == expectedSeqNum) {
            printf("Acknowledge: %d\n", seqNum);
            expectedSeqNum++;
        }
    }

    closesocket(receiverSocket);
    WSACleanup();

    return 0;
}
