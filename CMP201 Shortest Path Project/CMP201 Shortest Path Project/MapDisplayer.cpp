#include "MapDisplayer.h"

#include <iostream>
#include <windows.h>   // WinApi header

#define DEFAULT_COLOUR FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BORDER_COLOUR BACKGROUND_RED | BACKGROUND_BLUE


MapDisplayer::MapDisplayer()
{
}


MapDisplayer::~MapDisplayer()
{
}


void MapDisplayer::displayMap(const Map& map, const Path& path)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Top border
	SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
	for (int x = 0; x < map.getSize().x + 2; x++)
	{
		std::cout << "  ";
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
	std::cout << std::endl;

	for (int y = 0; y < map.getSize().y; y++)
	{
		// Left border
		SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
		std::cout << "  ";

		// Map
		for (int x = 0; x < map.getSize().x; x++)
		{
			Vector2i coord(x, y);

			if (coord == path.getStart())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << " S";
			}
			else if (coord == path.getEnd())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << " E";
			}
			else if (path.contains(coord))
			{
				//SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << " o";
			}
			else
			{
				switch (map.getValue(coord))
				{
				case 0:
					SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
					std::cout << "  ";
					break;
				case 1:
					//SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
					std::cout << "  ";
					break;
				default:
					break;
				}
			}
		}

		// Right border
		SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
		std::cout << "  ";

		SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
		std::cout << std::endl;
	}

	// Bottom border
	SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
	for (int x = 0; x < map.getSize().x + 2; x++)
	{
		std::cout << "  ";
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
	std::cout << std::endl;
}