#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
    char *const argv[] = {"ejecutado","Hola","Mundo",NULL}; //Argumentos para pasar, es muy importante que el primero sea el nombre del programa y el último un NULL
    printf("Programa %s / PID: %d \n", argv[0], getpid());
    printf("Presione cualquier tecla para continuar...\n");
    getchar();
    execv("./ejecutado",argv);
    printf("Hubo un error en la ejecución! Cancelando...\n");
    return -1;
   
}
