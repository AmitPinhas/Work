#ifndef CAT_HPP
#define CAT_HPP

#include <string>

class Cat
{
public:
	Cat();
	Cat(unsigned int a_age, int a_legs, const char* a_name);
		
	bool operator==(const Cat& a_cat) const;
	bool operator!=(const Cat& a_cat) const;
	
	bool operator<(const Cat& a_cat) const;
	bool operator>(const Cat& a_cat) const;

	unsigned int Age();
	unsigned int Age() const;
	
	int Legs();
	int Legs() const;
	
	typename std::string& Name();
	const typename std::string& Name() const;
	
	void Print() const;
private:
	unsigned int m_age;
	int m_legs;
	std::string m_name;
};

typedef bool(*CatComp)(const Cat&, const Cat&);
bool CatAreAgeEqual(const Cat& a_catA, const Cat& a_catB);
bool CatAreNumOfLegsEqual(const Cat& a_catA, const Cat& a_catB);
bool CatAreSameNames(const Cat& a_catA, const Cat& a_catB);
bool CatLessAge(const Cat& a_catA, const Cat& a_catB);
bool CatLessName(const Cat& a_catA, const Cat& a_catB);

/////////////////////////////////////////////////////////////////

inline bool Cat::operator==(const Cat& a_cat) const
{
	return CatAreAgeEqual(*this, a_cat) && CatAreNumOfLegsEqual(*this, a_cat) && CatAreSameNames(*this, a_cat);
}

inline bool Cat::operator!=(const Cat& a_cat) const
{
	return !(*this == a_cat);
}

inline bool Cat::operator<(const Cat& a_cat) const
{
	return m_age < a_cat.m_age;
}

inline bool Cat::operator>(const Cat& a_cat) const
{
	return m_age > a_cat.m_age;
}




inline unsigned int Cat::Age()
{
	return m_age;
}

inline unsigned int Cat::Age() const
{
	return m_age;
}

inline int Cat::Legs()
{
	return m_legs;
}

inline int Cat::Legs() const
{
	return m_legs;
}

inline std::string& Cat::Name()
{	
	return m_name;
}

inline const std::string& Cat::Name() const
{
	return m_name;
}

inline bool CatAreAgeEqual(const Cat& a_catA, const Cat& a_catB)
{
	return a_catA.Age() == a_catB.Age();
}

inline bool CatAreNumOfLegsEqual(const Cat& a_catA, const Cat& a_catB)
{
	return a_catA.Legs() == a_catB.Legs();
}

inline bool CatAreSameNames(const Cat& a_catA, const Cat& a_catB)
{
	 
	return a_catA.Name().compare(a_catB.Name()) == 0 ? true : false;
}

inline bool CatLessAge(const Cat& a_catA, const Cat& a_catB)
{
	return a_catA.Age() < a_catB.Age();
}

inline bool CatLessName(const Cat& a_catA, const Cat& a_catB)
{
	return a_catA.Name().compare(a_catB.Name()) < 0 ? true : false;
}



#endif /*CAT_HPP*/
