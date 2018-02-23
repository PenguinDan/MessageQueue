/*
* Each receiver repeatedly gets a message and displays the value and the Sender’s identity
* Receiver #1
*    Accepts from who:
*       Only accepts messages from 251 AND 997 SENDERS
*    Termination cause:
*       Terminates after BOTH OF ITS SENDERS HAVE TERMINATED
*/

//All of the necessary libraries for the program to run
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
using namespace std;

//Constants that define the Senders in which this Receiver listens to
const int ACCEPT_FROM_1 = 251;
const int ACCEPT_FROM_2 = 997
//Defines the size of the character array to be received
const int MESSAGE_SIZE = 50;
//Variable that keeps track of total received messages
int receivedMessagesCount = 0;

//Forward declaring methods
int allocateQueue();

/*
* The main starting point of the application
*/
int main() {

	int qid = allocateQueue();

	//Message buffer
	struct buf {
		long mtype;
		char message[MESSAGE_SIZE];
	};

	buf msg;
	int size = sizeof(msg)-sizeof(long);

	exit(0);
}

/*
*	Allocates a queue where message objects are saved
*
* @Param: None
*
*	@Return: A message queue identifier
*/
int allocateQueue() {
	string filePath = ".";
	int id = 'u';

	return msgget(ftok(filePath, id), IPC_EXCL|IPC_CREAT|0777);
}
