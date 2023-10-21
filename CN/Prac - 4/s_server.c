#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int a[] = { 30, 40, 50, 60, 70, 80, 90, 100, 110 };
    int y = sizeof(a) / sizeof(a[0]);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error in socket creation.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8011);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error in binding.\n");
        return 1;
    }

    if (listen(serverSocket, 10) == 0) {
        printf("Waiting for connection...\n");
    } else {
        printf("Error in listening.\n");
    }

    int addr_size = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addr_size);

    printf("The number of packets sent is: %d\n", y);

    // Send the number of packets to the client
    if (send(clientSocket, (char*)&y, sizeof(y), 0) == SOCKET_ERROR) {
        printf("Error sending the number of packets.\n");
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Send the packets to the client
    for (int i = 0; i < y; i++) {
        if (send(clientSocket, (char*)&a[i], sizeof(a[i]), 0) == SOCKET_ERROR) {
            printf("Error sending packet %d.\n", i);
            closesocket(clientSocket);
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
    }

    int k;
    // Receive the index 'k' from the client
    if (recv(clientSocket, (char*)&k, sizeof(k), 0) == SOCKET_ERROR) {
        printf("Error receiving index 'k' from the client.\n");
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Send the packet 'a[k]' to the client
    if (send(clientSocket, (char*)&a[k], sizeof(a[k]), 0) == SOCKET_ERROR) {
        printf("Error sending packet 'a[%d]' to the client.\n", k);
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Quitting\n");

    // Clean up and close the sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

