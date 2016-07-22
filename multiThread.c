#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>

#define CHILDREN 5
#define READ 0
#define WRITE 1
#define BUFFER_SIZE 100

int timedout = 0;

void SIGALRM_handler(int signal)
{
    assert(signal == SIGALRM);
    timedout = 1;
}

int main()
{
    int fd[5][2], i, count, pipeid;
    count = 0;
    pid_t parent = 0;
    pid_t child = 0;
    pid_t stdinput = 0;
    struct timeval start;

    gettimeofday(&start, NULL);
    for (i = 0; i < CHILDREN; i++)
    {
        if(pipe(fd[i])== -1)
        {
            fprintf(stderr,"Pipe %d failed.");
            return 1;
        }
    }

    if (fork() == 0) //child 1
    {
        pipeid = 0;
        stdinput = getpid();
        close(fd[0][0]);
        srand(pipeid);
    }
    else if (fork() == 0) //child 2
    {
        pipeid = 1;
        child = getpid();
        close(fd[1][0]);
        srand(pipeid);
    }
    else if (fork() == 0) //child 3
    {
        pipeid = 2;
        child = getpid();
        close(fd[2][0]);
        srand(pipeid);
    }
    else if (fork() == 0) //child 4
    {
        pipeid = 3;
        child = getpid();
        close(fd[3][0]);
        srand(pipeid);
    }
    else if (fork() == 0) //child 5
    {
        pipeid = 4;
        child = getpid();
        close(fd[4][0]);
        srand(pipeid);
    }
    else //parent
    {
        parent = getpid();
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][1]);
        close(fd[3][1]);
        close(fd[4][1]);
    }

    if (parent == 0) //child
    {
        while (!timedout)
        {
            struct timeval now;
            char msg[100], buffer[100];
            float time;

            if (stdinput == 0) //non stdin child
            {
                int wait = rand()%3;
                sleep(wait);
                gettimeofday(&now, NULL);
                float timestamp = (float) ((float)(now.tv_sec - start.tv_sec) + ((float)(now.tv_usec - start.tv_usec)/1000000));
                sprintf(buffer, "Time: 0:%2.3f, Message#: %d", timestamp, count);
                write(fd[pipeid][WRITE], buffer, BUFFER_SIZE);
                count++;
            }
            else //stdin child
            {
                printf("Enter Input: ");
                fgets(msg, 100, stdin);
                gettimeofday(&now, NULL);
                float timestamp = (float) ((float)(now.tv_sec - start.tv_sec) + ((float)(now.tv_usec - start.tv_usec)/1000000));
                sprintf(buffer, "Time: 0:%2.3f, Message#: %d Message: %s", timestamp, count, msg);
                write(fd[pipeid][WRITE], buffer, BUFFER_SIZE);
                count++;
            }
        }
    }
    else //parent
    {
        FILE *output; //output file
        output = fopen("output.txt","w");
        char buffer[100];
        int result, nread;
        fd_set inputs, input_fds;
        struct itimerval timer;
        struct timeval now2;
        timerclear(& timer.it_interval);
        timerclear(& timer.it_value);
        timer.it_value.tv_sec = 30;
        (void) signal(SIGALRM, SIGALRM_handler);
        setitimer(ITIMER_REAL, &timer, NULL);
        while (!timedout)
        {
            FD_ZERO(&inputs);
            FD_SET(fd[0][0], &inputs);
            FD_SET(fd[1][0], &inputs);
            FD_SET(fd[2][0], &inputs);
            FD_SET(fd[3][0], &inputs);
            FD_SET(fd[4][0], &inputs);
            input_fds = inputs;
            result = select(FD_SETSIZE, &input_fds, NULL, NULL, NULL);
            switch (result)
            {
                case -1:
                {
                    perror("Select");
                    exit(1);
                }
                case 0:
                {

                    printf("No children are ready. \n");
                    sleep(1);
                }
                default:
                {
                     if (FD_ISSET(fd[0][READ], &input_fds)) {
                        nread = read(fd[0][READ], buffer, BUFFER_SIZE);
                        buffer[nread] = 0;
                        gettimeofday(&now2, NULL);
                        float timestamp = (float) ((float)(now2.tv_sec - start.tv_sec) + ((float)(now2.tv_usec - start.tv_usec)/1000000));
                        if (nread > 0) {
                            fprintf(output, "0:%.3f Child 1: %s", timestamp, buffer);
                        }
                    }
                    if (FD_ISSET(fd[1][READ], &input_fds)) {
                        nread = read(fd[1][READ], buffer, BUFFER_SIZE);
                        buffer[nread] = 0;
                        gettimeofday(&now2, NULL);
                        float timestamp = (float) ((float)(now2.tv_sec - start.tv_sec) + ((float)(now2.tv_usec - start.tv_usec)/1000000));
                        if (nread > 0) {
                            fprintf(output, "0:%.3f Child 2: %s\n", timestamp, buffer);
                        }
                    }
                    if (FD_ISSET(fd[2][READ], &input_fds)) {
                        nread = read(fd[2][READ], buffer, BUFFER_SIZE);
                        buffer[nread] = 0;
                        gettimeofday(&now2, NULL);
                        float timestamp = (float) ((float)(now2.tv_sec - start.tv_sec) + ((float)(now2.tv_usec - start.tv_usec)/1000000));
                        if (nread > 0) {
                            fprintf(output, "0:%.3f Child 3: %s\n", timestamp, buffer);
                        }
                    }
                    if (FD_ISSET(fd[3][READ], &input_fds)) {
                        nread = read(fd[3][READ], buffer, BUFFER_SIZE);
                        buffer[nread] = 0;
                        gettimeofday(&now2, NULL);
                        float timestamp = (float) ((float)(now2.tv_sec - start.tv_sec) + ((float)(now2.tv_usec - start.tv_usec)/1000000));
                        if (nread > 0) {
                            fprintf(output, "0:%.3f Child 4: %s\n", timestamp, buffer);
                        }
                    }
                    if (FD_ISSET(fd[4][READ], &input_fds)) {
                        nread = read(fd[4][READ], buffer, BUFFER_SIZE);
                        buffer[nread] = 0;
                        gettimeofday(&now2, NULL);
                        float timestamp = (float) ((float)(now2.tv_sec - start.tv_sec) + ((float)(now2.tv_usec - start.tv_usec)/1000000));
                        if (nread > 0) {
                            fprintf(output, "0:%.3f Child 5: %s\n", timestamp, buffer);
                        }
                        fflush(stdout);
                    }
                }
            }
        }
    fclose(output);
    }
}
