#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

typedef struct Servidor
{
    unsigned int port;
    unsigned int address;
    unsigned int max_connections;
    pthread_t *thread_pool;
    pthread_mutex_t lock;
    enum States{WORKING,FAILED,STOPED} state;
    void (*func_ptr_success)(int FD_client);
    void (*func_ptr_error)();
    void (*Servidor_Start)(Servidor *);
    void (*Servidor_Stop)(Servidor *);
}Servidor;

Servidor *Servidor_Create(unsigned int port,unsigned int address, unsigned int max_connections,void *ptr_success,void *ptr_error);
void Servidor_Destroy(Servidor * servidor);

#endif