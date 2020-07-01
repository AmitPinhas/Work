#ifndef CAT_HPP
#define CAT_HPP

#include <string> /**/
#include <cstddef>/*size_t*/

class Cat
{
public:
	
	Cat();
	Cat(size_t a_age, float a_weight, const char* a_name);
	//~Cat() = default;
	//Cat(const Cat& a_cat) = default;
	//Cat& operator=(const Cat& a_cat) = default;	
	bool operator==(const Cat& a_cat) const;
	bool operator!=(const Cat& a_cat) const;
	operator int() const;
	Cat& operator++();
	size_t& Age();
	size_t Age() const;
	
	float& Weight();
	float Weight() const;
	
	typename std::string& Name();
	const typename std::string& Name() const;
	
	std::ostream& Print(std::ostream& a_os) const;
private:
	size_t m_age;
	float m_weight;
	std::string m_name;
};



typedef bool(*CatComp)(const Cat&, const Cat&);
bool CatAreAgeEqual(const Cat& a_catA, const Cat& a_catB);
bool CatAreNumOfLegsEqual(const Cat& a_catA, const Cat& a_catB);
bool CatAreSameNames(const Cat& a_catA, const Cat& a_catB);
bool CatLessAge(const Cat& a_catA, const Cat& a_catB);
bool CatLessName(const Cat& a_catA, const Cat& a_catB);


Cat operator+(Cat const& a_catA, int a_num);
Cat operator+(int a_num, Cat const& a_catA);
bool operator<(Cat const& a_catA, Cat const& a_catB);
bool EqualTo(Cat const& a_catA, Cat const& a_catB);
bool Greater(Cat const& a_catA, Cat const& a_catB);
bool EqualTo(size_t const& a_catA, size_t const& a_catB);
bool Greater(size_t const& a_catA, size_t const& a_catB);

std::ostream& operator<< (std::ostream& os, const Cat& a_cat);

/////////////////////////////////////////////////////////////////

inline bool Cat::operator==(const Cat& a_cat) const
{
	return CatAreAgeEqual(*this, a_cat) && CatAreNumOfLegsEqual(*this, a_cat) && CatAreSameNames(*this, a_cat);
}

inline bool Cat::operator!=(const Cat& a_cat) const
{
	return !(*this == a_cat);
}

inline size_t& Cat::Age()
{
	return m_age;
}

inline size_t Cat::Age() const
{
	return m_age;
}

inline float& Cat::Weight()
{
	return m_weight;
}

inline float Cat::Weight() const
{
	return m_weight;
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
	return a_catA.Weight() == a_catB.Weight();
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
