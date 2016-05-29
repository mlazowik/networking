#ifndef CHAT_SOCKET_H
#define CHAT_SOCKET_H

#include <string>
#include <netdb.h>
#include <io/descriptor.h>

class TCPSocket : public Descriptor {
public:
    TCPSocket();
    TCPSocket(int descriptor);

    void setPort(int port);
    void setHost(std::string host);

    void connect();

    void bindToAddress();
    void startListening();
    TCPSocket acceptConnection();

private:
    int port;

    struct addrinfo *address;

    const int BACKLOG_QUEUE_LENGTH = 5;
};

#endif //CHAT_SOCKET_H