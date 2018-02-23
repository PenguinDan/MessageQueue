/*
 - Send each event to ALL RECEIVERS
 - Requires acknowledgement for each message from BOTH RECEIVERS before it continues execution
 - Terminates when it gets/observes a RANDOM NUMBER SMALLER THAN 100
 */
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

const int SENDER_ID = 997;
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
