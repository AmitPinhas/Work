#include <stdio.h>
#include <string.h> /* strcpy */
#include <stdlib.h> /* size_t */

#define SIZE_NAME 100
#define SIZE_ARRAY 3
#define SIZE_LINE 200
#define SIZE_WORD 15

typedef struct Person{
     int m_age;
     char name[SIZE_NAME];
}Person;

int Exercise2(FILE *_file);
int Exercise4(int _nLines , FILE *_file);
int Exercise6(char *_nameFile , char *_name);
int BinaryWrite(Person *_arrPerson , size_t _count , FILE *_file);
int BinaryRead(Person *_arrPerson , size_t _count , FILE *_file);

int main()
{
     Person arrPersons[SIZE_ARRAY] , ArrRead[SIZE_ARRAY]; 
     FILE *filePtr , *filePtrBinary , *ptrBinari;
     arrPersons[0].m_age = 10 ;
     arrPersons[1].m_age = 11 ;    
     arrPersons[2].m_age = 12 ;
     strcpy(arrPersons[0].name , "Sergey");
     strcpy(arrPersons[1].name , "Lior");   
     strcpy(arrPersons[2].name , "Yosef");     
     
     filePtr = fopen("Persons.txt" , "r+");
     if ( NULL == filePtr)
     {
          puts("file ptr null");
     }     
     filePtrBinary = fopen("PersonsBinary.txt" , "w");
     if ( NULL == filePtrBinary )
     {
         puts("file ptr null"); 
     }
     BinaryWrite(arrPersons , SIZE_ARRAY , filePtrBinary); 
     fclose(  filePtrBinary);  
     ptrBinari = fopen("PersonsBinary.txt" , "r");
     if ( NULL == ptrBinari)
     {
          puts("file ptr null");
     }     
     BinaryRead(ArrRead , SIZE_ARRAY , ptrBinari);
     
     Exercise2(filePtr);
     Exercise4(1 , filePtr);
     Exercise6("Yosi.txt" , "amit");
     BinaryWrite(arrPersons , SIZE_ARRAY , filePtrBinary);
     
     BinaryRead(ArrRead , SIZE_ARRAY , ptrBinari);
     
     fclose(filePtr);  
     fclose(filePtrBinary);         
     return 1;
}

int Exercise2(FILE *_file)
{
     Person arrPersons[SIZE_ARRAY] , ArrRead[SIZE_ARRAY];
     int index;

     arrPersons[0].m_age = 10 ;
     arrPersons[1].m_age = 11 ;    
     arrPersons[2].m_age = 12 ;
     strcpy(arrPersons[0].name , "Sergey");
     strcpy(arrPersons[1].name , "Lior");   
     strcpy(arrPersons[2].name , "Yosef");

     
     for ( index=0 ; index<SIZE_ARRAY ; index++)
     {
          fprintf(_file , "%s  %d\n" , arrPersons[index].name , arrPersons[index].m_age);
     }
     
     fseek(_file , 0 , SEEK_SET);
     
     for ( index=0 ; index<SIZE_ARRAY ; index++)
     {
          fscanf(_file , "%s%d" , ArrRead[index].name , &ArrRead[index].m_age);
     }     
     for ( index=0 ; index<SIZE_ARRAY ; index++)
     {
          printf("name: %s  age: %d\n" , ArrRead[index].name , ArrRead[index].m_age);
     } 
     
     return 1;
}

int Exercise4(int _nLines , FILE *_file)
{
     char line[SIZE_LINE] , ch ;
     int index=2 , count=0 , ind;
         
     fseek(_file , -index , SEEK_END);
     while (( (ftell(_file)) != 0) && (_nLines != 0 ) )
     {
          if (fgetc(_file) == '\n')
          {
            _nLines--;  
          }
          index++;
          fseek(_file , -index , SEEK_END);
     }
     
     fseek(_file , 2 , SEEK_CUR);
     fgets(line , SIZE_LINE , _file);

     while(!feof(_file))
     {
          fputs(line , stdout);
          fgets(line , SIZE_LINE , _file);
     }
     
     
     return 1;
}

int Exercise6(char *_nameFile , char *_name)
{
     FILE *ptrFile;
     char word[SIZE_WORD];
     int count=0;
     
     ptrFile = fopen (_nameFile , "r");
     if ( NULL == ptrFile)
     {
          puts("File Error");
     }
      
     while(!feof(ptrFile))
     {
          fscanf(ptrFile , "%s" , word);
          
          if ( strcmp(word , _name) == 0 )
          {
               count++;
          }         
     }
     fscanf(ptrFile , "%s" , word);
          
     if ( strcmp(word , _name) == 0 )
      {
           count++;
      }     
      
      printf("In file %s the word %s appeared %d times\n" ,  _nameFile , _name , count);
     
     fclose(ptrFile);
     return 1;
}

int BinaryWrite(Person *_arrPerson , size_t _count , FILE *_file)
{
  size_t size ;
  
  size = fwrite(_arrPerson , sizeof(Person) , _count , _file);
  
  printf("%ld\n" , size);
  
  return 1;
}

int BinaryRead(Person *_arrPerson , size_t _count , FILE *_file)
{
  size_t size ;
  int index;
  
  size = fread(_arrPerson , sizeof(Person) , _count , _file);
  
  printf("%ld\n" , size);
  
   for ( index=0 ; index<SIZE_ARRAY ; index++)
     {
          printf("name: %s  age: %d\n" , _arrPerson[index].name , _arrPerson[index].m_age);
     }   
  
  return 1;
}
