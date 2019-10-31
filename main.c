    
    
    
    
    // 1) La herencia de hilos esta terminada y funciona correctamente
    // 2) falta ver el tema que hace un getchar para cada hilo, con lo cual los procesos que no terminaron con exit()
    // siguen corriendo y esperando con un getchar(), en consecuencia, cuando quiero escribir en terminal cada dos botones me termina un proceso
    // es como si se trabara la terminal.



#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


void mostrar_info(pid_t pid, pid_t ppid, char *, char *);

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void main(){
    //pthread_mutex_lock(&mutex);
    char *padre="padre", *hijo="hijo", *nieto="nieto", *bisnieto="bisnieto", *normal="normal", *zombie="zombie", *demonio="demonio";
    for(int i=0; i<4; i++){
        pid_t pid = fork();
        if(pid==0){
            if(i==0){
                pid_t pid = fork();
                if(pid==0){
                    sleep(1);
                    mostrar_info(getpid(),getppid(),nieto,demonio);
                    break;
                }else{
                    pid_t pid = fork();
                    if(pid==0){
                        sleep(1);
                        mostrar_info(getpid(),getppid(),nieto,demonio);
                        break;
                    }else{
                        mostrar_info(getpid(),getppid(),hijo,zombie);
                        exit(0); // finalizo al padre (se convierte en zombie ya que main no termino), e init adopta ambos hijos (convirtiendolos en demonio 1 y 2)
                    }
                }
            }
            if(i==1){
                pid_t pid = fork();
                if(pid==0){
                    sleep(1);
                    mostrar_info(getpid(),getppid(),nieto,demonio);
                    break;
                }else{
                    mostrar_info(getpid(),getppid(),hijo,zombie);
                    exit(0); // finalizo al padre (se convierte en zombie ya que main no termino), e init adopta al hijo (convirtiendolo en demonio 3)
                }
            }
            if(i==2){
                for(int j=0; j<2; j++){
                    pid_t pid = fork();
                    if(pid==0){
                        for(int k=0; k<2; k++){
                            pid_t pid = fork();
                            if(pid==0){
                                mostrar_info(getpid(),getppid(),bisnieto,normal);
                                break;
                            }else{
                                if(k==1)
                                    mostrar_info(getpid(),getppid(),nieto,normal);
                            }
                        }
                        break;
                    }else{
                        if(j==1)
                            mostrar_info(getpid(),getppid(),hijo,normal);
                    }
                        
                }
                
            }
            if(i==3){
                pid_t pid = fork(); // nieto 3
                if(pid==0){
                    pid_t pid = fork(); // bisnieto 5
                    if(pid==0){
                        mostrar_info(getpid(),getppid(),bisnieto,normal);
                        break;
                    }else{
                        mostrar_info(getpid(),getppid(),nieto,normal);
                    }
                }else{
                    mostrar_info(getpid(),getppid(),hijo,normal);
                }
            }
            break;
        }else{
            if(i==0){
                mostrar_info(getpid(),getppid(),padre,"main");
            }
        }
    }
    getchar();
}

void mostrar_info(pid_t pid, pid_t ppid, char *parentesco, char *tipo){
    printf("PID: %d PPID: %d Parentesco-Tipo: %s - %s\n",pid,ppid,parentesco,tipo);
}