#include <stdio.h>
#include <termios.h>
#include <pthread.h>
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

pthread_mutex_t inputOutputmutex;   // Atomiska?

void fromAVR(void);
void *keyinput(void);
void *gui(void);
void *bridge(void);
void transmit(message);


int main(void){
    pthread_t t_keyinput, t_gui, t_bridge;

    pthread_create(&t_keyinput, null, &keyinput, null);
    pthread_create(&t_gui, null, &gui, null);
    pthread_create(&t_bridge, null, &bridge, null);

    pthread_mutex_init()
    pthread_mutex_init()

    fromAVR();
}

void fromAVR(void){                // från avr
    COM_1 = open("/dev/ttyS0", O_RDWR);

    strukt termios serialconfig;
    tcgetattr(COM_1, &serialconfig)
    serialconfig.c_cflag = B9600 | CLOCAL; // CS8 is allready set
    serialconfig.c_lflag =~ (ICANON | ECHO | ECHOK); // Toggle off

    //Sätter hur ofta signalenrna får ändras
    cfsetospeed(&serialconfig, B9600);
    cfsetispeed(&serialconfig, B9600);
    int data = 0;
    while(true){
        data = 0;
        read(serialconfig, &data, ); //(strukt, variabel, meep) läser indata till variabeln

        if(data == 0x6){        // 0110 North green south red
            northLight = 1;
            southLight = 0;
        }else if(data == 0x9){  // 1001 North red south green
            northLight = 0;
            southLight = 1;
        }else if(data == 0xA){  // 1010 both red
            northLight = 0;
            southLight = 0;
        }
    }
}

void *keyinput(void){               //från tangentbordet
    while(true){
        char carInput = getchar();
        if(carInput == "n"){
            northQueue++;
            transmit(0x1);
        }elseif(charInput == "s"){
            southQueue++;
            transmit(0x4);
        }elseif(charInput == "e"){
            break;
        }
    }
    printf("Terminerad");
}


void *gui(void){
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

void *bridge(void){             // to avr
    //int onbridge = 0; // om inte avr fixar det själv kan vi iplemetera en onbridge
    while(true){
        if(northLight == 1){
            northQueue--;
            transmit(0x2);

        }

        if(southLight == 1){
            southQueue--;
            transmit(0x8);
        }
        sleep(1);
    }
}

void transmit(int message){
    int meep = write(COM_1, message, sizeof(message));
}
