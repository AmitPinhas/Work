#include<stdio.h>/* for printing */
#include<stdlib.h>/* for allocation */

#include"hash.h"
#include"dyVec.h"
#include"dll.h"
#include"itr.h"
#include"functions.h"

#define INC 5
#define MAG_NUM 0xBEEFBEEF
#define GET_IND(map,key)(map->m_hashFunc(key)%(map->m_capacity))
#define IS_MAP_NOT_INITIALIZED(map)(!map || (map)->m_magNum != MAG_NUM)
typedef enum{FALSE,TRUE=!FALSE}Bool;

typedef struct Pair{    
    void* m_item;
	void* m_key;
}Pair;


struct HashMap{

    size_t m_magNum;
    List** m_listArrMap;
	size_t m_capacity;
	HashFunction m_hashFunc;
	EqualityFunction m_cmpKeyFunc;		
};

typedef struct ForEachStruct{
	KeyValueActionFunction m_keyValAct;
	void* m_context;
}ForEachStruct;

typedef struct DestroyStruct{

	void (*m_keyDestroy)(void* _key);
	void (*m_valDestroy)(void* _value);
		
}DestroyStruct;

typedef struct KeyCmp{
   
    void* m_key;
	EqualityFunction m_cmpKeyFunc;
		
}KeyCmp;

static int GetNumOfChains(const HashMap* _map);
static int GetMaxChainLength(const HashMap* _map);
static float GetAvarageChainLength(const HashMap* _map);

static void* HashGetKey(Pair* _node);

static Bool IsPrime(size_t _num);
static size_t NextPrime(size_t _num) ;

static void HashMapInit(HashMap* _map, List** _listArr,size_t _capacity, HashFunction _hashFunc,  EqualityFunction _keysEqualFunc);

