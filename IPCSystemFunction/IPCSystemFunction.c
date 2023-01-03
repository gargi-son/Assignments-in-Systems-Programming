/*
Name:Gargi Sontakke
Gno: G01334018
Assignment 5: IPC system function
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<assert.h>
#include<signal.h>
#include<fcntl.h>

int cs531_system(const char *comm);

int cs531_system(const char *comm)
{ 
    int signal_status;
    int child;
    int tel_type,wait_var;
    sig_t int_status,quit_status,stop_status, kill_status;
    fflush(stdout);
    tel_type = open("/dev/tty",O_RDWR);
    if(tel_type == -1)
    {
        fprintf(stderr,"Cannot Open /dev/tty\n");
        return -1;
    }

    child = fork();
    if(child==0)
    {
        close(0); dup(tel_type);
        close(1); dup(tel_type);
        close(2); dup(tel_type);
        close(tel_type);
        printf("Currently in the child process with pid %d\n",getpid());
        sleep(40);
        execlp("sh","sh","-c",comm,(char *) 0);
        exit(127);
    }
    close(tel_type); 
    stop_status = signal(SIGSTOP, SIG_IGN);
    quit_status = signal(SIGQUIT,SIG_IGN);
    int_status = signal(SIGINT,SIG_IGN);
    kill_status = signal(SIGKILL, SIG_IGN);
    
    printf("Currently in the Parent Process with pid %d\n", getpid());
    do 
    {
        wait_var = waitpid(child, &signal_status, WUNTRACED | WCONTINUED);
        if (wait_var == -1) 
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        } 
        if (WIFSTOPPED(signal_status)) 
        {
            printf("Process was stopped by signal %d\n", WSTOPSIG(signal_status));
        } 
        else if (WIFCONTINUED(signal_status)) 
        {
            printf("Process was continued\n");
        }    
        else if (WIFSIGNALED(signal_status)) 
        {
            printf("Process was killed by signal %d\n", WTERMSIG(signal_status));
        }     
        else if (WIFEXITED(signal_status)) 
        {
            printf("Process was exited, Signal=%d\n", WEXITSTATUS(signal_status));
        } 
    } while (!WIFEXITED(signal_status) && !WIFSIGNALED(signal_status)); 

    signal(SIGINT,int_status);
    signal(SIGQUIT,quit_status); 
    signal(SIGKILL,kill_status);
    printf("\n %ld ",wait(&signal_status));
    return signal_status;

}
int main(int argc, char *argv[])
{
  if(argv[1]==NULL)
  {
    cs531_system("who");
  }
  else{
    cs531_system(argv[1]);
  }
}
