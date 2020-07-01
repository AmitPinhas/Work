#include "actions.hpp"

#include <cstdio>
#include <cctype>
#include <sstream>

namespace actions
{

void UpperCase::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::string newString;		
	std::string::iterator begin=readString.begin();
	std::string::iterator end=readString.end();

	while(begin != end)
	{
		SkipSpaces(begin);
		newString.push_back(toupper(*begin));
		++begin;
	}	
	a_out -> Write(newString);
}

void LowerCase::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::string newString;		
	std::string::iterator begin=readString.begin();
	std::string::iterator end=readString.end();

	while(begin != end)
	{
		SkipSpaces(begin);	
		newString.push_back(tolower(*begin));
		++begin;
	}	
	a_out -> Write(newString);
}



void RemoveSpaces::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::string newString;		
	std::string::iterator begin=readString.begin();
	std::string::iterator end=readString.end();

	while(begin != end)
	{
		SkipSpaces(begin);	
		newString.push_back(*begin);
		++begin;
	}	
	a_out -> Write(newString);
}

void CapWord::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::stringstream copyString(readString);
	std::string line;
	std::string newString;
	
	while(getline(copyString, line))
	{
		std::stringstream copyLine(line);	
		std::string word;	
		while(copyLine >> word)
		{
			word[0] = toupper(word[0]);
			newString.append(word);
			newString.append(" ");			
		}
		newString.append("\n");
	}	
	a_out -> Write(newString);	
}

Censor::Censor(const std::string& a_words)
: a_mapWords(InitMap(a_words))
{
}

std::map<std::string,size_t> Censor::InitMap(const std::string& a_words)
{
	std::map<std::string,size_t> returnMap;
	std::stringstream copyWords(a_words);
	std::string word;	
	
	while(copyWords >> word)
	{
		returnMap[word] = word.size();
	}
	
	return returnMap;	
}


void Censor::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::stringstream copyString(readString);
	std::string line;
	std::string newString;
	
	while(getline(copyString, line))
	{
		std::stringstream copyLine(line);	
		std::string word;	
		while(copyLine >> word)
		{
			CheckWord(word, newString);	
		}
		newString.append("\n");
	}	
	a_out -> Write(newString);	
}

void Censor::CensorWord(std::map<std::string,size_t>::iterator a_iter, std::string& a_newString)
{
	size_t size = a_iter->second;
	while(size-- > 0)
	{
		a_newString.append("*");	
	}
	a_newString.append(" ");	
}

void Censor::CopyWord(std::string& a_newString, const std::string& a_word)
{
	a_newString.append(a_word);
	a_newString.append(" ");		
}

void Censor::CheckWord(const std::string& a_word, std::string& a_newString)
{
	std::map<std::string,size_t>::iterator iter;
	iter = a_mapWords.find(a_word);
	if(iter == a_mapWords.end())
	{
		CopyWord(a_newString, a_word);				
	}
	else
	{
		CensorWord(iter, a_newString);
	}		
}

Remove::Remove(const std::string& a_letters)
: a_mapLetters(InitMap(a_letters))
{
}

std::map<char,char> Remove::InitMap(const std::string& a_letters)
{
	std::map<char,char> returnMap;
	std::string copyLetters(a_letters) ;
	std::string::iterator begin=copyLetters.begin();
	std::string::iterator end=copyLetters.end();	
	
	while(begin != end)
	{
		if(*begin != ' ')
		{	
			returnMap[*begin] = *begin;
		}
		++begin;
	}	
	return returnMap;	
}


void Remove::Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out)
{
	std::string readString = a_in -> Read();
	std::string newString;	
	std::string::iterator begin=readString.begin();
	std::string::iterator end=readString.end();

	while(begin != end)
	{
		if(*begin != ' ')
		{
			CheckLetter(*begin, newString);
		}
		if(*begin == ' ' && *(begin+1) != ' ')
		{
			newString.append(" ");				
		}
		++begin;
	}	
	a_out -> Write(newString);
}

void Remove::CheckLetter(char a_letter, std::string& a_newString)
{
	std::map<char,char>::iterator iter;
	iter = a_mapLetters.find(a_letter);
	if(iter == a_mapLetters.end())
	{			
		a_newString.push_back(a_letter);
	}
	else
	{
		a_newString.append(" ");				
	}
}


void SkipSpaces(std::string::iterator& a_begin)
{
	while(*a_begin == ' ' && *(a_begin + 1) == ' ')
	{
		++a_begin;
	} 	
}

}
