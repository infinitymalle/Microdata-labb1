#include <stdio.h>
//#include <termios.h>

int carsOnBridge = 0;
int northQueue = 0;
int northLight = 0;
int southQueue = 0;
int southLight = 0;

void startsimulation(*state); 
void gui(*state); 
void transmit(*message);




int main(void){
    gui();
}

void gui(){
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

void startsimulator(state){
    c_cflag = B9600 | CLOCAL | ; // CS8 is allready set
    c_lflag =~ (ICANON | ECHO | ECHOK); // Toggle off
}