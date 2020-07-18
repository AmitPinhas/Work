#ifndef __ENTRANCE_H__ 
#define __ENTRANCE_H__ 
#include "../include/ErrDefs.h" /* error typedef*/
#include "../../include/chatprotocol.h" /* signup struct */

/** 
 * @brief Run the entrance functions, signup and login
 * @author Eyal Yaish
 */ 

typedef enum EntranceOpt {
    ENTRANCE_SIGNUP = 1,
    ENTRACE_LOGIN,
    ENTRANCE_EXIT_APP                
} EntranceOpt;

/**  
 * @brief Get name and password from user and save it in _signup given. 
 * @param[in] _signUp - _signUp structure to insert details.
 * @return success or error code.
 * @retval ERR_OK on success.
 * @retval ERR_PARAM_ERROR if username or password given from user is empty.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs EntranceSignup (SignUp* _signUp);

/**  
 * @brief Get name and password from user and save it in _login given. 
 * @param[in] _login - _login structure to insert details.
 * @return success or error code.
 * @retval ERR_OK on success.
 * @retval ERR_PARAM_ERROR if username or password given from user is empty.
 * @warning The func doesn't check pointers for null, and it is user responsibilty.
 */
ErrDefs EntranceLogIn (LogIn* _login);

/**  
 * @brief Send the entrance menu option to ui to print and return the user selection matching Entrance option.
 * @return User selection.
 * @retval EntranceOpt selection given.
 * @warning The func doesn't check if selection is in range of EntranceOpt.
 */
EntranceOpt EntranceMenu();

#endif /* Closes __entrance.h__ */
