#ifndef __SENDER_H__
#define __SENDER_H__
#include <stdlib.h> /* size_t*/
#include "NetErr.h" /*Err defines */

/** 
 * @brief Create an app to send messages from in multicasting using udp protocol. 
 * The app send messages in MSG structure based on chatprotocol, and will print by name and text. 
 * Messages and Name should not contain more the 255 characters.
 * @author Eyal Yaish
 */ 
typedef struct ChatSender ChatSender;

/**  
 * @brief Create a newly chat sender. When created, it send the it's process pid to the msgId que given.
 * @param[size_t] _port - Port number from which to recieve the messages
 * @param[char*] _groupAddr - Ip adress of multicast type to recievce messages from.
 * @param[char*] _name - Name to attached to each message for identify the sender.
 * @param[int] _msgId - Message que id to its pid.
 * @return ChatSender* - on success
 * @retval NULL on fail or if any of the pointers is null 
 *
 * @warning Giving correct message queue id is user responsibility. If failed create continue normaly.
 */
ChatSender* ChatSenderCreate (size_t _port, const char* _groupAdrr, const char* _name, int _msgId);

/**  
 * @brief Deallocate a previously allocated ChatSender
 * @param[in] _sender - ChatSender to be deallocated.  On success will be nulled.
 * @warning return null if _sender is null 
 */
void ChatSenderDestroy(ChatSender** _sender);

/**  
 * @brief Run the _sender ready to read messages from stdin.  
 * @param[in] _sender - ChatSender to run.
 * @return success or error code.
 * @retval NET_ERR_SUCCESS  on success.
 * @retval NET_ERR_NOT_INITIALIZED  error,  ChatSender not initilized.
 * @warning messages can't be more the 255 characters. 
 */
NetErr ChatSenderRun(ChatSender* _sender);

/**  
 * @brief Send one message. 
 * @param[in] _multi - ChatSender to run.
 * @param[char*] _msg - message to send.
 * @param[int] _msgSize - message size, must be more then 0.
 * @return success or error code.
 * @retval NET_ERR_SUCCESS on success.
 * @retval NET_ERR_TRANSMITION_FAILED if failed to send the message.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
NetErr ChatSenderSendMessage(ChatSender* _sender, const char* _msg, int _msgSize);

#endif /* sender.h */