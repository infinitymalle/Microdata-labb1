#include <stdio.h>
#include <termios.h>
#include <pthread.h>


int COM_1;
int carsOnBridge = 0;
int northQueue = 0;
int northLight = 0;
int southQueue = 0;
int southLight = 0;


void startsimulation(); 
void gui(*state); 
void transmit(message);


int main(void){


}

void read(){
    COM_1 = open("/dev/ttyS0", O_RDWR);

    strukt termios serialconfig;
    tcgetattr(COM_1, &serialconfig)
    serialconfig.c_cflag = B9600 | CLOCAL; // CS8 is allready set
    serialconfig.c_lflag =~ (ICANON | ECHO | ECHOK); // Toggle off


}

void write(text){

}

void *gui(){
    system("clear");
    printf("Cars on bridge: %d", carsOnBridge);
    printf("North queue: %d", northQueue);

    if(northLight == 0){
        printf("\033[1;31m");
    }else{
        printf("\033[1;32m");
    }
    printf("North light \033[37m");
    printf("South queue: %d", southQueue);

    if(southLight == 0){
        printf("\033[1;31m");
    }else{
        printf("\033[1;32m");
    }
    printf("South light \033[37m");
}

void *bridge(){
    while(true){
        if(northLight == 1){
            northQueue--;
            transmit(0x2);
        }
        if(southLight == 1){
            southQueue--;
            transmit(0x4);
        }
    }
}
