#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__
#include <stdlib.h> /* size_t */
#include "../include/ErrDefs.h" /* error typedef*/
typedef struct ClientManager ClientManager; 

/** 
 * @brief ClientManager charge of the main flow of the app by calling the different modules functions.
 * @author Eyal Yaish
 */ 

/** 
 * @brief Create a new ClientManager.
 * @param[char*] _serverIp - Server ip the app connect to. 
 * @param[size_t] _serverPort - Port number from which can connect to server.
 * @return Newly created ClientManager or null on failure
 * @warning Do not check if _serveIp is null or legal. 
 */
ClientManager* ClientManagerCreate(const char* _serverIp, size_t _serverPort);

/**  
 * @brief Deallocate a previously allocated ClientManager
 * @param[in] _clientManager - ClientManager to be deallocated.  On success will be nulled.
 * @warning return null if ClientManager is null 
 */
void ClientManagerDestroy (ClientManager** _clientManager);

/**  
 * @brief Run the flow of the app.  
 * @param[in] _clientManager - ClientManager to run.
 * @warning Do not check if _clientManager is null. 
 */
void ClientManagerRun (ClientManager* _clientManager);

#endif /* clientManager.h */ 