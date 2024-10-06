#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta [512];
	
	if ((sock_listen== socket(AF_INET, SOCK_STREAM,0))<0)
		printf("Error creating socket");
	
	memset(&serv_adr,0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	serv_adr.sin_port= htons(9000);
	
	if(bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr))<0)
		printf("Error in bind");
		
	
	if(listen(sock_listen,3)<0) //cola de esperas siendo atendidas no puede ser mayor que 3
		printf("Error while listenig");
	
	
	int i;
	
	for (i=0; i<5; i++){
		printf("Listening\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		if (sock_conn < 0) {
			perror("Error accepting connection");
			continue; // Continuar con la siguiente iteraciÃ³n si hay un error
		}
		printf("I have recieved connection\n");
		
		ret=read(sock_conn, peticion, sizeof(peticion));
		if (ret < 0) {
			perror("Error reading from socket");
			close(sock_conn);
			continue; // Continuar si hay un error de lectura
		}
		
		peticion[ret]='\0';
		printf("Recieved:%s\n", peticion);
		
		int codigo;
		int grados;
		
		if (sscanf(peticion, "%d %d", &codigo, &grados) != 2) {
			sprintf(respuesta, "Invalid input format");
		} 
		else {
				
			printf("Codigo: %d, Grados: %d\n",codigo, grados);
			
			if (codigo==1)
			{
				float resultado = (grados - 32) * (5.0 / 9.0);
				sprintf(respuesta, "%d ºF son %f ºC", grados,resultado);
			}
			
			else if (codigo==2)
			{
				float resultado = (grados* 9.0 / 5.0) + 32;
				sprintf(respuesta, "%d ºC son %f ºF", grados,resultado);
			}
			
			else
				sprintf(respuesta,"Valor no válido");
		}
		write(sock_conn, respuesta, strlen(respuesta));
		close(sock_conn);
	}
	close(sock_listen);
	return 0;
}

