#ifndef HELPER_H
#define HELPER_H

namespace advcpp
{

template<typename T>
struct Helper;

template<>
struct Helper<char>{
	static int Upper(int a_letter);
	static int Lower(int a_letter);
	static size_t Len(const char* a_string);
	static int Cmp(const char* a_first, const char* a_second );
	static char End();
};

template<>
struct Helper<wchar_t>{
	static wint_t Upper(wint_t a_letter);
	static wint_t Lower(wint_t a_letter);	
	static size_t Len(const wchar_t* a_string);
	static int Cmp(const wchar_t* a_first, const wchar_t* a_second );
	static wchar_t End();
};

} // namespace advcpp

#include "inl/helper.inl"

#endif // HELPER_H
