#include <stdio.h>
#include <winsock2.h>

#define PORT 12345
#define WINDOW_SIZE 4

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    SOCKET senderSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (senderSocket == INVALID_SOCKET) {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(PORT);
    receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char packet[1024];
    int seqNum = 0;

    while (1) {
        for (int i = seqNum; i < seqNum + WINDOW_SIZE; i++) {
            sprintf(packet, "Packet %d", i);
            sendto(senderSocket, packet, strlen(packet), 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
        }

        Sleep(2000); // Simulate a timeout

        seqNum += WINDOW_SIZE;
    }

    closesocket(senderSocket);
    WSACleanup();

    return 0;
}
