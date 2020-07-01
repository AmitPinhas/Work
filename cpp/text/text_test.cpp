#include "mu_test.h"

#include "actions.hpp"
#include "i_input_text.hpp"
#include "i_output_text.hpp"
#include "writters.hpp"
#include "readers.hpp"
#include "transform.hpp"

#include <cstdio>
#include <cctype>
#include <fstream>
#include <sstream>


UNIT(remove_spaces_string)

	std::string src ("aaa            bbb lll");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	actions::RemoveSpaces removeSpaces;
	std::cout << src << '\n';	
	removeSpaces.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();
	std::cout << tmp << '\n';	
	std::string::iterator begin=tmp.begin();
	std::string::iterator end=tmp.end();

	while (begin !=  end)
	{
		ASSERT_THAT( (*begin == ' ' && *(begin+1) == ' ') == 0);
		++begin;
	}

END_UNIT

UNIT(upper_action_string)

	std::string src ("aaa        bbb lll");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	actions::UpperCase upperAct;
	
	std::cout << src << '\n';
	
	upperAct.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();
	
	std::cout << tmp << '\n';
			
	std::string::iterator begin=tmp.begin();
	std::string::iterator end=tmp.end();

	while (begin !=  end)
	{
		if ( *begin != ' ' )
		{
			ASSERT_THAT( isupper(*begin) != 0);
		}
		++begin;
	}

END_UNIT

UNIT(lower_action_string)

	std::string src ("AAA BBB LLL");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	actions::LowerCase lowerAct;
	
	lowerAct.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();
		
	std::string::iterator begin=tmp.begin();
	std::string::iterator end=tmp.end();

	while (begin !=  end)
	{
		if ( *begin != ' ' )
		{
			ASSERT_THAT( islower(*begin) != 0);
		}
		++begin;
	}

END_UNIT

UNIT(capword_action_string)

	std::string src ("aaa   bbb  lll");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	actions::CapWord capAct;
	
	capAct.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();

	std::stringstream copyTmp(tmp);
	std::string word;
	
	while(copyTmp >> word)
	{
		ASSERT_THAT( isupper(word[0]) != 0 );
	}

END_UNIT

UNIT(censor_string)

	std::string src ("super-type lala blabla  abstract aaaa interface");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	std::string words("super-type abstract interface");
	actions::Censor censor(words);
	
	std::cout << src << '\n';
	
	censor.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();

	std::cout << tmp << '\n';	
	
	ASSERT_PASS();

END_UNIT

UNIT(remove_action_string)

	std::string src ("super-type lala blabla  abstract aaaa interface");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::StringWritter myWrite(returnStr);
	cpp::IOutputText *myOutput = &myWrite;
	std::string words("s u l b");
	actions::Remove remove(words);
	
	std::cout << src << '\n';
	
	remove.Transform(myInput, myOutput);	
	
	std::string tmp = myWrite.String();

	std::cout << tmp << '\n';	
	
	ASSERT_PASS();

END_UNIT

UNIT(remove_spaces_console)

	input::ConsoleReader myConsole;
	cpp::IInputText *myInput = &myConsole;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	actions::RemoveSpaces removeSpaces;
	
	removeSpaces.Transform(myInput, myOutput);	

	ASSERT_PASS();

END_UNIT

UNIT(upper_action_console)

	input::ConsoleReader myConsole;
	cpp::IInputText *myInput = &myConsole;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	actions::UpperCase upperAct;
	
	upperAct.Transform(myInput, myOutput);	

	ASSERT_PASS();

END_UNIT

UNIT(lower_action_console)

	input::ConsoleReader myConsole;
	cpp::IInputText *myInput = &myConsole;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	actions::LowerCase lowerAct;
	
	lowerAct.Transform(myInput, myOutput);	

	ASSERT_PASS();

END_UNIT

