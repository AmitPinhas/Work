#include "cat.hpp"
#include <cstdlib>/*rand*/
#include <ctime>/*time*/
#include <iostream> /*cout*/
#include <cassert>

static const char* g_catsNames[100] = {"Abby", "Angel" , "Annie", "Baby", "Bailey", "Bandit", "Bear",
"Bella", "Bob", "Boo", "Boots", "Bubba", "Buddy", "Buster", "Cali", "Callie", "Casper", "Charlie","Chester",
"Chloe", "Cleo", "Coco", "Cookie", "Cuddles", "Daisy", "Dusty", "Felix", "Fluffy", "Garfield", "George",
"Ginger", "Gizmo", "Gracie", "Harley", "Jack", "Jasmine", "Jasper", "Kiki", "Kitty", "Leo", "Lilly", "Lily",
"Loki", "Lola", "Lucky", "Lucy", "Luna", "Maggie", "Max", "Mia", "Midnight", "Milo", "Mimi","Miss kitty", "Missy",
"Misty", "Mittens", "Molly", "Muffin", "Nala", "Oliver", "Oreo", "Oscar", "Patches", "Peanut", "Pepper", "Precious",
"Princess", "Pumpkin", "Rascal", "Rocky", "Sadie", "Salem", "Sam", "Samantha", "Sammy", "Sasha", "Sassy", "Scooter",
"Shadow", "Sheba", "Simba", "Simon", "Smokey", "Snickers", "Snowball", "Snuggles", "Socks", "Sophie", "Spooky", "Sugar",
"Tiger", "Tigger", "Tinkerbell", "Toby", "Trouble", "Whiskers", "Willow", "Zoe", "Zoey"};

Cat::Cat(size_t a_age, float a_weight, const char* a_name)
: m_age(a_age)
, m_weight(a_weight)
, m_name(a_name)
{
	assert(a_name != 0);
}

class Random
{
public:
	Random()
	{
		srand(time(NULL));
	}
};

Cat::Cat()
: m_age(rand() % 100)
, m_weight((rand() % 100 + (rand()/10.0)/(rand()/100.0)))
, m_name(g_catsNames[rand() % 100])
{
	static Random rand;
}

std::ostream& Cat::Print(std::ostream& a_os) const
{
	a_os <<"Name:"<<Name()<<'\n'<<"Age:"<<Age()<<'\n'<<"Weight:"<<Weight()<<'\n';
	return a_os;
}

std::ostream& operator<< (std::ostream& a_os, const Cat& a_cat)
{
	return a_cat.Print(a_os);
}

Cat operator+(Cat const& a_catA, int a_num)
{
	Cat cat(a_catA.Age() + a_num, a_catA.Weight() + a_num, a_catA.Name().c_str());
	return cat;
}

Cat operator+(int a_num, Cat const& a_catA)
{
	Cat cat(a_catA.Age() + a_num, a_catA.Weight() + a_num, a_catA.Name().c_str());
	return cat;
}

Cat& Cat::operator++()
{
	this->m_age++;
	this->m_weight++;
	return *this;
}

Cat::operator int() const
{
	return this->Age();
}

bool operator<(Cat const& a_catA, Cat const& a_catB)
{
	return a_catA.Age() < a_catB.Age();
}

bool EqualTo(Cat const& a_catA, Cat const& a_catB)
{
	return a_catA.Age() == a_catB.Age();
}

bool Greater(Cat const& a_catA, Cat const& a_catB)
{
	return a_catA.Age() < a_catB.Age();
}

bool EqualTo(size_t const& a_catA, size_t const& a_catB)
{
	return a_catA == a_catB;
}

bool Greater(size_t const& a_catA, size_t const& a_catB)
{
	return a_catA < a_catB;
}
