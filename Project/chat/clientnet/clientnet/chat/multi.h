#ifndef __MULTI_H__
#define __MULTI_H__
#include <stdlib.h> /* size_t*/
#include "NetErr.h" /*Err defines */

/** 
 * @brief Create an app to recieve messages from in multicasting using udp protocol. 
 * The app recieve messages in MSG structure based on chatprotocol, and will print by name and text. 
 * Messages and Name should not contain more the 255 characters.
 * @author Eyal Yaish
 */ 
typedef struct Multicast Multicast;

/**  
 * @brief Create a newly multicast message reciever. When created, it send the it's process pid to the msgId que given.
 * @param[size_t] _port - Port number from which to recieve the messages
 * @param[char*] _groupAddr - Ip adress of multicast type to recievce messages from.
 * @param[int] _msgId - Message que id to its pid.
 * @return Multicast* - on success
 * @retval NULL on fail or if any of the pointers is null 
 *
 * @warning Giving correct message queue id is user responsibility. If failed create continue normaly.
 */
Multicast* MultiCreate (size_t _port, const char* _groupAdrr, int _msgId);

/**  
 * @brief Deallocate a previously allocated multicast
 * @param[in] _multi - Multicast object to be deallocated.  On success will be nulled.
 * @warning return null if _multi is null 
 */
void MultiDestroy(Multicast** _multi);

/**  
 * @brief Run the multicats and print to screen every message recieve. 
 * @param[in] _multi - Multicast object to run.
 * @return success or error code.
 * @retval NET_ERR_SUCCESS  on success.
 * @retval NET_ERR_NOT_INITIALIZED  error,  Multicast object not initilized.
 *
 */
NetErr MultiRun(Multicast* _multi);

#endif /* multi.h */