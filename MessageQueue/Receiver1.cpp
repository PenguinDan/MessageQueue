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
const int ACCEPT_FROM_2 = 997;
//Defines the size of the character array to be received
const int ARRAY_SIZE = 50;
//Defines the maximum amount of messages that this Receiver could receive
const int MAX_MESSAGES = 5000;
//Defines the message type in which this message could receive
const int RECEIVABLE_MESSAGE_TYPE = 1;
//Defines the message flag stating that the first message on the queue is received
const int MESSAGE_FLAG = 0;
//Message buffer
struct buffer {
    long messageType;
    long senderId;
    char message[ARRAY_SIZE];
};
//Forward declaring methods
int allocateQueue();
int retrieveMessageSize(buffer);
void sendMessageAcknowledgement(int , buffer , int , int);
void receiveMessage(int, buffer, int, long, int);

/*
 * The main starting point of the application
 */
int main() {

    //Create a message queue for other programs to connect to
    int messageQueueId = msgget(ftok(".", 'u'), IPC_EXCL|IPC_CREAT|0600);
    //Message that prints out the message queue ID for easy deallocation
    //from the terminal
    cout << "Created Message Queue ID: " << messageQueueId << endl;

    //Build buffer for message acknowledgement to sender 997
    //Sender 997 only receives messages of messageType 2
    buffer acknowledgementMessage;
    acknowledgementMessage.messageType = 3;
    acknowledgementMessage.senderId = 1;
    strcpy(acknowledgementMessage.message, "Acknowledgement from Receiver 1");

    //Create a buffer object to store the received messages
    buffer receivedMessage;
    const int MESSAGE_SIZE = retrieveMessageSize(receivedMessage);

    bool sender251Terminated = false;
    bool sender997Terminated = false;
    while(!sender251Terminated && !sender997Terminated) {
      cout << "Receiver 1 now waiting for message:" << endl;
      //Waits until a message with the proper message type specified by
      //the constant RECEIVABLE_MESSAGE_TYPE is the current first message
      //in the message queue
      msgrcv(messageQueueId, (struct msgbuf *)&receivedMessage, MESSAGE_SIZE,
      RECEIVABLE_MESSAGE_TYPE, MESSAGE_FLAG);
      //Check if the message is a termination message from either Sender
      if(strcmp(receivedMessage.message, "Terminated") == 0) {
        cout << "Sender #" << receivedMessage.senderId << " has terminated." << endl;
        //A sender has terminated, jump back to the top.
        continue;
      }
      //The message has been received, specify which sender the message
      //was received from and the message
      cout << "Message from Sender #" << receivedMessage.senderId <<
        ": " << receivedMessage.message << endl;

      //Check if the message was sent from Sender #997
      if(receivedMessage.senderId == ACCEPT_FROM_2) {
          //The message was received from Sender #997
          cout << "Sending acknowledgement message to Sender 997" << endl;
          //Send the acknowledgement message to Sender 997
          msgsnd(messageQueueId, (struct msgbuf *)&acknowledgementMessage,
          MESSAGE_SIZE, MESSAGE_FLAG);
      }
  }

  //Both Sender 251 and Sender 997 have terminated

}

/*
 * Wrapper method that outputs the size of the message to be received
 *
 * @Param:
 *    buffer message: The message buffer to be received
 *
 * @Return:
 *    The size of the message to be received
 */
int retrieveMessageSize(buffer message) {
    return sizeof(message) - sizeof(long) - sizeof(long);
}
