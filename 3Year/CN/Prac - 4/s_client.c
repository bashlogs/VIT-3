#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET connection;
    struct sockaddr_in serverAddr;
    int v[9]; // Array to store data
    int n = 0;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Create a socket
    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection == INVALID_SOCKET) {
        printf("Error in socket creation.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8011);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the appropriate server IP address

    // Connect to the server
    if (connect(connection, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed.\n");
        return 1;
    }

    printf("Connected to server...\n");

    // Read the number of frames from the server
    int p;
    if (recv(connection, (char*)&p, sizeof(p), 0) == SOCKET_ERROR) {
        printf("Error receiving number of frames.\n");
        closesocket(connection);
        WSACleanup();
        return 1;
    }

    printf("No of frame is: %d\n", p);

    // Receive frames from the server
    for (int i = 0; i < p; i++) {
        if (recv(connection, (char*)&v[i], sizeof(v[i]), 0) == SOCKET_ERROR) {
            printf("Error receiving frame %d.\n", i);
            closesocket(connection);
            WSACleanup();
            return 1;
        }
        printf("Received frame is: %d\n", v[i]);
    }

    v[5] = -1;

    // Request retransmission for frames with value -1
    for (int i = 0; i < p; i++) {
        if (v[i] == -1) {
            printf("Request to retransmit packet no %d again!!\n", i + 1);
            n = i;
            if (send(connection, (char*)&n, sizeof(n), 0) == SOCKET_ERROR) {
                printf("Error sending request for retransmission.\n");
                closesocket(connection);
                WSACleanup();
                return 1;
            }
        }
    }

    // Receive the retransmitted frame
    if (recv(connection, (char*)&v[n], sizeof(v[n]), 0) == SOCKET_ERROR) {
        printf("Error receiving retransmitted frame.\n");
        closesocket(connection);
        WSACleanup();
        return 1;
    }

    printf("Received frame is: %d\n", v[n]);

    printf("Quitting\n");

    // Clean up and close the socket
    closesocket(connection);
    WSACleanup();

    return 0;
}

