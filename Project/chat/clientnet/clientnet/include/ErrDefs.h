#ifndef __ERRDEFS_H__ 
#define __ERRDEFS_H__ 

typedef enum ErrDefs{
        ERR_OK,
        ERR_GENERAL,
        ERR_NOT_INITIALIZED,
        ERR_SYS_ERROR,
        ERR_PARAM_ERROR,
        ERR_ALLOCATION_FAILED, 
        ERR_GROUP_CREATE_FAILED,
        ERR_GROUP_NOT_EXIST,
        ERR_OVERFLOW,
        ERR_EMPTY
}ErrDefs;

#endif /* Closes ErrDefs.h */
