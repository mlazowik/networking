#include <sys/socket.h>
#include <system_error>
#include <netinet/in.h>

#include "udp_socket.h"

UDPSocket::UDPSocket() : Descriptor(0) {
    this->descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    if (this->descriptor < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

UDPSocket::UDPSocket(int descriptor) : Descriptor(descriptor) { }

void UDPSocket::setPort(int port) {
    this->port = port;
}

void UDPSocket::bindToAddress() {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(this->port);

    if (bind(this->descriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}