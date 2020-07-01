#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <list>

#include "commons.hpp"
#include "concurrent_hash_table_const_itr.hpp"
#include "concurrent_hash_table_itr.hpp"
#include "default_hasher.hpp"
#include "mutex.hpp"


namespace advcpp
{

template< typename Key, typename Value>
struct Pair;

template< typename Key, typename Value>
class Bucket;

//Key:: must have operator== and copy constructor and default ctor
//Value::default ctor
//Hasher callable
template< typename Key, typename Value, typename Hasher = DefaultHasher<Key> >
class ConcurrentHashTable: private std::vector<Bucket< Key, Value> >, private UnCopyable
{
public:
	typedef ConcurrentHashTableItr<Key, Value, Hasher> iterator;//IS NOT THREAD SAFE
	typedef ConcurrentHashTableItr<Key, Value, Hasher> const_iterator;//IS NOT THREAD SAFE

	explicit ConcurrentHashTable(size_t a_capacity = s_defaultCapacity, Hasher a_func = DefaultHasher<Key>());
	~ConcurrentHashTable() NOEXCEPT;
	//ConcurrentHashTable(const ConcurrentHashTable& a_table) = delete;
	//ConcurrentHashTable& operator(const ConcurrentHashTable& a_table) = delete;

	ConcurrentHashTableItr<Key, Value, Hasher> Insert(const Key& a_key, const Value& a_val);
	ConcurrentHashTableConstItr<Key, Value, Hasher> Find(const Key& a_key) const;
	ConcurrentHashTableItr<Key, Value, Hasher> Find(const Key& a_key);


	bool Find(const Key& a_key, Value& a_val) const;
	template<typename Update>
	ConcurrentHashTableItr<Key, Value, Hasher> Upsert(const Key& a_key, const Value& a_val, Update a_update);
	void CopyAllTable(std::vector<Value>& a_vectorToFill) const;

	void Clear();
	bool Remove(const Key& a_key, Value& a_val);

	Value& operator[](const Key& a_key);


	size_t Size() const;
	size_t Capacity() const;
	float LoadFactor() const;

	void Resize(size_t a_newCapacity);
	Bucket<Key, Value> const& IndxBucket(size_t a_indx) const;
	Bucket<Key, Value>& IndxBucket(size_t a_indx);

	//iterators are not thread, safe used for testing in one thread
	ConcurrentHashTableItr<Key, Value, Hasher> Begin();
	ConcurrentHashTableItr<Key, Value, Hasher> End();
	ConcurrentHashTableConstItr<Key, Value, Hasher> Begin() const;
	ConcurrentHashTableConstItr<Key, Value, Hasher> End() const;

private:

	Bucket< Key, Value>& getBucket(const Key& a_key);
	Bucket<Key, Value> const& GetBucket(const Key& a_key) const;

	void swap(ConcurrentHashTable& a_origin);
    void Insert(const Key& a_key, const Value& a_val, size_t a_hashVal);
    void copyConcurrentHashTable(ConcurrentHashTable& a_target,const ConcurrentHashTable& a_origin);

	static void fillMutexVector(std::vector<Mutex*>& a_vecMutex);

	size_t calculateIndex(const Key& a_key) const;
	size_t calculateIndexMutex(const Key& a_key) const;
	const Hasher& hash() const;
private:
	const static size_t s_defaultCapacity = 499;
	size_t m_capacity;
	size_t m_size;
	Hasher m_hashFunc;
	mutable std::vector<Mutex*> m_vecMutex;
};

template< typename Key, typename Value, typename Hasher>
void swap(ConcurrentHashTable<Key, Value, Hasher>& a_tableA, ConcurrentHashTable<Key, Value, Hasher>& a_tableB);

template< typename Key, typename Value>
class Bucket
{
public:
	typedef typename std::list<Pair<const Key, Value> >::iterator iterator;
	typedef typename std::list<Pair<const Key, Value> >::const_iterator const_iterator;
	//friend class ConcurrentHashTableItr<Key, Value, Hasher>;
    //Bucket() = default;
    //Bucket(const Bucket& a_table) = default;
	//~Bucket() = default;
	//Bucket& operator=(const Bucket& a_table);

	iterator Insert(const Key& a_key,const Value& a_val, size_t a_hVal);
	const_iterator Find(const Key& a_key, size_t a_hVal) const;
	iterator Find(const Key& a_key, size_t a_hVal);
	bool Remove(const Key& a_key, Value& a_val, size_t a_hVal);
	void Clear();

	iterator Begin();
	iterator End();

	const_iterator Begin() const;
	const_iterator End() const;
private:
    std::list<Pair<const Key, Value> >& Container();
    const std::list<Pair<const Key, Value> >& Container() const;
private:
    std::list<Pair<const Key, Value> > m_bucket;
};

template< typename Key, typename Value>
struct Pair
{
    Pair(const Key& a_key, const Value& a_value, size_t a_hashVal);
    std::pair<const Key, Value> m_pair;
    size_t HashValue() const;
    size_t m_hashValue;
};

}//namespace advcpp

#include "concurrent_hash_table.inl"

#endif //HASH_TABLE_HPP