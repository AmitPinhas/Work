#include "mu_test.h"

#include <unordered_set>
#include <optional>
#include <vector>
#include <iterator> // iterator_traits
#include <algorithm> // copy
#include <limits> // max

using namespace std;

static const size_t FINISH = 0;
static const size_t OK = 1;

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> MinimalRangeContraning(ForwardIter a_beginSource, ForwardIter a_endSource,
                                                                ForwardIter a_beginTarget, ForwardIter a_endTarget);

template <typename ForwardIter>
static size_t CheckParams(ForwardIter a_beginSource, ForwardIter a_endSource,
                          ForwardIter a_beginTarget, ForwardIter a_endTarget);

template <typename ForwardIter>
static void copyToSet(unordered_set<typename iterator_traits<ForwardIter>::value_type>& a_target, ForwardIter a_beginTarget, ForwardIter a_endTarget);                          

template <typename ForwardIter>
static void copyOnlyTarget(ForwardIter a_beginSource, ForwardIter a_endSource, 
                           vector<ForwardIter>& a_itersTarget,
                           unordered_set<typename iterator_traits<ForwardIter>::value_type>& a_target);

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> findResult(vector<ForwardIter> a_itersTarget,
                                                    ForwardIter a_beginTarget, 
                                                    ForwardIter a_endTarget);

UNIT(empty_source)

    string s;
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    if(!r)
    {
        ASSERT_PASS();        
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }

END_UNIT

UNIT(empty_target)

    string s("abc");
    string t;

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    if(!r)
    {
        ASSERT_PASS();        
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }

END_UNIT

UNIT(target_is_larger_than_source)

    string s("abc");
    string t("abcd");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    if(!r)
    {
        ASSERT_PASS();        
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }

END_UNIT


UNIT(target_not_exists_in_source)

    string s("abc");
    string t("qw");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    if(!r)
    {
        ASSERT_PASS();        
    }
    else
    {
        ASSERT_FAIL("r should be nullopt");
    }

END_UNIT

UNIT(source_and_target_equal)

    string s("abc");
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    auto tBegin = t.begin();
    auto tEnd = t.end();
    auto rBegin = r->first;
    auto rEnd = r->second;

    while(rBegin != rEnd)
    {
        if(*tBegin == *rBegin)
        {
            ++tBegin;
        }
        ++rBegin;
    }

    if(tBegin != tEnd)
    {
        ASSERT_FAIL("miss elements from the target");
    }

    ASSERT_THAT(distance(r->first, r->second) == 3);   

END_UNIT

UNIT(first_different)

    string s("jabc");
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    auto tBegin = t.begin();
    auto tEnd = t.end();
    auto rBegin = r->first;
    auto rEnd = r->second;

    while(rBegin != rEnd)
    {
        if(*tBegin == *rBegin)
        {
            ++tBegin;
        }
        ++rBegin;
    }

    if(tBegin != tEnd)
    {
        ASSERT_FAIL("miss elements from the target");
    }

    ASSERT_THAT(distance(r->first, r->second) == 3);   

END_UNIT

UNIT(last_different)

    string s("abcj");
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    auto tBegin = t.begin();
    auto tEnd = t.end();
    auto rBegin = r->first;
    auto rEnd = r->second;

    while(rBegin != rEnd)
    {
        if(*tBegin == *rBegin)
        {
            ++tBegin;
        }
        ++rBegin;
    }

    if(tBegin != tEnd)
    {
        ASSERT_FAIL("miss elements from the target");
    }

    ASSERT_THAT(distance(r->first, r->second) == 3);   

END_UNIT

UNIT(separated)

    string s("abjc");
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    auto tBegin = t.begin();
    auto tEnd = t.end();
    auto rBegin = r->first;
    auto rEnd = r->second;

    while(rBegin != rEnd)
    {
        if(*tBegin == *rBegin)
        {
            ++tBegin;
        }
        ++rBegin;
    }

    if(tBegin != tEnd)
    {
        ASSERT_FAIL("miss elements from the target");
    }

    ASSERT_THAT(distance(r->first, r->second) == 4);   

END_UNIT

UNIT(same_elements)

    string s("cacbaaaaabbbbbbaaacabbbabbaaababaaaaaaccaccac");
    string t("abc");

    auto r = MinimalRangeContraning(s.begin(), s.end(), t.begin(), t.end());

    auto tBegin = t.begin();
    auto tEnd = t.end();
    auto rBegin = r->first;
    auto rEnd = r->second;

    while(rBegin != rEnd)
    {
        if(*tBegin == *rBegin)
        {
            ++tBegin;
        }
        ++rBegin;
    }

    if(tBegin != tEnd)
    {
        ASSERT_FAIL("miss elements from the target");
    }

    ASSERT_THAT(distance(r->first, r->second) == 9);   

