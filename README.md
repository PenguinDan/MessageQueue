# Main Project:



  * Create 2 Receivers and 3 Senders where the Senders are sending data to the Receivers.
  * The 5 Programs are running concurrently on the same machine.


# Jobs
## Sender
* Create a random 32 bit number generator for each of the senders
* Assign and store the values **251, 257, or 997** to the respective project where each of the senders will **behave differently**
* **Sender #997**
  * Sends to who:
      * Sends each event to *ALL RECEIVERS*
  * Requirements:
      * Requires acknowledgement for each message from *BOTH RECEIVERS* before it continues execution
  * Termination cause:
      * Terminates when it gets/observes a *RANDOM NUMBER SMALLER THAN 100*
* **Sender #251**
  * Sends to who:
      * Sends each event to only *ONE RECEIVER*
  * Requirements:
      * Does not accept any acknowledgement messages
  * Termination cause:
      * Terminates on a *“KILL” COMMAND FROM A SEPARATE TERMINAL*
      * The above will be supplied by the professor as a patch code to be integrated with this sender
 * **Sender #257**
    * Sends to who:
        * Sends each event to only *ONE RECEIVER*
    * Requirements:
        * Does not accept any acknowledgement messages
    * Termination cause:
        * Terminates when *ITS RECEIVER STOPS RECEIVING EVENT NOTIFICATIONS*

## Receiver
* Each receiver repeatedly gets a message and displays the value and the Sender’s identity
* **Receiver #1**
  * Accepts from who:
    * Only accepts messages from *251 AND 997 SENDERS*
  * Termination cause:
    * Terminates after BOTH OF ITS SENDERS HAVE TERMINATED
* **Receiver #2**
  * Accepts from who:
    * Only accepts messages from *257 AND 997 SENDERS*
  * Termination cause:
    * Terminates after it has *RECEIVED A TOTAL OF 5000 MESSAGES*
