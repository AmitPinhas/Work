#include "BookFactory.hpp"
#include "BookCreator.hpp"

namespace cpp
{

BookFactory::BookFactory(IParser& a_parser, ITextReader& a_reader, BookCreator& a_creator)
: m_parser(a_parser)
, m_reader(a_reader)
, m_creator(a_creator)
{
}

Book* BookFactory::GetNextBook()
{
	std::vector<std::string> vecCategory;
	std::string line = m_reader.Read();
	if(line.size() > 0)
	{
		m_parser.Delim(line, vecCategory);	
		return m_creator.Create(vecCategory);
	}
	return 0;
}

bool BookFactory::HasMore()
{
	return m_reader.HasMore();
}

}

