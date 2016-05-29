#ifndef CHAT_UDP_SOCKET_H
#define CHAT_UDP_SOCKET_H

#include <io/descriptor.h>

class UDPSocket : public Descriptor {
public:
    UDPSocket();
    UDPSocket(int descriptor);

    void setPort(int port);

    void bindToAddress();

private:
    int port;
};

#endif //CHAT_UDP_SOCKET_H
