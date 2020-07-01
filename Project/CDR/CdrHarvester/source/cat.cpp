#include "cat.hpp"
#include <cstdlib>/*rand*/
#include <ctime>/*time*/
#include <iostream> /*cout*/

static const char* g_catsNames[100] = {"Abby", "Angel" , "Annie", "Baby", "Bailey", "Bandit", "Bear",
"Bella", "Bob", "Boo", "Boots", "Bubba", "Buddy", "Buster", "Cali", "Callie", "Casper", "Charlie","Chester",
"Chloe", "Cleo", "Coco", "Cookie", "Cuddles", "Daisy", "Dusty", "Felix", "Fluffy", "Garfield", "George",
"Ginger", "Gizmo", "Gracie", "Harley", "Jack", "Jasmine", "Jasper", "Kiki", "Kitty", "Leo", "Lilly", "Lily",
"Loki", "Lola", "Lucky", "Lucy", "Luna", "Maggie", "Max", "Mia", "Midnight", "Milo", "Mimi","Miss kitty", "Missy",
"Misty", "Mittens", "Molly", "Muffin", "Nala", "Oliver", "Oreo", "Oscar", "Patches", "Peanut", "Pepper", "Precious",
"Princess", "Pumpkin", "Rascal", "Rocky", "Sadie", "Salem", "Sam", "Samantha", "Sammy", "Sasha", "Sassy", "Scooter",
"Shadow", "Sheba", "Simba", "Simon", "Smokey", "Snickers", "Snowball", "Snuggles", "Socks", "Sophie", "Spooky", "Sugar", 
"Tiger", "Tigger", "Tinkerbell", "Toby", "Trouble", "Whiskers", "Willow", "Zoe", "Zoey"};

Cat::Cat(unsigned int a_age,int a_legs,const char* a_name)
: m_age(a_age)
, m_legs(a_legs)
, m_name(a_name)
{
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
, m_legs(rand() % 10)
, m_name(g_catsNames[rand() % 100])
{
	static Random rand;
}

void Cat::Print() const
{
	std::cout <<"Name:"<<m_name<<'\n'<<"Age:"<<m_age<<'\n'<<"Legs:"<<m_legs<<'\n';
}





