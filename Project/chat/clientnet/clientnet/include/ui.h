#ifndef __UI_H__ 
#define __UI_H__ 
#include "../include/ErrDefs.h" /* error typedef*/
#include "../../include/chatprotocol.h" /* Name */

/** 
 * @brief   Ui module handle interaction with user by printing to stdout and getting input from stdin.
 *          Max char input is set in the chatprotcol as VALUE_LEN - 1.
*           If input is bigger an illigal input will check and the rest will be deleted. 
 * @author Eyal Yaish
 */ 
typedef struct Ui Ui;

/**  
 * @brief Get password from user. 
 * @param[char*] _password - buffer to store password.
 * @param[char*] _txt - text to print to user.
 * @param[char*] _passLen - set the length of the input if legal.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_PARAM_ERROR if input is not legal.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs UiGetPassword(char* _password, char* _txt, char* _passLen);

/**  
 * @brief Get name from user. 
 * @param[char*] _name - buffer to store password.
 * @param[char*] _txt - text to print to user.
 * @param[char*] _passLen - set the length of the input if legal.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_PARAM_ERROR if input is not legal.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs UiGetName(char* _name, char* _txt, char* _nameLen);

/**  
 * @brief Print options and get user selection from Ui after providing menu and return its selection. 
 * @param[char*] _options[] - array of strings to print to user.
 * @param[int] _size - size of the arrays.
 * @param[char*] _txt - text to print to user.
 * @return Integer - User selection.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
int UiSelectGroupAction(char* _options[], int _size, char* _txt);

/**  
 * @brief Get group name from user. 
 * @param[char*] _groupName - buffer to store password.
 * @param[char*] _txt - text to print to user.
 * @param[char*] _passLen - set the length of the input if legal.
 * @return success or error code.
 * @retval ERR_OK on success
 * @retval ERR_PARAM_ERROR if input is not legal.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs UiGetGroupName(char* _groupName, char* _txt, char* _groupLen);

/**  
 * @brief Print txt to user. 
 * @param[char*] _txt - text to print to user.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
void UiPrintMsg(char* _txt);

/**  
 * @brief Print all groups. 
 * @param[Name] _name - array of group names to print to user.
 * @param[int] _size - size of the array.
 * @param[char*] _txt - text to print to user.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
void UiPrintGroups(Name _name[], int _size);

/**  
 * @brief Print server response to user. 
 *        if res is out of range of enum, will print undefine error.
 * @param[RespType] _res - _res type to print to user.
 */
void UiErrorHandling(RespType _res);

#endif /* Closes __UI.h__ */
