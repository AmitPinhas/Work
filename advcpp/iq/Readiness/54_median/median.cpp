#include "mu_test.h"

#include <vector>
#include <algorithm> // swap

using namespace std;

class Median
{
public:
    Median() = default ;
    ~Median() = default ;
    Median(const Median& a_rhs) = default ;
    Median& operator =(const Median& a_rhs) = default ;

    void Add(int a_num);

    int GetMedian() const;  

private:
    void sortElements();

private:
    vector<int> a_elements;

};


inline void Median::Add(int a_num)
{
    a_elements.push_back(a_num);
    sortElements();

}

inline int Median::GetMedian() const
{
    size_t medianIndex = a_elements.size() / 2 ;

    return a_elements[medianIndex];
}

inline void Median::sortElements()
{
    size_t indexNum = a_elements.size() - 1;

    for(int i = indexNum - 1; i >= 0; --i)
    {
        if(a_elements[i] > a_elements[indexNum])
        {
            swap(a_elements[i], a_elements[indexNum]);
            indexNum = i;
        }
        else
        {
            break;
        }
    }
}


UNIT(smoke)

    Median m;

    m.Add(1);
    m.Add(2); 
    m.Add(345); 

    ASSERT_THAT(m.GetMedian() == 2);        

END_UNIT

TEST_SUITE(median)

    TEST(smoke)

END_SUITE    