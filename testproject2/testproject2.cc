#include <iostream>
#include "sub.h"

int main( void )
{
	std::cout << "Program start." << std::endl;
	test t;
	t.init();
	std::cout << "Program will end." << std::endl;
	return 0;
}
