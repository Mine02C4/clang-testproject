#include "sub.h"
#include <iostream>

test::test( void )
{
	std::cout << "Ctor." << std::endl;
}

void test::init( void )
{
	std::cout << "Call method “init.”" << std::endl;
}
