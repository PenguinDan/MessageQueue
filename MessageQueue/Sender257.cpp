/*
 - Sends each event to only ONE RECEIVER
 - Does not accept any acknowledgement messages
 - Terminates when ITS RECEIVER STOPS RECEIVING EVENT NOTIFICATIONS
 */
//Initialize Constants
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int SENDER_ID = 257;
const int MESSAGE_SIZE = 50;

int generateRandomNum();
void initializeSRand();

int main(){
    struct buf{
        long mtype;
        //Define message size
        char message[MESSAGE_SIZE];
    };buf msg;
    initializeSRand();
}

//Generate a random number
int generateRandomNum(){
    return rand() % INT_MAX;
}

//Inititalize srand to the internal with the internal clokc of the computer
void initializeSRand(){
    srand((int) time(NULL));
}
