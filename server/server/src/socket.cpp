#include "socket.h"

Socket::Socket(int serwer_port)
{ 
	mySocket = s_socket();

    //ustawienie parametrow gniazda(socket)
    serwerAddrress.sin_family = AF_INET;
    serwerAddrress.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY - automatycznie wybiera ip
    serwerAddrress.sin_port = htons(static_cast<uint16_t>(serwer_port)); // host to network byte order
    memset(&(serwerAddrress.sin_zero), '\0', 8);

    sin_size = sizeof(struct sockaddr_in);

    std::cout << "The socket has been created!" << std::endl;
}

Socket::~Socket()
{
    std::cout << "Socket has been closed!" << std::endl;
}

void Socket::s_bind()
{
	if(bind(mySocket,reinterpret_cast<struct sockaddr*>(&serwerAddrress) , sizeof(struct sockaddr)) == -1)
    {
        exit(3);
        perror("Error function bind");
    }
}

void Socket::s_listen()
{
	if(listen(mySocket, BACKLOG) == -1)
    {
        perror("Error function listen");
        exit(5);
    }
}

void Socket::s_setsockopt()
{
	if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) //fukcja nadpisuje jeszcze nie zwolniony wczesniej uzywany port
    {
        perror("Error function setsockopt");
        exit(2);
    }
}

int Socket::s_socket()
{
	return socket(PF_INET, SOCK_STREAM, 0);
}

int Socket::s_accept()
{
	return accept(mySocket, reinterpret_cast<struct sockaddr *>(&clientAddress), reinterpret_cast<socklen_t *>(&sin_size));
}

void Socket::s_connect()
{
	if(connect(mySocket, reinterpret_cast<struct sockaddr*>(&serwerAddrress) , sizeof(struct sockaddr)) == -1)
    {
        perror("Error function connect");
        exit(2);
    }
}