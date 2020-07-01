#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "add.h"
#include "sub.h"
#include "multiplication.h"

int main(int argc, char **argv) 
{
   void *lib_handle_add , *lib_handle_sub , *lib_handle_mul ;
   int (*fAdd)(int , int);
   int (*fSub)(int , int); 
   int (*fMultiplication)(int , int);     
   int x;
   char *error;

   lib_handle_add = dlopen("/opt/lib/libadd.so", RTLD_LAZY);
   if (!lib_handle_add) 
   {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
   }

   lib_handle_sub = dlopen("/opt/lib/libsub.so", RTLD_LAZY);
   if (!lib_handle_sub) 
   {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
   }
   
   lib_handle_mul = dlopen("/opt/lib/libmul.so", RTLD_LAZY);
   if (!lib_handle_mul) 
   {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
   }   
   
   fAdd = dlsym(lib_handle_add, "add");
   if ((error = dlerror()) != NULL)  
   {
      fprintf(stderr, "%s\n", error);
      exit(1);
   }   
	
   fSub = dlsym(lib_handle_sub, "sub");
   if ((error = dlerror()) != NULL)  
   {
      fprintf(stderr, "%s\n", error);
      exit(1);
   }
   
   fMultiplication = dlsym(lib_handle_mul, "multiplication");
   if ((error = dlerror()) != NULL)  
   {
      fprintf(stderr, "%s\n", error);
      exit(1);
   }   


   x = (*fAdd)(5 , 6);
   printf("ValxAdd=%d\n",x);

   x = (*fSub)(10 , 5);
   printf("ValxSub=%d\n",x);

   x = (*fMultiplication)(5 , 6);
   printf("ValxMultiplication=%d\n",x);

   dlclose(lib_handle_add);   
   dlclose(lib_handle_sub);  
   dlclose(lib_handle_mul);  
         	
	return 0 ;

}
