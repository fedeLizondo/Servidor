#include "client.h"

#define DEFAULT_PORT 8080

ptr_client client_create(const char *ipAddress, const int port)
{
    ptr_client client = malloc(sizeof(Client));
    if(client > 0){
        client->ipAddress = (ipAddress != NULL) ? inet_addr(ipAddress) : INADDR_ANY;
        client->port = (port > 0) ? port : DEFAULT_PORT;
        client->max_size_recive = 4096;
        client->max_size_send = 1024;
        client->file_descriptor = 0;
    }
    return client;
}
void client_run(ptr_client this)
{
    if (this == NULL)
    {
        return;
    }

    struct sockaddr_in Client_sock;
    Client_sock.sin_family = AF_INET;
    Client_sock.sin_addr.s_addr = this->ipAddress;
    Client_sock.sin_port = htons(this->port);

    int FD_CLIENT = socket(AF_INET, SOCK_STREAM, 0);
    if (FD_CLIENT < 0)
    {
        printf("Error Iniciando el servidor");
        client_destroy(this);
        return;
    }

    this->file_descriptor = FD_CLIENT;

    if (connect(FD_CLIENT, (struct sockaddr *)&Client_sock, sizeof(struct sockaddr_in)) < 0)
    {
        printf("Error conectado con el servidor.\n");
        client_destroy(this);
        return;
    }
}

void client_send(ptr_client this,const char *message)
{
    if (this != NULL)
    {
        send(this->file_descriptor, message, sizeof(char) * this->max_size_send, 0);
    }
}
void client_recive(ptr_client this, char *buffer)
{
    if (this != NULL)
    {
        recv(this->file_descriptor, buffer, sizeof(char) * this->max_size_recive, 0);
    }
};
void client_destroy(ptr_client this)
{
    if (this != NULL) {
        if (this->file_descriptor > 0)
        {
            close(this->file_descriptor);
        }
        free(this);
    }
};