END_UNIT

TEST_SUITE(minimal_range_contraning_test)

    TEST(empty_source)
    TEST(empty_target)
    TEST(target_is_larger_than_source)
    TEST(target_not_exists_in_source)
    TEST(source_and_target_equal)
    TEST(first_different)
    TEST(last_different)
    TEST(separated)
    TEST(same_elements)

END_SUITE   

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> MinimalRangeContraning(ForwardIter a_beginSource, ForwardIter a_endSource,
                                                                ForwardIter a_beginTarget, ForwardIter a_endTarget)
{
    using UnorderedSet = unordered_set<typename iterator_traits<ForwardIter>::value_type>;

    if(FINISH == CheckParams(a_beginSource, a_endSource, a_beginTarget, a_endTarget))
    {
        return nullopt;
    }

    UnorderedSet target;

    copyToSet(target, a_beginTarget, a_endTarget);

    vector<ForwardIter> itersTarget;
    
    size_t sourceSize = distance(a_beginSource, a_endSource);

    itersTarget.reserve(sourceSize);

    copyOnlyTarget(a_beginSource, a_endSource, itersTarget, target);

    return findResult(itersTarget, a_beginTarget, a_endTarget);
}    

template <typename ForwardIter>
static size_t CheckParams(ForwardIter a_beginSource, ForwardIter a_endSource,
                          ForwardIter a_beginTarget, ForwardIter a_endTarget)
{
    if(a_beginSource == a_endSource || a_beginTarget == a_endTarget)
    {
        return FINISH;
    }

    if(distance(a_beginSource, a_endSource) < distance(a_beginTarget, a_endTarget))
    {
        return FINISH;
    }

    return OK;
}                    

template <typename ForwardIter>
static void copyToSet(unordered_set<typename iterator_traits<ForwardIter>::value_type>& a_target, ForwardIter a_beginTarget, ForwardIter a_endTarget)
{
    while(a_beginTarget != a_endTarget)
    {
        a_target.insert(*a_beginTarget);
        ++a_beginTarget;
    }
}

template <typename ForwardIter>
static void copyOnlyTarget(ForwardIter a_beginSource, ForwardIter a_endSource, 
                           vector<ForwardIter>& a_itersTarget,
                           unordered_set<typename iterator_traits<ForwardIter>::value_type>& a_target)
{
    while(a_beginSource != a_endSource)
    {
        if(a_target.end() != a_target.find(*a_beginSource))
        {
            a_itersTarget.push_back(a_beginSource);
        }
        ++a_beginSource;
    }
}          

template <typename ForwardIter>
optional<pair<ForwardIter, ForwardIter>> findResult(vector<ForwardIter> a_itersTarget,
                                                    ForwardIter a_beginTarget, 
                                                    ForwardIter a_endTarget)
{
    size_t lengthTarget = distance(a_beginTarget, a_endTarget);

    if(a_itersTarget.size() < lengthTarget)
    {
        return nullopt;
    }

    size_t lastCheck = a_itersTarget.size() - lengthTarget + 1;
    size_t mindistance = numeric_limits<size_t>::max();
    ForwardIter begin;
    ForwardIter end;
    ForwardIter tmpBeginTarget = a_beginTarget;

    for(size_t i = 0; i < lastCheck; ++i)
    {
        if(*a_itersTarget[i] == *tmpBeginTarget)
        {
            ++tmpBeginTarget;

            size_t j = i + 1;

            for(; j < a_itersTarget.size(); ++j)
            {
                if(*a_itersTarget[j] == *tmpBeginTarget)
                {
                    ++tmpBeginTarget;
                    if(tmpBeginTarget == a_endTarget)
                    {
                        break;
                    }
                }
            }
            if(tmpBeginTarget == a_endTarget)
            {
               size_t tmpDistance;
               tmpDistance = distance(a_itersTarget[i], a_itersTarget[j]);
               if(tmpDistance < mindistance)
               {
                   mindistance = tmpDistance;
                   begin = a_itersTarget[i];
                   end = a_itersTarget[j];
                   ++end;
               }
            }
            tmpBeginTarget = a_beginTarget;
        }
    }

    if(mindistance == numeric_limits<size_t>::max())
    {
        return nullopt;
    }
    return make_pair(begin, end);
}                                                    