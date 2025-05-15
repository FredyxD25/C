#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void imprimeDePipe(int leePipe); //Funcionalidad para el hijo

void enviaAPipe(int escribePipe); //Funcionalidad para el padre


int main() {

    pid_t procHijo;

    int pipeFileDescriptors[2]; //Descriptores de ambos extremos


    if(pipe(pipeFileDescriptors) == -1) { //Genera pipe

        printf("Error al crear pipe\n");

        exit(1);

    }


    procHijo=fork(); //Genera proceso hijo


    if(procHijo<0) {

        int errnum=errno; //Preservamos código de error

        printf("Error %d al generar proceso hijo con fork\n",errnum);

        exit(1);

    }

    if(procHijo==0) {

    //Es el hijo, cierra pipe de envío y procede

        close(pipeFileDescriptors[1]);

        imprimeDePipe(pipeFileDescriptors[0]);

    }

    if(procHijo>0) {

    //Es el padre, cierra pide de recepción y procede

        close(pipeFileDescriptors[0]);

        enviaAPipe(pipeFileDescriptors[1]);

    }

    return 0;

}


/**

* Funcionalidad para el hijo, lee del pipe la cadena enviada, imprime

* el contenido de esta a STDOUT, cierra su extremo del pipe (lectura)

* y termina su proceso.

**/

void imprimeDePipe(int leePipe) {

    char buf; //Carácter de buffer

    printf("Proceso hijo, esperando cadena...\n");

    while (read(leePipe, &buf, 1) > 0)

    write(STDOUT_FILENO, &buf, 1);

    write(STDOUT_FILENO, "\n", 1); //Fin de línea

    close(leePipe);

    printf("Proceso hijo, finalizando\n");

    exit(0);

}

/**

* Funcionalidad para el padre, lee una cadena de hasta 10 caracteres,

* la escribe a su extremo del pipe, cierra su extremo y espera a que

* un proceso hijo termine antes de terminar su propio proceso.

**/

void enviaAPipe(int escribePipe) {
    char buf[10]; // Buffer para hasta 9 caracteres + null
    printf("Proceso padre, ingresa una cadena de hasta 10 caracteres y enter:\n");
    scanf("%9s", buf);
    printf("\n\n"); // Separa la entrada de las futuras salidas.
    write(escribePipe, buf, strlen(buf));
    close(escribePipe); // Presenta EOF al proceso hijo
    wait(NULL); // Espera terminación de hijo
    printf("Hijo terminado, terminando proceso padre\n");
    exit(0);
}