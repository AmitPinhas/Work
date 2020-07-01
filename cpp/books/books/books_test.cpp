#include "mu_test.h"

#include "FileReader.hpp"
#include "Book.hpp"
#include "Library.hpp"


UNIT(find_by_isbn)
	cpp::FileReader fileReader("../../../../Downloads/Sample_from_the_dara_file.txt");
	cpp::Library library;
	
	library.Loader(fileReader);
	
	library.FindByIsbn("804106304");
	
	ASSERT_PASS();
	
END_UNIT

TEST_SUITE(test the books on fire)

	TEST(find_by_isbn)

END_SUITE
