

class Counters
{
public:
    explicit Counters(size_t a_size);
    
    size_t Get(size_t a_index);
    
    void Set(size_t a_value, size_t a_index);
    
    void SetAll(size_t a_value);

private:
    vector<pair<size_t,size_t>> m_counters;
    size_t m_currTime;
    pair<size_t, size_t> m_valueAll;
    
};

inline Counters::Counters(size_t a_size)
: m_counters(a_size, make_pair(0, 0))
, m_currTime(0)
, m_valueAll(0, 0)
{
}

inline size_t Counters::Get(size_t a_index)
{
    if(m_counters[a_index].second < m_valueAll.second)
    {
        return m_valueAll.first;
    }
    
    return m_counters[a_index].first;
}

inline void Counters::Set(size_t a_value, size_t a_index)
{
   m_counters[a_index].first = a_value;
   m_counters[a_index].second = ++m_currTime;
}

inline void Counters::SetAll(size_t a_value)
{
   m_valueAll.first = a_value;
   m_valueAll.second = ++m_currTime;    
}

vector<int> solution(int N, vector<int> &A) 
{
    Counters counters(N);
    size_t maxCount = 0;
    
    for(auto index : A)
    {
        if(index == N + 1)
        {
          counters.SetAll(maxCount);  
        }
        else
        {
            size_t tmpValueCounter = counters.Get(index - 1);
            ++tmpValueCounter;
            if(tmpValueCounter > maxCount)
            {
                maxCount = tmpValueCounter;
            }
            counters.Set(tmpValueCounter, index - 1);
        }
    }
    
    vector<int> resultCounters;
    resultCounters.reserve(N);
    
    for(int i = 0; i < N; ++i)
    {
        resultCounters.push_back(counters.Get(i));
    }
    
    return resultCounters;
}



vector<int> solution2(int N, vector<int> &A) 
{
    vector<int> counters(N, 0);
    int currMaxCounter = 0;
    int setAll = 0;
    
    for(auto num : A)
    {
        if(num == N + 1)
        {
            setAll = currMaxCounter;
        }
        else
        {
            int newValue = max(counters[num - 1], setAll);
            if(++newValue > currMaxCounter)
            {
                currMaxCounter = newValue;
            }
            counters[num - 1] = newValue;
        }
    }
    
    for(auto &num : counters)
    {
        num = max(num, setAll);
    }
    
    return counters;
}

