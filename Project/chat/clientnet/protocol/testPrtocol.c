#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "../include/protocol.h"
#include "../include/chatprotocol.h"
#define NAME_MSG        "EYAL"
#define PASSWORD_MSG    "mmdj"
#define BUFF_SIZE   1024

void TestSign()
{
    char* msg;
    SignUp sign;
    int size = 0;

    msg = (char*) malloc (sizeof(char)*BUFF_SIZE);
    sign.m_type = SIGNUP;
    sign.m_length = 0;
    sign.m_userName.m_type = NAME;
    sign.m_password.m_type = PASSWORD;
    sign.m_userName.m_length = strlen(NAME_MSG);
    sign.m_password.m_length = strlen(PASSWORD_MSG);
    strcpy(sign.m_userName.m_value, NAME_MSG);
    strcpy(sign.m_password.m_value, PASSWORD_MSG);
    printf("%s\n", sign.m_userName.m_value);
    printf("%s\n", sign.m_password.m_value);
    ProtocolPackSignup(&sign, &msg, &size);
    msg -= size;

    memset(&sign, 0, sizeof(sign));
    ProtocolUnpackSignup(&sign, &msg);
    printf("%s\n", sign.m_userName.m_value);
    printf("%s\n", sign.m_password.m_value);

}

void TestRes()
{
    char buf[BUFF_SIZE];
    char* msg = buf;
    Response res;
    Response resTemp;
    int size = 0;

    res.m_type = RESPONSE;
    res.m_length = 1;
    res.m_value = INVALID_USERNAME;
    printf("%d\n", res.m_type);
    printf("%d\n", res.m_value);
    ProtocolPackResponse(&res, &msg, &size);
    msg -= size;
    ProtocolUnpackResponse(&resTemp, &msg);
    printf("%d\n", resTemp.m_type);
    printf("%d\n", resTemp.m_value);

}

int main(){

    TestSign();
    TestRes();
}