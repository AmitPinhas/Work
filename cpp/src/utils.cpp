#include "utils.hpp"

#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <set>
#include <cassert>

namespace advcpp
{

namespace numbers
{

size_t NextPrimeLookup(size_t a_capacity)
{
	//std::ifstream myFile("~/Downloads/data/10000_primes.txt");
	//std::ifstream myFile("~/data/10000_primes.txt");	
	std::ifstream myFile("../../../../Downloads/data/10000_primes.txt");
	//std::ifstream myFile("./datafile.txt");
	//std::ifstream myFile("datafile.txt");
	assert(myFile.is_open());
	std::string line;
	
	std::set<size_t> primes;
	
	while (!myFile.eof())
	{ 
		getline(myFile, line);
		
	    if(line.size() > 0)
	    {
	      std::stringstream myLine(line);
	      std::string word;
		  while(myLine >> word)
	      {
			std::stringstream prime(word);
			size_t primeNum;
			prime >> primeNum;
			primes.insert(primeNum);
		  }
		}
		else
		{
			break;
		}	    
	}
	
	while(primes.find(a_capacity) == primes.end())
	{
		++a_capacity;
	}
	
	return a_capacity;
	
}

}

}
