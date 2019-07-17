#include "servidor.h"
#define DEFAULT_PORT 8080;
#define MAX_CONNECTIONS 100;
#define TRUE 1;
#define FALSE 0;

void *doNothingAndReturnNull(void *ptr) { return ptr; };

ptr_Servidor servidor_create(const char *ipAddress, const int port)
{
    ptr_Servidor servidor = malloc(sizeof(Servidor));
    servidor->ipAddress = (ipAddress != NULL) ? inet_addr(ipAddress) : INADDR_ANY;
    servidor->port = (port > 0) ? port : DEFAULT_PORT;
    servidor->maxConnections = MAX_CONNECTIONS;
    servidor->onError = doNothingAndReturnNull;
    servidor->onSuccess = doNothingAndReturnNull;
    servidor->shouldRun = TRUE;
    return servidor;
};

void servidor_destroy(ptr_Servidor servidor)
{
    servidor_stop(servidor);
    free(servidor);
};

void servidor_run(ptr_Servidor this)
{
    if (this == NULL)
    {
        return;
    }

    struct sockaddr_in Servidor_Socket, Cliente_Socket;
    bzero((char *)&Servidor_Socket, sizeof(Servidor_Socket));
    Servidor_Socket.sin_family = AF_INET;
    Servidor_Socket.sin_addr.s_addr = this->ipAddress;
    Servidor_Socket.sin_port = htons(this->port);

    int FD_SERVIDOR = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (FD_SERVIDOR < 0)
    {
        printf("Error make SOCKET");
        exit(1);
    }

    int reutilizar = 1;
    setsockopt(FD_SERVIDOR, SOL_SOCKET, SO_REUSEADDR, &reutilizar, sizeof(reutilizar));

    if (bind(FD_SERVIDOR, (void *)&Servidor_Socket, sizeof(Servidor_Socket)) < 0)
    {
        printf("Error in BIND");
        close(FD_SERVIDOR);
        exit(1);
    }

    if (listen(FD_SERVIDOR, this->maxConnections) < 0)
    {
        printf("Error in LISTING");
        close(FD_SERVIDOR);
        exit(1);
    }

    //TODO AGREGAR UN MEJOR MANEJO DE HILOS
    pthread_t ptr_hilo;
    int FD_CLIENT = 0;

    unsigned int len;
    while (this->shouldRun)
    {
        FD_CLIENT = accept(FD_SERVIDOR, (struct sockaddr *)&Cliente_Socket, &len);
        if (FD_CLIENT < 0)
        {
            printf("ERROR in ACCEPT");
            this->onError(NULL);
        }
        else
        {
            pthread_create(&ptr_hilo, NULL, this->onSuccess, (void *)&FD_CLIENT);
        }
    }

    pthread_join(ptr_hilo, NULL);

    if (FD_CLIENT > 0)
    {
        close(FD_CLIENT);
    }

    if (FD_SERVIDOR > 0)
    {
        close(FD_SERVIDOR);
    }
};

void servidor_stop(ptr_Servidor this)
{
    if (this != NULL)
    {
        this->shouldRun = FALSE;
    }
};