UNIT(capword_action_console)

	input::ConsoleReader myConsole;
	cpp::IInputText *myInput = &myConsole;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	actions::CapWord capAct;
	
	capAct.Transform(myInput, myOutput);	

	ASSERT_PASS();

END_UNIT


UNIT(censor_action_console)

	input::ConsoleReader myConsole;
	cpp::IInputText *myInput = &myConsole;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	std::string words("super-type abstract interface");
	actions::Censor censor(words);
	
	censor.Transform(myInput, myOutput);	

	ASSERT_PASS();

END_UNIT

UNIT(remove_spaces_file)

	char nameFile[] = "test.txt";
	input::FileReader myFile(nameFile);
	cpp::IInputText *myInput = &myFile;
	char outNameFile[] = "test3.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	actions::RemoveSpaces removeSpaces;
	
	removeSpaces.Transform(myInput, myOutput);	
		
	ASSERT_PASS();

END_UNIT

UNIT(upper_action_file)

	char nameFile[] = "test.txt";
	input::FileReader myFile(nameFile);
	cpp::IInputText *myInput = &myFile;
	char outNameFile[] = "test.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	actions::UpperCase upperAct;
	
	upperAct.Transform(myInput, myOutput);	
		
	ASSERT_PASS();

END_UNIT

UNIT(lower_action_file)

	char nameFile[] = "test.txt";
	input::FileReader myFile(nameFile);
	cpp::IInputText *myInput = &myFile;
	char outNameFile[] = "test3.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	actions::LowerCase lowerAct;
	
	lowerAct.Transform(myInput, myOutput);	
		
	ASSERT_PASS();

END_UNIT

UNIT(capword_action_file)

	char nameFile[] = "test3.txt";
	input::FileReader myFile(nameFile);
	cpp::IInputText *myInput = &myFile;
	char outNameFile[] = "test.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	actions::CapWord capAct;
	
	capAct.Transform(myInput, myOutput);	
		
	ASSERT_PASS();

END_UNIT

UNIT(censor_action_file)

	char nameFile[] = "test12.txt";
	input::FileReader myFile(nameFile);
	cpp::IInputText *myInput = &myFile;
	char outNameFile[] = "test.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	std::string words("super-type abstract interface");
	actions::Censor censor(words);
	
	censor.Transform(myInput, myOutput);	
		
	ASSERT_PASS();

END_UNIT

UNIT(remove_spaces_string_to_console)

	std::string src ("aaa            bbb lll");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	std::string returnStr;
	output::ConsoleWritter myWrite;
	cpp::IOutputText *myOutput = &myWrite;
	actions::RemoveSpaces removeSpaces;
	
	removeSpaces.Transform(myInput, myOutput);	

	ASSERT_PASS();	

END_UNIT

UNIT(remove_spaces_string_to_file)

	std::string src ("aaa            bbb lll");
	input::StringReader myString(src);
	cpp::IInputText *myInput = &myString;
	char outNameFile[] = "test.txt";
	output::FileWritter myWrite(outNameFile);
	cpp::IOutputText *myOutput = &myWrite;
	actions::RemoveSpaces removeSpaces;
		
	removeSpaces.Transform(myInput, myOutput);	

	ASSERT_PASS();	

END_UNIT

TEST_SUITE(test the text on fire)

	TEST(remove_spaces_string)
	TEST(upper_action_string)
	TEST(lower_action_string)
	TEST(capword_action_string)
	TEST(censor_string)
	TEST(remove_action_string)
	TEST(remove_spaces_console)
	TEST(upper_action_console)
	TEST(lower_action_console)
	TEST(capword_action_console)
	TEST(censor_action_console)
	TEST(remove_spaces_file)
	TEST(upper_action_file)
	TEST(lower_action_file)
	TEST(capword_action_file)
	TEST(censor_action_file)
	TEST(remove_spaces_string_to_console)
	IGNORE_TEST(remove_spaces_string_to_file)

END_SUITE
