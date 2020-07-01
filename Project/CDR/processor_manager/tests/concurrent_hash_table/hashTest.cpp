#include "mu_test.h"

#include <iostream>

#include "cat.hpp"
#include "util_functions.hpp"

#include "concurrent_hash_table.hpp"

size_t CatNameHash(std::string const & a_catName)
{
        unsigned long hash = 5381;

        for(size_t i = 0; i < a_catName.size(); ++i)
        {
                hash = ((hash << 5) + hash) + a_catName[i];
        }

        return hash;
}


UNIT(positive_insert_and_find_one_cat)
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(4, CatNameHash);
        ASSERT_EQUAL(table.Capacity(), 5U);
        ASSERT_EQUAL(table.Size(), 0);
        Cat cat(3, 10.5, "lior");
        ASSERT_THAT(table.Insert("lior", cat) != table.End());
        ASSERT_EQUAL(table.Size(), 1);
        advcpp::ConcurrentHashTableItr<std::string, Cat, size_t (*)(std::string const&)> it = table.Find("lior");
        ASSERT_THAT(it != table.End());
        ASSERT_EQUAL(it->first, "lior");
        ASSERT_EQUAL((*it).second, cat);
END_UNIT

UNIT(insert_multiple_cats_check_correct_class_invariant)
        const size_t size = 10;
        const char* arr[size] = {"aty", "bty", "buu", "cio", "chu","aty", "bty", "buu", "cio", "chu"};
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(10, CatNameHash);
        ASSERT_EQUAL(table.Capacity(), 11U);
        ASSERT_EQUAL(table.Size(), 0);
        for(size_t i = 0, j = 0; i < size/2; ++i, ++j)
        {
                ASSERT_THAT(table.Insert(arr[j], Cat(i, i, arr[j])) != table.End());
        }
        ASSERT_EQUAL(table.Size(), 5);
        for(size_t i = 5, j = 5; i < size; ++i, ++j)
        {
                ASSERT_THAT(table.Insert(arr[j], Cat(i, i, arr[j])) == table.End());
        }

        for(size_t i = 0, j = 0; i < size/2; ++i, ++j)
        {
                ASSERT_THAT(table.Find(arr[j]) != table.End());
        }
END_UNIT

UNIT(remove_inserted_cats)
        const size_t size = 5;
        const char* arr[size] = {"ttt", "iii", "ooo", "ggg", "vvv"};
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(10, CatNameHash);
        ASSERT_EQUAL(table.Capacity(), 11U);
        ASSERT_EQUAL(table.Size(), 0);
        for(size_t i = 0; i < size; ++i)
        {
                ASSERT_THAT( table.Insert(arr[i], Cat(i, i, arr[i])) != table.End());
        }
        Cat catCpy;
        for(size_t i = 0; i < size; ++i)
        {
                ASSERT_THAT(table.Remove(arr[i], catCpy));
                ASSERT_EQUAL(catCpy, Cat(i, i, arr[i]));
        }
END_UNIT

UNIT(remove_non_existant_cat)
        const size_t size = 5;
        const char* arr[size] = {"ttt", "iii", "ooo", "ggg", "vvv"};
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(10, CatNameHash);
        ASSERT_EQUAL(table.Capacity(), 11U);
        ASSERT_EQUAL(table.Size(), 0);
        for(size_t i = 0; i < size; ++i)
        {
                ASSERT_THAT(table.Insert(arr[i],Cat(i, i, arr[i])) != table.End());
        }

        Cat catCpy;
        ASSERT_THAT(!table.Remove("hhh", catCpy));
END_UNIT

UNIT(clear_hash_table)
        const size_t size = 20;
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(20, CatNameHash);
        for(size_t i = 0; i < size; ++i)
        {
               Cat cat;
               table.Insert(cat.Name(), cat);
        }

        ASSERT_THAT(table.Size() != 0);
        table.Clear();
        ASSERT_EQUAL(table.Size(), 0);
END_UNIT

UNIT(operator_subscript_test)
    advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(4, CatNameHash);
    Cat catT(3, 10.5, "Tom");
    Cat catJ(10, 13.3, "Jerry");
    table.Insert(catT.Name(), catT);
    table.Insert(catJ.Name(), catJ);
    ASSERT_EQUAL(table[catT.Name()], catT);
    ASSERT_EQUAL(table[catJ.Name()], catJ);
END_UNIT

UNIT(print_next_thousand_primes)
    size_t num = 2;
    for(size_t i = 0; i < 1000; ++i)
    {
            std::cout<< num<<", ";
            num = numbers::FindNextPrime(num);
    }
    ASSERT_PASS();
END_UNIT

