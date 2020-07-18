#ifndef __CLIENTNET_H__
#define __CLIENTNET_H__

#include <stdlib.h> /* size_t*/

/** 
 * @brief Connect to server in a tcp protocol, send and recieve messages.
 * @author Eyal Yaish
 */ 

typedef struct Clientnet Clientnet;

typedef enum ClientErr {
	CLIENT_SUCCESS = 0,
	CLIENT_UNINITIALIZED_ERROR, 		/**< Uninitialized client error 	*/
    CLIENT_CONNECTION_ERROR, 		    /**< Failed to connect with server 	*/
    CLIENT_CLOSE_SOCKET,                /**< server close socket 	*/
    CLIENT_TRANSMITION_FAILED           /**< System failed to send or recieve 	*/
} ClientErr;

/**  
 * @brief Create a newly Clientnet. 
 * @param[size_t] _serverPort - Port number of server.
 * @param[char*] _serverIp - Ip adress of server.
 * @return Clientnet* - on success
 * @retval NULL on fail or if _serverIp is null, or if failed to create.
 */
Clientnet* ClientnetCreate(const char* _serverIp, size_t _serverPort);

/**  
 * @brief Deallocate a previously allocated Clientnet
 * @param[in] _clientnet - Clientnet to be deallocated.  On success will be nulled.
 * @warning return null if _clientnet is null 
 */
void ClientnetDestroy (Clientnet** _clientnet);

/**  
 * @brief Send a message to server. 
 * @param[in] _clientnet - Clientnet to run.
 * @param[char*] _msg - message to send.
 * @param[int] _msgSize - message size, must be more then 0.
 * @return success or error code.
 * @retval CLIENT_SUCCESS on success.
 * @retval CLIENT_TRANSMITION_FAILED if failed to send the message.
 * @retval CLIENT_CLOSE_SOCKET if socket was closed by the server.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ClientErr ClientnetSendMsg (Clientnet* _clientnet ,char* _msg, size_t _msgSize);

/**  
 * @brief Reciev a message from server. 
 * @param[in] _clientnet - Clientnet to run.
 * @param[char*] _buff - buffer to copy the message to.
 * @param[int] _buffSize - buffer max size, must be more then 0.
 *                          If max size is less then data transmitted, the rest of the data will recieved in the next call for the function.
 * @return success or error code.
 * @retval CLIENT_SUCCESS on success.
 * @retval CLIENT_TRANSMITION_FAILED if failed to send the message.
 * @retval CLIENT_CLOSE_SOCKET if socket was closed by the server.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ClientErr ClientnetRecieveMsg(Clientnet* _clientnet, char* _buff, size_t _buffSize);
#endif /* clientnet.h */ 
