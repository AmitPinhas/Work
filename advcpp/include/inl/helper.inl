
namespace advcpp
{

size_t Helper<char>::Len(const char* a_string)
{
	return ::strlen(a_string);
}	

size_t Helper<wchar_t>::Len(const wchar_t* a_string)
{
	return wcslen(a_string);
}

int Helper<char>::Cmp(const char* a_first, const char* a_second )
{
	return strcmp(a_first, a_second);
}

int Helper<wchar_t>::Cmp(const wchar_t* a_first, const wchar_t* a_second )
{
	return wcscmp(a_first, a_second);	
}

int Helper<char>::Upper(int a_letter)
{
	return toupper(a_letter);
}

wint_t Helper<wchar_t>::Upper(wint_t a_letter)
{
	return towupper(a_letter);
}

int Helper<char>::Lower(int a_letter)
{
	return tolower(a_letter);
}

wint_t Helper<wchar_t>::Lower(wint_t a_letter)
{
	return towlower(a_letter);
}

char Helper<char>::End()
{
	return '\0';
}

wchar_t Helper<wchar_t>::End()
{
	return L'\0';
}

} // namespace advcpp
