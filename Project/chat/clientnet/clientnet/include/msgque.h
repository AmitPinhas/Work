#ifndef __MSG_QUE_H__
#define __MSG_QUE_H__
#include "../include/ErrDefs.h" /* error typedef*/
#include <sys/types.h>  /* pid_t */

/** 
 * @brief   Create a message queue with unique identity based on given path.
 *          The message queue is for sending the pid of the process that use it.
 * @author Eyal Yaish
 */

typedef struct MsgBuf {
    long        m_type;
    pid_t       m_pid;
}MsgBuf;

/** 
 * @brief Create a new msgque and store its id to the _msdId pointer..
 * @param[char*] _path - path to file for creating a unique key. 
 * @param[int*] _msgId - Pointer to integer to store the newMsg id.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_SYS_ERROR if failed to create the message queue.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs MsgQueCreate(const char* _path, int* _msgId);

/**  
 * @brief Remove the message queue identified by the msgId from the system.
 * @param[int] _msgId - message queue id to remove.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_SYS_ERROR if failed to remove the message queue.
 */
ErrDefs MsgQueDestroy (int _msgId);

/**  
 * @brief Write the buffer to the message queue in the given channel. 
 * @param[int] _msgId - message queue id to sens to.
 * @param[MsgBuf] _buff - _buffer that containe the channel and the pid to send.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_SYS_ERROR if failed to send the message.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs MsgQueWrite(int _msgId, MsgBuf _buff);

/**  
 * @brief Read a buffer from the message queue in the given channel. 
 * @param[int] _msgId - message queue id to sens to.
 * @param[MsgBuf*] _buff - pointer to _buffer to store the recieved message.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_SYS_ERROR if failed to recieve the message.
 */
ErrDefs MsgQueRead(int _msgId, MsgBuf* _buff);
#endif /* msgQue.h */