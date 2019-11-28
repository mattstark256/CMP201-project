#include "UserInterface.h"

#include <iostream>
#include <string>
#include "Vector2i.h"

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::beginSession()
{
	std::cout << "Session begun\n";

	while (true)
	{
		std::cout << "Finding path\n";

		//Vector2i v1(1, 2);
		//Vector2i v2(3, 4);
		//Vector2i v3;

		//std::cout << v1.x << " " << v1.y << std::endl;
		//std::cout << v2.x << " " << v2.y << std::endl;
		//std::cout << v3.x << " " << v3.y << std::endl;

		//v3 = v1 + v2;

		//std::cout << v1.x << " " << v1.y << std::endl;
		//std::cout << v2.x << " " << v2.y << std::endl;
		//std::cout << v3.x << " " << v3.y << std::endl;

		//v3 -= v2;

		//std::cout << v1.x << " " << v1.y << std::endl;
		//std::cout << v2.x << " " << v2.y << std::endl;
		//std::cout << v3.x << " " << v3.y << std::endl;

		//if(v3 == v1){ std::cout << "They're equal\n"; }

		std::cout << "Run again?\n";
		std::string s;
		std::cin >> s;
	}
}
