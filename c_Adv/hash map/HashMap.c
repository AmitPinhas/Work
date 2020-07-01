
#include "HashMap.h"
#include "../../DS/vector/vector.h"
#include "../../DS/double list/list_functions/DLList.h"
#include "../../DS/double list/list_functions/list_itr.h"
#include "../../DS/double list/list_functions/list_functions.h"

/* ---------------------------------------------------------- defines ---------------------------------------------------------------------------- */

#define NO_BLOCK_SIZE 0
#define TRUE 1
#define FALSE 0

/* ----------------------------------------------------------- macro ---------------------------------------------------------------------------- */

#define MODULO(index , capacity) ( index%capacity )

/* ---------------------------------------------------------- structs ---------------------------------------------------------------------------- */

struct HashMap{
	Vector *m_vector;
	HashFunction m_hashFunc;
	EqualityFunction m_equalityFunc;
};

typedef struct{
	void *m_key;
	void *m_value;
}Pair;


typedef struct{
	void *m_key;
	EqualityFunction m_equalityFunc;
}KeyComp;


typedef struct{
	void (*_keyDestroy)(void* _key) m_keyDes ;
	void (*_valDestroy)(void* _value) m_valDes ;	
}funcPair;

/* ------------------------------------------------------- local function ------------------------------------------------------------------------ */

 /* capacity be rounded to nearest larger prime number */
static size_t PrimeNumber(size_t _capacity);

 /* check insert param */
static MapResult CheckInsertParam(HashMap* _map, const void* _key, const void* _value);

 /* get index to map */
static size_t GetIndexMap(HashMap* _map, const void* _key);

 /* create bukets */
static void CreateBukets( Vector *_vector );

 /* check if list empty */
static int CheckIfListEmpty(List *_list);

/* insert pair to list */
static MapResult InsertNodeToList( List *_list , const void* _key , const void* _value );

static Pair* CreatePair(const void* _key , const void* _value );

static MapResult CheckIfKeyExist( List *_list , const void* _key , EqualityFunction _keysEqualFunc);

static KeyComp CreateKeyComp( const void* _key  , EqualityFunction _keysEqualFunc );

/* =============================================================================================================================================== */
/* ============================================================= API ============================================================================= */
/* =============================================================================================================================================== */

/* ------------------------------------------------------  Hash Map Create ----------------------------------------------------------------------- */

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap *hashMap;
	
	if ( (0 == _capacity) || (NULL == _hashFunc) || (NULL == _keysEqualFunc) )
	{
		return NULL ;
	}
	
	hashMap = (HashMap*)malloc(sizeof(HashMap));
	if ( NULL == hashMap )
	{
		return NULL ;
	}
	
	_capacity = PrimeNumber( _capacity );
	
	hashMap -> m_vector = VectorCreate ( _capacity, NO_BLOCK_SIZE );
	if ( NULL == hashMap -> m_vector )
	{
		free(hashMap);
		retrun NULL;
	}
	
	CreateBukets( hashMap -> m_vector ) ;
	
	hashMap -> m_hashFunc = _hashFunc ;
	hashMap -> m_equalityFunc = _keysEqualFunc ;
	return hashMap;
}


/* --------------------------------------------------------- Hash Map Insert ---------------------------------------------------------------------- */

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	MapResult paramResult , resultKey;
	size_t indexMap;
	int resultListNull;
	List *list;
	
	
	if ( (paramResult = CheckInsertParam(_map , _key , _value)) != MAP_SUCCESS )
	{
		return paramResult;
	}
	
	indexMap = GetIndexMap( _map , _key ) ;
	
	VectorGet(_map->m_vector, indexMap , (void**)&list) ; 
	
	if ( (resultListNull = CheckIfListEmpty( list ) == TRUE )
	{
		return InsertNodeToList( list , _key , _value );
	}
	else
	{
		if ( (resultKey = CheckIfKeyExist( list , _key , _map->m_equalityFunc ) ) == MAP_KEY_DUPLICATE_ERROR )
		{
			return MAP_KEY_DUPLICATE_ERROR ;
		}
		else
		{
			return InsertNodeToList( list , _key , _value );
		}
	}
}



