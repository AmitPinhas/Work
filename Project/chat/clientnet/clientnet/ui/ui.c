#include <stdio.h> /* printf */
#include <string.h> /* strcpy */ 
#include "../include/ui.h"
#define TRUE                    1
#define FAILED                  0
#define ILLIGAL_INPUT    "Illigal input"
#define ILLIGAL_NAME_TXT        "illigal name"

static int IsLegalInput(const char* _name, char* _len);
static void ClearStdin();
/******************************************************/
/************     Public      *************************/
/******************************************************/
ErrDefs UiGetPassword(char* _password, char* _txt, char* _passLen)
{
    printf("\n%s\n", _txt);
    fgets(_password, VALUE_LEN - 1, stdin);
    if (FAILED == IsLegalInput(_password, _passLen))
    {
        return ERR_PARAM_ERROR;
    }
    return ERR_OK;
}

ErrDefs UiGetName(char* _name, char* _txt, char* _nameLen)
{
    printf("\n%s\n", _txt);
    fgets(_name, VALUE_LEN - 1, stdin);
    if (FAILED == IsLegalInput(_name, _nameLen))
    {
        return ERR_PARAM_ERROR;
    }
    return ERR_OK;
}

int UiSelectGroupAction(char* _options[], int _size, char* _txt)
{
    int i = 0;
    int selection = 0;
    printf("\n%s\n", _txt);
    for ( ;i < _size; ++i)
    {
        printf("%d. %s\n", i + 1, _options[i]);
    }
    printf("\n");
    selection = fgetc(stdin) - '0';
    fgetc(stdin);
    return selection;
}

ErrDefs UiGetGroupName(char* _groupName, char* _txt, char* _groupLen)
{
    printf("%s\n", _txt);
    fgets(_groupName, VALUE_LEN - 1, stdin);
    if (FAILED == IsLegalInput(_groupName, _groupLen))
    {
        return ERR_PARAM_ERROR;
    }
    return ERR_OK;
}

void UiPrintMsg(char* _txt)
{
    printf("%s\n", _txt);
    return;
}

void UiErrorHandling(RespType _res)
{
    switch (_res)
    {
    case SUCCESS:
        UiPrintMsg("Action Success");
        break;
    case INVALID_USERNAME:
        UiPrintMsg("Invalid username ");
        break;
    case INVALID_PASSWORD:
        UiPrintMsg("Invalid password ");
        break;
    case EXISTING_USERNAME:
        UiPrintMsg("Username Exist");
        break;
    case INVALID_GROUP_ID:
        UiPrintMsg("Invalid Group Id ");
        break;
    case USER_ALREADY_IN_USE:
        UiPrintMsg("User is already in use");
        break;
    case SERVER_ERROR:
        UiPrintMsg("Server user error ");
        break;
    case MULTI_ADDRESS_DEPLETED:
        UiPrintMsg("Can't create more groups");
        break;
    default:
        UiPrintMsg("Undefined error");
        break;
    }
    return;
}

void UiPrintGroups(Name _name[], int _size)
{
    int i = 0;
    
    for ( ; i < _size; ++i)
    {
        printf("%d. %s\n", i+1, _name[i].m_value);
    }
    return;
}

/******************************************************/
/************     Locals      *************************/
/******************************************************/
static int IsLegalInput(const char* _name, char* _len)
{
    *_len = strlen(_name);

    if(0 >= *_len)
    {
        printf("%s\n", ILLIGAL_INPUT);
        ClearStdin();
        return FAILED;
    }
    return TRUE;
}

static void ClearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    { 

    }
    return;
}