UNIT(resize_hash_table)
    const size_t size = 6;
    const char* arr[size] = {"ttt", "iii", "ooo", "ggg", "vvv", "ppp"};
    advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(6, CatNameHash);
    for(size_t i = 0; i < size; ++i)
    {
            ASSERT_THAT(table.Insert(arr[i], Cat(i, i, arr[i])) != table.End());
    }

    table.Resize(10U);
    for(size_t i = 0; i < size; ++i)
    {
            ASSERT_THAT(table.Find(arr[i]) != table.End());
    }
END_UNIT

UNIT(my_hash_itr_test)
        const size_t size = 25;
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(size, CatNameHash);
        std::vector<Cat> vec;
        for(size_t i = 0; i < size; ++i)
        {
              vec.push_back(Cat(i, i, "Cat"));
        }

        advcpp::ConcurrentHashTableItr<std::string, Cat, size_t (*)(std::string const&)> begin = table.Begin();
        advcpp::ConcurrentHashTableItr<std::string, Cat, size_t (*)(std::string const&)> end = table.Begin();
        size_t i = 0;
        while(begin != end)
        {
                ASSERT_EQUAL(begin->second, vec[i]);
                ++begin;
                ++i;
        }
        ASSERT_PASS();
END_UNIT

UNIT(default_ctor_test)
        const size_t size = 20;
        typename advcpp::ConcurrentHashTable<int, size_t> table;
        int key = 0;
        for(size_t i = 0; i < size; ++i, ++key)
        {
              table.Insert(key, i);
        }
        ASSERT_EQUAL(table.Size(), 20);
        key = 0;
        for(size_t i = 0; i < size; ++i, ++key)
        {
              ASSERT_THAT(table.Find(key) != table.End());
        }
END_UNIT


struct UpdateCat
{
        UpdateCat(size_t a_val)
        : val(a_val)
        {
        }

        void operator()(Cat& a_update, Cat const& a_toAdd)
        {
                a_update.Age() += val + a_toAdd.Age();
                a_update.Weight() += val + a_toAdd.Weight();

        }

        size_t val;
};

UNIT(my_hash_upsert_test)
        const size_t size = 15;
        advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)> table(size, CatNameHash);
        std::vector<Cat> vec;
        char const *names[] = {"Abby", "Angel" , "Annie", "Baby", "Bailey", "Bandit",
        "Bear","Bella", "Bob", "Boo", "Boots", "Bubba", "Buddy", "Buster", "Cali"};
        for(size_t i = 0; i < size; ++i)
        {
              vec.push_back(Cat(i, i, names[i]));
        }
        for(size_t i = 0; i < size; ++i)
        {
              table.Insert(vec[i].Name(), vec[i]);
        }
        ASSERT_EQUAL(table.Size(), size);
        for(size_t i = 0; i < size; ++i)
        {
              ASSERT_THAT(table.Find(names[i]) != table.End());
        }
        for(size_t i = 0; i < size; ++i)
        {
                advcpp::ConcurrentHashTable<std::string, Cat, size_t (*)(std::string const&)>::iterator it =
                table.Upsert(vec[i].Name(), vec[i], UpdateCat(10));
                vec[i].Age() += 10 + vec[i].Age();
                vec[i].Weight() += 10 + vec[i].Weight();
                ASSERT_EQUAL(it->second, vec[i]);
        }
END_UNIT

UNIT(copy_whole_hash_table)
        const size_t capacity = 50;
        advcpp::ConcurrentHashTable<const std::string, Cat, size_t (*)(std::string const&)> table(capacity, CatNameHash);
        char const *names[] = {"Abby", "Angel" , "Annie", "Baby", "Bailey", "Bandit",
        "Bear","Bella", "Bob", "Boo", "Boots", "Bubba", "Buddy", "Buster", "Cali"};
        const size_t size = 15;
        std::vector<Cat> vec;
        for(size_t i = 0; i < size; ++i)
        {
              vec.push_back(Cat(i, i, names[i]));
        }
        for(size_t i = 0; i < size; ++i)
        {
              table.Insert(vec[i].Name(), vec[i]);
        }
        ASSERT_EQUAL(table.Size(), size);
        std::vector<Cat> toCopy;
        table.CopyAllTable(toCopy);
        ASSERT_EQUAL(toCopy.size(), size);
END_UNIT

TEST_SUITE(the hash table on fire)
    TEST(positive_insert_and_find_one_cat)
    TEST(insert_multiple_cats_check_correct_class_invariant)
    TEST(remove_inserted_cats)
    TEST(remove_non_existant_cat)
    TEST(clear_hash_table)
    TEST(operator_subscript_test)
    IGNORE_TEST(print_next_thousand_primes)
    TEST(resize_hash_table)
    TEST(my_hash_itr_test)
    TEST(my_hash_upsert_test)
    TEST(default_ctor_test)
    TEST(copy_whole_hash_table)
END_SUITE

