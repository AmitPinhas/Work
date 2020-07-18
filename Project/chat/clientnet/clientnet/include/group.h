#ifndef __GROUP_H__
#define __GROUP_H__
#include "../include/ErrDefs.h" /* error typedef*/

/** 
 * @brief   Group modlue handle the different groups the user is in charge of. It keep the groups in a hash-map database.
 *          When joing or creating a group, the chat proccess open automatically. 
 *          The module communicating with the different chat proccess by message que.       
 *          When the user leave a group, it kills it's chat proccess. 
 * @author Eyal Yaish
 */ 
typedef struct GroupManager GroupManager;

typedef enum GroupAction {
    CREATE_NEW_GROUP = 1,   /** Create a group */
    GET_ALL_GROUPS,         /** Get all exisiting groups */
    JOIN_A_GROUP,           /** Join group */
    LEAVE_A_GROUP,          /** Leave group */
    LOG_OUT,                /** Logout */
    EXIT_APP                /** Logout and exit app */
}GroupAction ;

/**  
 * @brief Create a newly groupManager.
 * @return groupManager* - on success
 * @retval NULL on fail.
 */
GroupManager* GroupManagerCreate();

/**  
 * @brief Deallocate a previously allocated groupManager
 * @param[in] _gManger - groupManager to be deallocated.  On success will be nulled.
 * @warning return null if _gManger is null 
 */
void GroupManagerDestroy (GroupManager** _gManger);

/**  
 * @brief Get user selection from Ui after providing menu and return its selection. 
 * @param[in] _gManger - groupManager to run.
 * @return Integer - User activity selection.
 */
int GroupManagerSelection(GroupManager* _gManger);

/**  
 * @brief Get group name from ui. 
 * @param[char*] _groupName - buffer to place group name.
 * @param[char*] _nameSize - char* to set the name length.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_PARAM_ERROR if name entered from user is not correct.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs GroupManagerGetName(char* _groupName, char* _nameLen);

/**  
 * @brief Create a new group and save it to data base. 
 * @param[in] _gManger - groupManager to create the group.
 * @param[char*] _groupName - name for the new group.
 * @return success or error code.
 * @retval ERR_OK on success.
 * @retval ERR_ALLOCATION_FAILED if there is no memory for new group.
 * @retval ERR_GROUP_CREATE_FAILED if failed to insert to database.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs GroupManagerCreateGroup(GroupManager* _gManger,const char* _groupName, char* _userName, const char* _ip);

/**  
 * @brief Leave a group and remove it from database. Leaving a group also closes the chat apps. 
 * @param[in] _gManger - groupManager to run.
 * @param[char*] _groupName - name of the group to leave.
 * @return success or error code.
 * @retval ERR_OK on success.
 * @retval ERR_GROUP_NOT_EXIST if the user is not part of the group.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs GroupManagerLeaveGroup (GroupManager* _gManger,const char* _groupName);

/**  
 * @brief Leave all the groups of the user. 
 * @param[in] _gManger - groupManager to create the group.
 * @return success or error code.
 * @retval ERR_OK on success.
 * @retval ERR_ALLOCATION_FAILED if after removing db, falied to create new db.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs GroupManagerLeaveAllGroups (GroupManager* _gManger);

#endif /* group.h */