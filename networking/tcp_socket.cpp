#include <system_error>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include "tcp_socket.h"

TCPSocket::TCPSocket() : Descriptor(-1) {
    this->descriptor = socket(PF_INET, SOCK_STREAM, 0);

    if (this->descriptor < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

TCPSocket::TCPSocket(int descriptor) : Descriptor(descriptor) { }

void TCPSocket::setPort(int port) {
    this->port = port;
}

void TCPSocket::setHost(std::string host) {
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = 0;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::string portString = std::to_string(this->port);

    int err = getaddrinfo(host.c_str(), portString.c_str(), &hints, &this->address);
    if (err != 0) {
        if (err == EAI_SYSTEM) {
            throw std::system_error(errno, std::system_category());
        } else {
            std::string e(gai_strerror(err));
            throw std::runtime_error("failed too look up the address: " + e);
        }
    }
}

void TCPSocket::connect() {
    if (::connect(this->descriptor, address->ai_addr, address->ai_addrlen) != 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void TCPSocket::bindToAddress() {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(this->port);

    if (bind(this->descriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void TCPSocket::startListening() {
    listen(this->descriptor, this->BACKLOG_QUEUE_LENGTH);
}

TCPSocket TCPSocket::acceptConnection() {
    int connectionDescriptor = accept(this->descriptor, (struct sockaddr*)0,
                               (socklen_t*)0);

    if (connectionDescriptor < 0) {
        throw std::system_error(errno, std::system_category());
    }

    return TCPSocket(connectionDescriptor);
}