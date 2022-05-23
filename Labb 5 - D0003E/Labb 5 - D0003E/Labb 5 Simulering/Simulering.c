#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
*   Author:
*   Malkolm Lundkvist
*   Eddie Höglund
*/

int COM_1;
int carsOnBridge = 0;
int northQueue = 0;
int northLight = 0; //1 grön 0 röd
int southQueue = 0;
int southLight = 0; //1 grön 0 röd
int terminera = 0;


//pthread_mutex_t inputOutputmutex;   // Atomiska?
pthread_mutex_t transmit_m, resourse_m;

void *fromAVR(void *dummy);
void keyinput(void);
void *gui(void *dummy);
void *bridge(void *dummy);
void transmit(uint8_t message);


int main(void){
    pthread_t t_fromAVR, t_gui, t_bridge;
    

    pthread_create(&t_fromAVR, NULL, fromAVR, 0);
    pthread_create(&t_bridge, NULL, bridge, 0);
    pthread_create(&t_gui, NULL, gui, 0);
    //pthread_mutex_init(&transmit_m, NULL);
    pthread_mutex_init(&resourse_m, NULL);

    keyinput();

    //pthread_join(t_fromAVR, NULL);
    //pthread_join(t_bridge, NULL);
    //pthread_join(t_gui, NULL);
}

void *fromAVR(void *dummy){                // från avr
    COM_1 = open("/dev/ttyS0", O_RDWR);

    struct termios serialconfig;
    tcgetattr(COM_1, &serialconfig);
    serialconfig.c_cflag = B9600 | CLOCAL; // CS8 is allready set

    int data = 0;
    while(true){
        if (terminera == 1) {
            break;
        }
        data = 0;
        read(COM_1, &data, 1); //(strukt, variabel, meep) läser indata till variabeln

        if(data == 0x9){        // 1001 North green south red
            pthread_mutex_lock(&resourse_m);
            northLight = 1;
            southLight = 0;
            pthread_mutex_unlock(&resourse_m);
        }else if(data == 0x6){  // 0110 North red south green
            pthread_mutex_lock(&resourse_m);
            northLight = 0;
            southLight = 1;
            pthread_mutex_unlock(&resourse_m);
        }else if(data == 0xA){  // 1010 both red
            pthread_mutex_lock(&resourse_m);
            northLight = 0;
            southLight = 0;
            pthread_mutex_unlock(&resourse_m);
        }
    }
}

void keyinput(void){               //från tangentbordet
    fd_set rfds;
    fcntl(fileno(stdin), F_SETFL, O_NONBLOCK);
    struct termios serialconfig;
    tcgetattr(STDIN_FILENO, &serialconfig);
    serialconfig.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &serialconfig);
    FD_SET(0, &rfds);
    while(true){
        if (FD_ISSET(0, &rfds)) {

            int charInput = getchar();
            if (charInput == 'n') {
                pthread_mutex_lock(&resourse_m);
                northQueue++;
                transmit(0x1);
                pthread_mutex_unlock(&resourse_m);
            }
            else if (charInput == 's') {
                pthread_mutex_lock(&resourse_m);
                southQueue++;
                transmit(0x4);
                pthread_mutex_unlock(&resourse_m);
            }
            else if (charInput == 'e') {
                terminera = 1;
                break;
            }
        }
    }
}


void *gui(void *dummy){
    while (true) {
        if (terminera == 1) {
            break;
        }
        system("clear");
        pthread_mutex_lock(&resourse_m);
        printf("\nNorth queue: %d ", northQueue);
        pthread_mutex_unlock(&resourse_m);
        if (northLight == 0) {
            printf("\033[1;31m");
        }
        else {
            printf("\033[1;32m");
        }
        printf("North light \033[37m");
        pthread_mutex_lock(&resourse_m);
        printf("\nSouth queue: %d ", southQueue);
        pthread_mutex_unlock(&resourse_m);
        if (southLight == 0) {
            printf("\033[1;31m");
        }
        else {
            printf("\033[1;32m");
        }
        printf("South light \033[37m");
        //printf("\033[2j");
        sleep(0.5);
    }
}

void *bridge(void *dummy){             // to avr
    //int onbridge = 0; // om inte avr fixar det själv kan vi iplemetera en onbridge
    while(true){
        if (terminera == 1) {
            break;
        }
        if(northLight == 1){
            pthread_mutex_lock(&resourse_m);
            northQueue--;
            transmit(0x2);
            pthread_mutex_unlock(&resourse_m);
        }

        if(southLight == 1){
            pthread_mutex_lock(&resourse_m);
            southQueue--;
            transmit(0x8);
            pthread_mutex_unlock(&resourse_m);
        }
        sleep(1);
    }
}

void transmit(uint8_t message){
    int meep = write(COM_1, &message, sizeof(message));
}
