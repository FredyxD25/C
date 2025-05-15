
#include <unistd.h>

#include <stdio.h>


int main(int argc, char* argv[]){


    printf("Programa %s / PID: %d \n", argv[0], getpid());

    for (int i = 0; i < argc; i++)

    {

        printf("Argumento de entrada %d : %s \n",i,argv[i]);

    }

    printf("Presione cualquier tecla para continuar...\n");

    getchar();

    return 0;

   

}