static int HashDestroyFunc(void * _element, void* _context);
static void DestroyAllBuckets(HashMap*_map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

static size_t ForEachBucket(const HashMap* _map, KeyValueActionFunction _action, void* _context);

static Pair* HashPairCreate(void* _key, void* _value);
static ListItr FindKey(const HashMap* _map, const void* _key);

static void HashCopyAllBuckets(List** _dest, List** _src, size_t _oldCap,size_t _newCap, HashFunction _hashFunc);
static void HashCopyBucket(List** _dest, List** _src, size_t _oldCap,size_t _newCap, HashFunction _hashFunc, int _ind);

static int HashMapInnerForEach(void * _element, void* _context);
static int PredicateFunc(void * _element, void* _context);
/* API */
HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* map;
	List** listArr;

	if(!_hashFunc || !_keysEqualFunc)
	{
		return NULL;
	}

	_capacity = NextPrime(_capacity);

	listArr = (List**)calloc(_capacity,sizeof(List*));
	if(!listArr)
	{
		return NULL;
	}

	map = (HashMap*)malloc(sizeof(HashMap));
	if(!map)
	{
		free(listArr);
		return NULL;
	}

	HashMapInit(map,listArr,_capacity,_hashFunc,_keysEqualFunc);	
	map->m_magNum = MAG_NUM;

	return map;
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(!_map || IS_MAP_NOT_INITIALIZED(*_map))
	{
		return;
	}
	
	(*_map)->m_magNum = 0xDEADBEEF;
	
	DestroyAllBuckets(*_map, _keyDestroy,_valDestroy);

	free(*_map);
	*_map = NULL;

	return;
}

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	Pair* newNode;
	size_t bucketIndex;
	void* pValue = NULL;
	
	if(IS_MAP_NOT_INITIALIZED(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(!_key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = GET_IND(_map,_key);
	if(!_map->m_listArrMap[bucketIndex])
	{
		_map->m_listArrMap[bucketIndex] = ListCreate();
	}
	
	if(HashMapFind(_map, _key, &pValue) == MAP_SUCCESS)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	newNode = HashPairCreate((Pair*)_key,(Pair*)_value);
	if(!newNode)
	{
		return MAP_ALLOCATION_ERROR;
	}	
	
	ListPushHead(_map->m_listArrMap[bucketIndex],newNode);
	
	return MAP_SUCCESS;
}

MapResult HashMapFind(const HashMap* _map, const void* _key, void** _pValue)
{	
	ListItr isFound;
	int bucketIndex;
	
	if(IS_MAP_NOT_INITIALIZED(_map) || !_pValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(!_key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = GET_IND(_map,_key);
	isFound = FindKey(_map,_key);
	
	if(isFound)
	{				
		if(isFound  != ItrEnd(_map->m_listArrMap[bucketIndex]))
		{
			*_pValue = ((Pair*)ItrGet(isFound))->m_item;
			return MAP_SUCCESS;
		}
	}

	return MAP_KEY_NOT_FOUND_ERROR;
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pValue)
{
	ListItr isFound;
	int bucketIndex;

	if(IS_MAP_NOT_INITIALIZED(_map) || !_pValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	if(!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = GET_IND(_map,_searchKey);
	isFound = FindKey(_map,_searchKey);
	
	if(isFound)
	{					
		if(isFound  != ItrEnd(_map->m_listArrMap[bucketIndex]))
		{
			*_pValue = ((Pair*)ListItrRemove(isFound))->m_item;
			return MAP_SUCCESS;
		}
	}
	else
	{
		return MAP_UNDERFLOW_ERROR;
	}
	
	return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMapSize(const HashMap* _map)
{
	register int i;
	size_t count=0;
	if(IS_MAP_NOT_INITIALIZED(_map))
	{
		return 0;
	}

	for(i=0;i<_map->m_capacity;++i)
	{
		count += ListSize(_map->m_listArrMap[i]);
	}
	return count;
}

MapResult HashMapRehash(HashMap *_map, size_t newCapacity)
{
	List** newList;
	register int i;
	
	if(IS_MAP_NOT_INITIALIZED(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	newCapacity = NextPrime(newCapacity);
	
	newList = (List**)calloc(newCapacity,sizeof(List*));
	if(!newList)
	{
		return MAP_ALLOCATION_ERROR;
	}
	/*FIXME use for each with contex as struct for new list** */
	
	HashCopyAllBuckets(newList,_map->m_listArrMap,(_map)->m_capacity,newCapacity,_map->m_hashFunc);
	
	for(i=0;i<(_map)->m_capacity;++i)
	{		
		ListDestroy(&(_map->m_listArrMap[i]),NULL);
	}
	
	_map->m_listArrMap = newList;
	_map->m_capacity = newCapacity;
	
	return MAP_SUCCESS;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{		
	if(IS_MAP_NOT_INITIALIZED(_map) || !_action)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	return ForEachBucket(_map,_action,_context);
}

#ifndef NDEBUG

MapStats HashMapGetStatistics(const HashMap* _map)
{
	MapStats stts;
	
	stts.numberOfBuckets = 0;
	stts.numberOfChains = 0;
	stts.maxChainLength = 0;
	stts.averageChainLength = 0;
	
	if(!_map || _map->m_magNum != MAG_NUM)
	{		
		return stts;
	}
	
	stts.numberOfBuckets = _map->m_capacity;
	stts.numberOfChains = GetNumOfChains(_map);
	stts.maxChainLength = GetMaxChainLength(_map);
	stts.averageChainLength = GetAvarageChainLength(_map);
	return stts;
}

#endif /* NDEBUG */

/* Static */
static size_t ForEachBucket(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	register int i;
	ListItr begin,end,stopped;
	size_t count=0;
	
	ForEachStruct forEach;
	
	forEach.m_keyValAct = _action;
	forEach.m_context = _context;
	
	for(i=0;i<_map->m_capacity;++i)
	{
		begin = ItrBegin(_map->m_listArrMap[i]);
		end = ItrEnd(_map->m_listArrMap[i]);
		if(begin)
		{			
			stopped = ListItrForEach(begin,end,HashMapInnerForEach,&forEach);
			while(begin!=stopped)
			{
				count++;
				begin = ItrNext(begin);
			}
		}
	}
	
	return count;
}

static void DestroyAllBuckets(HashMap*_map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	register int i=0;
	ListItr start=NULL,end=NULL;
	DestroyStruct DestroyFunc;

	DestroyFunc.m_keyDestroy = _keyDestroy;
	DestroyFunc.m_valDestroy = _valDestroy;

	for(i=0;i<(_map)->m_capacity;++i)
	{			
		start = ItrBegin((_map)->m_listArrMap[i]);
		end = ItrEnd(((_map)->m_listArrMap[i]));
		
		if(start)
		{
			ListItrForEach(start,end,HashDestroyFunc,&DestroyFunc);
		}
		ListDestroy(&(_map->m_listArrMap[i]),NULL);
	}
}

static int HashMapInnerForEach(void * _element, void* _context)
{
	void* elementVal = ((Pair*)_element)->m_item;
	void* elementKey = ((Pair*)_element)->m_key;
	void* context = ((ForEachStruct*)_context)->m_context;
	KeyValueActionFunction act = ((ForEachStruct*)_context)->m_keyValAct;
	
	return act(elementKey,elementVal,context);
}

static ListItr FindKey(const HashMap* _map, const void* _key)
{	
	ListItr begin,end,isFound;
	int bucketIndex;	
	KeyCmp keyCmp;
	
	keyCmp.m_cmpKeyFunc = _map->m_cmpKeyFunc;
	keyCmp.m_key = (void*)_key;
	
	bucketIndex = GET_IND(_map,_key);	
	begin = ItrBegin(_map->m_listArrMap[bucketIndex]);
	end = ItrEnd(_map->m_listArrMap[bucketIndex]);	
	
	if(begin)
	{	
		isFound = ListItrFindFirst(begin,end, PredicateFunc,&keyCmp);		
		return isFound;
	}

	return NULL;
}

static int PredicateFunc(void * _element, void* _context)
{
	void* contextKey = ((KeyCmp*)_context)->m_key;
	void* elementKey = ((Pair*)_element)->m_key;
	
	return ((KeyCmp*)_context)->m_cmpKeyFunc(contextKey,elementKey);
}

static int HashDestroyFunc(void * _element, void* _context)
{
	void* elementVal = ((Pair*)_element)->m_item;
	void* elementKey = ((Pair*)_element)->m_key;
	
	if(((DestroyStruct*)_context)->m_keyDestroy)
	{
		((DestroyStruct*)_context)->m_keyDestroy(elementKey);	
	}
	
	if(((DestroyStruct*)_context)->m_valDestroy)
	{
		((DestroyStruct*)_context)->m_valDestroy(elementVal);	
	}
	
	return 1;
}

#ifndef NDEBUG

static int GetNumOfChains(const HashMap* _map)
{
	register int i;
	int count=0;
	for(i=0;i<_map->m_capacity;++i)
	{
		if(_map->m_listArrMap[i])
		{
			count += 1;
		}
	}
	return count;
}

static int GetMaxChainLength(const HashMap* _map)
{
	register int i;
	int maxSize = 0, tmp;
	for(i=0;i<_map->m_capacity;++i)
	{
		if(_map->m_listArrMap[i])
		{
			tmp = ListSize(_map->m_listArrMap[i]);
			maxSize = tmp > maxSize ? tmp:maxSize;
		}
	}
	return maxSize;
}

static float GetAvarageChainLength(const HashMap* _map)
{
	register int i;
	int sum = 0, count=0;
	for(i=0;i<_map->m_capacity;++i)
	{
		if(_map->m_listArrMap[i])
		{
			count++;
			sum += ListSize(_map->m_listArrMap[i]);
		}
	}
	return ((float)sum)/count;
}

#endif /* NDEBUG */
static size_t GetIndex(size_t _capcity, HashFunction _hashFunc,void* _key)
{
	return _hashFunc(_key)%_capcity;
}

static void HashCopyBucket(List** _dest, List** _src, size_t _oldCap,size_t _newCap, HashFunction _hashFunc, int _ind)
{
	
	ListItr bucketBegin, bucketEnd;
	int* key;
	size_t index;

	bucketBegin = ItrBegin(_src[_ind]);
	bucketEnd = ItrEnd(_src[_ind]);

	while(!ListItrEquals(bucketBegin,bucketEnd))
	{
		key = HashGetKey((Pair*)ItrGet(bucketBegin));
		index = GetIndex(_newCap,_hashFunc,key);
		if(!_dest[index])
		{
			_dest[index] = ListItrCut(bucketBegin,ItrNext(bucketBegin));
			bucketBegin = ItrBegin(_src[_ind]);
		}			
		else
		{
			ListItrSplice(((ListItr)_dest[index]),bucketBegin,ItrNext(bucketBegin));
			bucketBegin = ItrNext(bucketBegin);
		}				
	}
			
}

static void HashCopyAllBuckets(List** _dest, List** _src, size_t _oldCap,size_t _newCap, HashFunction _hashFunc)
{
	register int i;

	for(i=0;i<_oldCap;++i)
	{
		if(_src[i])
		{
			HashCopyBucket(_dest,_src,_oldCap,_newCap,_hashFunc,i);
		}			
	}

	return;
}

static Pair* HashPairCreate(void* _key, void* _value)
{
	Pair* newNode = (Pair*)malloc(sizeof(Pair));
	if(!newNode)
	{
		return NULL;
	}
	newNode->m_item = _value;
	newNode->m_key = _key;
	return newNode;
}

static void HashMapInit(HashMap* _map, List** _listArr,size_t _capacity, HashFunction _hashFunc,  EqualityFunction _keysEqualFunc)
{
	_map->m_listArrMap = _listArr;
	_map->m_capacity = _capacity;
	_map->m_hashFunc = _hashFunc;
	_map->m_cmpKeyFunc = _keysEqualFunc;
	return;
}

static Bool IsPrime(size_t _num)  
{  
	register int i;
    if (_num <= 1)
	{
		return FALSE;
	}    
    if (_num <= 3)
	{
		return TRUE;
	}    

    if (_num%2 == 0 || _num%3 == 0)
	{
		return FALSE;
	}   
    
    for (i=5; i*i<=_num; i=i+6)  
        if (_num%i == 0 || _num%(i+2) == 0)  
		{
			return FALSE;  
		}
    
    return TRUE;  
}  
  
static size_t NextPrime(size_t _num) 
{ 	
    size_t prime = _num; 
    Bool found = FALSE; 

	 if (_num <= 1) 
	{
		return 2; 
	}
    while (!found) 
	{ 
        prime++; 
  
        if (IsPrime(prime)) 
		{
			found = TRUE; 
		}
    }   
    return prime; 
} 

static void* HashGetKey(Pair* _node)
{
	return _node->m_key;
}

