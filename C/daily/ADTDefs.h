#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__

typedef enum
{
     /* General ADT Errors */
     ERR_OK                   =0,
     ERR_GENERAL,
     ERR_NOT_INITIALIZED,
     ERR_ALLOCATION_FAILED,
     ERR_REALLOCATION_FAILED,
     ERR_UNDERFLOW,
     ERR_OVERFLOW,
     ERR_WORNG_INDEX,
     STACK_EMPTY
         /* Vector Errors */
}ADTErr;

#endif /* __ADTDEFS_H__ */
