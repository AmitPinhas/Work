#ifndef __LIST_H__
#define __LIST_H__

#define TRUE 1
#define FALSE 0

typedef struct Person
{
     int m_id ; /* Primary Key */
     char m_name[128];
     int m_age;
     struct Person* m_next;
}Person;

/*
  Description: Inserting an new person into the head of the array.
  Input: Pointer to head and pointer to the new person.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head - if the pointer to the new person is null.
  Comlexity: O(1) .    
  Warning : There is no reference to the key .
*/
Person* ListInsertHead(Person *_head ,Person *_p);

/*
  Description: Removing the first person in the array.
  Input: Pointer to head and pointer to pointer to item.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head - if the pointer to the head is null , if pointer to item is null or pointer to pointer to item is null. 
  Comlexity: O(1) .    
*/
Person* ListRemoveHead(Person *_head ,Person **_item);

/*
  Description: Inserting new person by key to the array.
  Input: Pointer to head , pointer to the new person and key.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head - if the pointer to the new person is null , if the key is already in the array.
  Comlexity: O(n) .    
  Warning : the key must be unique .
*/
Person* ListInsertByKey(Person *_head, int _key, Person *_p);

/*
  Description: Inserting new person by key to the array.
  Input: Pointer to head , pointer to the new person and key.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head - if the pointer to the new person is null , if the key is already in the array.
  Comlexity: O(n) .  
  Warning : the key must be unique .
      
*/
Person* ListInsertByKeyRec(Person *_head, int _key , Person *_p);

/*
  Description: Remove person by key from the array.
  Input: Pointer to head , key and pointer to pointer to new variable from type person.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head -if the pointer to the head is null , if pointer to variable is null or pointer to pointer to variable is null. 
  Comlexity: O(n) .      
*/
Person* ListRemoveByKey(Person *_head , int _key , Person **_p);

/*
  Description: Remove person by key from the array.
  Input: Pointer to head , pointer to the new person and pointer to pointer to new variable from type person.
  Output: Pointer to the new head / pointer to old head .
  Error: pointer to old head -if the pointer to the head is null , if pointer to variable is null or pointer to pointer to variable is null.  
  Comlexity: O(n) .     
*/
Person* ListRemoveByKeyRec(Person *_head , int _key , Person **_p);

/*
  Description: print the list.
  Input: Pointer to head .
  Output: no output .
  Error: no error .      
*/
void PrintList(Person *_head);

/*
  Description: flip the list.
  Input: Pointer to head .
  Output: pointer to the flip list / null .
  Error: null - if the pointer to the list is null .      
*/
Person* Flip(Person *_head);

/*
  Description: check if a loop exists in the linked list or does not exist .
  Input: Pointer to the head of the linked list .
  Output: TRUE / FALSE .
  Error: TRUE - if there is a loop in the list .
         FALSE - no loop in the list or pointer null .
  Comlexity: O(n) .     
*/
int DetectLoop(Person *_head);


#endif /* __LIST_H__ */



