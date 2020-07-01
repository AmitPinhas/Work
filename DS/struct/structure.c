#include <stdio.h>
#include <string.h>

#define OK 1
#define SIZE_ARRAY 3
#define SIZE_NAME 30
#define ERROR_PARAM -1

union grade
{
     int igrade;
     char cgrade[3];
};

typedef struct person
{
     char name[SIZE_NAME];
     int id;
     int age;
     int education;
     union grade grade;
     
} person ;

int Sort_By_Id(person *_arr , int _size);
int Sort_By_Name(person *_arr , int _size);
int swap(person *person1 , person *person2);

int main()
{
     person amit , *ptr_amit=&amit , arr_person[SIZE_ARRAY];
     int index , size;
     
     amit.grade.igrade=100;
     printf("%d\n",amit.grade.igrade);
     
     size=sizeof(union grade);
     printf("%d\n",size);
     
     amit.grade.cgrade[0]='a';
     amit.grade.cgrade[1]='-';
     amit.grade.cgrade[2]='\0';
     
     puts(amit.grade.cgrade);
     
     printf("%d\n",amit.grade.igrade);
     
/*     
     printf("Please enter name , id , age , education: ");
     scanf("%s %d %d %d" , amit.name , &amit.id , &amit.age , &amit.education);
     printf("%s , %d , %d , %d\n" , ptr_amit->name , ptr_amit->id , ptr_amit->age , ptr_amit->education);
     
     for(index=0 ; index<SIZE_ARRAY ; index++)
     {
          printf("Please enter name , id , age , education: ");
          scanf("%s %d %d %d" , arr_person[index].name , &arr_person[index].id , &arr_person[index].age , &arr_person[index].education);
     }
     
     printf("original:\n");
     
     for(index=0 ; index<SIZE_ARRAY ; index++ , putchar('\n'))
     {
       printf("%s , %d , %d , %d\n" , arr_person[index].name , arr_person[index].id , arr_person[index].age , arr_person[index].education);
     }
     
     size=sizeof(arr_person)/sizeof(arr_person[0]);
     
     Sort_By_Id(arr_person , size);
     
     printf("id:\n");
     
     for(index=0 ; index<SIZE_ARRAY ; index++ , putchar('\n'))
     {
       printf("%s , %d , %d , %d\n" , arr_person[index].name , arr_person[index].id , arr_person[index].age , arr_person[index].education);
     }
     
     Sort_By_Name(arr_person , size);
     
     printf("name:\n");
     
      for(index=0 ; index<SIZE_ARRAY ; index++ , putchar('\n'))
     {
       printf("%s , %d , %d , %d\n" , arr_person[index].name , arr_person[index].id , arr_person[index].age , arr_person[index].education);
     } */
     
     return OK;
}

int Sort_By_Id(person *_arr,int _size)
{
     int index , change=1 , index2 ;
     person tmp;
     
     if(_arr == NULL || _size<=0)
     {
          return ERROR_PARAM;
     }
     
     while(change)
     {
          for(index=0 , index2=index+1 ,change=0 ; index2<_size ; index++ , index2++)
          {
               if(_arr[index].id > _arr[index2].id)
               {              
               swap(&_arr[index] , &_arr[index2]);
               change=1;
               }
          }
     }
     
     return OK;
}

int Sort_By_Name(person *_arr , int _size)
{
     int index , change=1 , index2 ;
     person tmp;
     
     if(_arr == NULL || _size<=0)
     {
          return ERROR_PARAM;
     }     
     
     while(change)
     {
          for(index=0 , index2=index+1 ,change=0 ; index2<_size ; index++ , index2++)
          {
               if(strcmp(_arr[index].name, _arr[index2].name) > 0)
               {
                    swap(&_arr[index] , &_arr[index2]);
                    change=1;
               }
          }
     }
     
     return OK;
}

int swap(person *person1 , person *person2)
{
     person tmp;

               tmp = *person1;
          *person1 = *person2;
          *person2 = tmp;     
     
     return OK;
}

/* Name: Amit Pinhas */
