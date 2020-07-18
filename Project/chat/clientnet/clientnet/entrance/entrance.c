#include <stdlib.h> /* NULL */
#include <string.h> /* strcpy, strlen */
#include "../include/ErrDefs.h" /* error enum */
#include "../include/entrance.h" /* typedef */
#include "../include/ui.h" /* ui fucntion */


#define GET_NAME_TXT            "Please enter name"
#define GET_PASSWORD_TXT        "Please enter password"
#define SELECTION_SIZE          3

static void SetNameValues(Name* _name);
static void SetPasswordValues(Password* _password);
/******************************************************/
/************     Public      *************************/
/******************************************************/
ErrDefs EntranceSignup (SignUp* _signUp)
{
    if (ERR_PARAM_ERROR == UiGetName(_signUp->m_userName.m_value, GET_NAME_TXT, &_signUp->m_userName.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    SetNameValues(&_signUp->m_userName);
    
    if (ERR_PARAM_ERROR == UiGetPassword(_signUp->m_password.m_value, GET_PASSWORD_TXT, &_signUp->m_password.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    SetPasswordValues(&_signUp->m_password);
    return ERR_OK;
}

ErrDefs EntranceLogIn (LogIn* _login)
{
    if (ERR_PARAM_ERROR == UiGetName(_login->m_userName.m_value, GET_NAME_TXT, &_login->m_userName.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    SetNameValues(&_login->m_userName);
    
    if (ERR_PARAM_ERROR == UiGetPassword(_login->m_password.m_value, GET_PASSWORD_TXT, &_login->m_password.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    SetPasswordValues(&_login->m_password);
    return ERR_OK;
}

EntranceOpt EntranceMenu()
{
    char* option[SELECTION_SIZE] = {"Sign up", "Log in", "Exit"};
    int selection = 0;
    selection = UiSelectGroupAction(option, SELECTION_SIZE, "\nChoose Your action:");
    return selection;
}
/******************************************************/
/************     Locals      *************************/
/******************************************************/
static void SetNameValues(Name* _name)
{
    _name->m_type = NAME;
    _name->m_value[_name->m_length - 1] = '\0';
    return;
}

static void SetPasswordValues(Password* _password)
{
    _password->m_type = PASSWORD;
    _password->m_value[_password->m_length - 1] = '\0';
    return; 
}

