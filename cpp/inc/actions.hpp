#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <map>

#include "transform.hpp"
#include "i_input_text.hpp"
#include "i_output_text.hpp"

namespace actions
{

class UpperCase : public cpp::ITransform
{
public:
	// UpperCase(const UpperCase& a_other) = default
	// ~UpperCase() = default
	// UpperCase& operator=(const UpperCase& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);	
};

class LowerCase : public cpp::ITransform
{
public:
	// LowerCase(const LowerCase& a_other) = default
	// ~LowerCase() = default
	// LowerCase& operator=(const LowerCase& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);
};


class RemoveSpaces : public cpp::ITransform
{
public:
	// NullAction(const NullAction& a_other) = default
	// ~NullAction() = default
	// NullAction& operator=(const NullAction& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);
};

class CapWord : public cpp::ITransform
{
public:
	// CapWord(const CapWord& a_other) = default
	// ~CapWord() = default
	// CapWord& operator=(const CapWord& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);
};


class Censor : public cpp::ITransform
{
public:
	explicit Censor(const std::string& a_words);
	
	// Censor(const Censor& a_other) = default
	// ~Censor() = default
	// Censor& operator=(const Censor& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);

private:
	std::map<std::string,size_t> InitMap(const std::string& a_words);
	void CensorWord(std::map<std::string,size_t>::iterator a_iter, std::string& a_newString);
	void CopyWord(std::string& a_newString, const std::string& a_word);
	void CheckWord(const std::string& a_word, std::string& a_newString);

private:
	std::map<std::string,size_t> a_mapWords;	
};


class Remove : public cpp::ITransform
{
public:
	explicit Remove(const std::string& a_letters);
	
	// Remove(const Remove& a_other) = default
	// ~Remove() = default
	// Remove& operator=(const Remove& a_other) = default

	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out);

private:
	std::map<char,char> InitMap(const std::string& a_letters);
	void CheckLetter(char a_letter, std::string& a_newString);

private:
	std::map<char,char> a_mapLetters;	
};

void SkipSpaces(std::string::iterator& a_begin);

}



#endif // ACTIONS_HPP
