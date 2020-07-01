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
     ERR_DUPLICATED_DATA,
     STACK_EMPTY
  
}ADTErr;

#endif /* __ADTDEFS_H__ */
