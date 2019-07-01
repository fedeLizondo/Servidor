#include "servidor.h"
#include <pthread.h>

void Servidor_Start(Servidor * servidor){
    if (servidor == NULL || servidor->state == WORKING) {
        return ;//No haga nada
    }
    
    //Creo el socket para la conexion 
	unsigned int len;
	int reutilizar = 1;

    struct sockaddr_in direccion_servidor,direccionCliente;
    bzero((char *) &direccion_servidor, sizeof(direccion_servidor));
    direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_addr.s_addr = (servidor->address == 0)? INADDR_ANY : servidor->address; 
	direccion_servidor.sin_port = htons(servidor->port);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	//Activo la opcion para que se pueda reutilizar la direccion y puerto (asi no tengo que esperar a que se libere)	
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &reutilizar, sizeof(reutilizar));
	
	if(bind(servidor,(void* ) &direccion_servidor, sizeof(direccion_servidor)) != 0){
		perror("Fallo el bind");
        servidor->state = FAILED;   
        servidor->func_ptr_error();
		return 1;
	}
	
	if(listen(servidor,servidor->max_connections)<0){
        perror("Fallo el listen");
        servidor->state = FAILED;   
        servidor->func_ptr_error();
		return 1;
    }
    

    int mustRunServer = (servidor->state == WORKING);
    
    int quantity_threads = 0;
    while( mustRunServer ){
        int FD_Cliente = accept(servidor, (void*) &direccionCliente, &len);     
        if(FD_Cliente > 0) {
            pthread_create(&(servidor->thread_pool[quantity_threads++])),NULL,servidor->func_ptr_success,(void *) &FD_Cliente);
        }
        pthread_mutex_lock(&servidor->lock);
        mustRunServer = (servidor->state == WORKING);
        pthread_mutex_unlock(&servidor->lock);
    }

    for(int i = servidor->max_connections; i > 0; --i){
        pthread_join(ptr_array_pthread[i],NULL);
    }

}

void Servidor_stop(Servidor * servidor){
    if(servidor == NULL)
        return;    
    pthread_mutex_lock(&servidor->lock);    
    servidor->state = STOPED
    pthread_mutex_unlock(&servidor->lock);
}

Servidor *Servidor_Create(unsigned int port,unsigned int address, unsigned int max_connections,void *ptr_success,void *ptr_error){
    Servidor *servidor = malloc(sizeof(Servidor));
    servidor->address = address;
    servidor->port = ( port == 0 )?8080:port;
    servidor->max_connections = (max_connections == 0)?1:max_connections;
    servidor->thread_pool = pthread_t pool[servidor->max_connections]; 
    pthread_mutex_init(servidor->lock,NULL);
    servidor->func_ptr_success = ptr_success;
    servidor->func_ptr_error = ptr_error;
    servidor->state = STOPED;
    return servidor;
};

void Servidor_Destroy(Servidor * servidor){
    if(servidor == NULL) {
        return;
    }
    
    if (servidor->state == WORKING ) {
        servidor->Servidor_Stop()
    }

    pthread_mutex_destroy(servidor->lock); 

    free(servidor)
};