/* ----------------------------------------------------- Hash Map Destroy ----------------------------------------------------------------------- */
void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
{
	if ( NULL == _map || NULL == *_map )
	{
		return;
	}
}


/* =============================================================================================================================================== */
/* ========================================================= local function ====================================================================== */
/* =============================================================================================================================================== */

/* --------------------------------------------------------- Prime Number ------------------------------------------------------------------------ */
static size_t PrimeNumber(size_t _capacity)
{
	int flag = 0 , i ;
	while (!flag)
	{
		flag = 1;
		for( i = 2 ; i < _capacity ; ++i )
		{
			if ( _capacity % i == 0 )
			{
				flag = 0 ;
				break ;
			}
		}
		if (!flag)
		{
			_capacity++;
		}
	}
	
	return _capacity ;			
}

/* ------------------------------------------------------ Check Insert Param ------------------------------------------------------------------- */
static MapResult CheckInsertParam(HashMap* _map, const void* _key, const void* _value)
{
	if ( NULL == _map )
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if ( NULL == _key )
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	return MAP_SUCCESS;
}


/* ------------------------------------------------------ Get Index Map ------------------------------------------------------------------- */
static size_t GetIndexMap(HashMap* _map, const void* _key)
{
	size_t indexMap;
	
	indexMap = _map -> m_hashFunc(_key);
	
	indexMap = MODULO( indexMap , VectorCapacity( _map -> m_vector));
	
	return indexMap;
}

/* ----------------------------------------------------- Create Bukets ------------------------------------------------------------------- */
static void CreateBukets( Vector *_vector )
{
	int i ;
	size_t capacity = VectorCapacity(_vector);
	
	for ( i = 0 ; i < capacity ; ++i )
	{
		VectorAppend( _vector , ListCreate );  
	}
	
	return ;
}



/* ----------------------------------------------------- Check If List Empty ------------------------------------------------------------------- */
static int CheckIfListEmpty(List *_list)
{
	if ( ListSize( _list ) == 0 )
	{
		return TRUE ;
	}
	
	return FALSE ;
}


/* -------------------------------------------------- Insert Node To List ---------------------------------------------------------------------- */
static MapResult InsertNodeToList( List *_list , const void* _key , const void* _value )
{
	Pair *pair;
	
	pair = CreatePair( _key , _value );
	
	 ListPushHead( _list , pair );
	 
	 return MAP_SUCCESS ;
}


/* ----------------------------------------------------- Create Pair --------------------------------------------------------------------------- */
static Pair* CreatePair(const void* _key , const void* _value )
{
	Pair *pair;
	
	pair = (Pair*) malloc(sizeof(Pair));
	
	pair -> m_key = _key;
	pair -> m_value = _value;
	
	return pair ;
}

/* ----------------------------------------------------- Check If Key Exist ---------------------------------------------------------------------- */
static MapResult CheckIfKeyExist( List *_list , const void* _key , EqualityFunction _keysEqualFunc)
{
	KeyComp *keyComp ;
	ListItr begin , end , first ;
	
	keyComp = CreateKeyComp( _key , _keysEqualFunc );
	
	begin = ListItrBegin( _list );
	end = ListItrEnd( _list );
	
	first =  ListItrFindFirst( begin , end ,  PredKeys , keyComp );
	
	if ( !ListItr_Equals( first , end) )
	{
		return MAP_KEY_DUPLICATE_ERROR ;
	}
	
	return MAP_SUCCESS ;
}



/* ---------------------------------------------------- Create Key Comp -------------------------------------------------------------------------- */
static KeyComp CreateKeyComp( const void* _key  , EqualityFunction _keysEqualFunc )
{
	KeyComp *keyComp ;
	
	keyComp = (KeyComp*) malloc(sizeof(KeyComp));
	
	keyComp -> m_key = _key ;
	
	keyComp -> m_equalityFunc = _keysEqualFunc ;
	
	return keyComp ;
}



static int PredKeys(void* _pair , void* _keyComp ) 
{
	void* key = ((Pair*)_pair)->m_key ;
	void* key2 = ((KeyComp*)_keyComp)->m_key ;
	
	if (((KeyComp*)_keyComp)->m_equalityFunc(key , key2))
	{
		return 0 ;
	}
	
	return 1 ;
}

