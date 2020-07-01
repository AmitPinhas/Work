#ifndef CAT_HPP
#define CAT_HPP

#include <iostream> // cout
#include <cstring> // strcmp

struct Cat
{
	Cat(char * a_name, int a_souls, int a_age);
	
	void Print() const;
	int Age() const;
	int Souls() const;
	const char& Name() const;
	char& Name();
	
	friend bool operator==(const Cat & a_first, const Cat & a_second);

private:
	int m_age;
	int m_souls;
	char *m_name;
};


Cat::Cat(char * a_name, int a_souls, int a_age) 
: m_age(a_age)
, m_souls(a_souls)
, m_name(a_name)
{
}

int Cat::Age() const
{
	return m_age;
}

int Cat::Souls() const
{
	return m_souls;
}

const char& Cat::Name() const
{
	return *m_name;
}

char& Cat::Name()
{
	return *m_name;	
}

void Cat::Print() const
{
	std::cout << Name() << " age: " << Age() << " souls: " << Souls() << '\n';
}

bool operator==(const Cat & a_first, const Cat & a_second)
{
	if(a_first.Age() != a_second.Age())
	{
		return false;
	}
	if(a_first.Souls() != a_second.Souls())
	{
		return false;		
	}
	if(0 != strcmp(a_first.m_name, a_second.m_name))
	{
		return false;
	}
	return true;
}

#endif // CAR_HPP
