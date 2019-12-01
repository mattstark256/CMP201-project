#include "MapDisplayer.h"

#include <windows.h>   // WinApi header
#include <iostream>
using namespace std;

#define DEFAULT_COLOUR FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BORDER_COLOUR BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE


MapDisplayer::MapDisplayer()
{
}


MapDisplayer::~MapDisplayer()
{
	delete[] intBuffer;
	delete[] colourBuffer;
}


void MapDisplayer::loadMap(const Map& map)
{
	delete[] intBuffer;
	delete[] colourBuffer;
	bufferSize = map.getSize();
	intBuffer = new int[bufferSize.x * bufferSize.y]{};
	colourBuffer = new int[bufferSize.x * bufferSize.y]{};

	for (int y = 0; y < bufferSize.y; y++)
	{
		for (int x = 0; x < bufferSize.x; x++)
		{
			Vector2i coord(x, y);
			if (map.getValue(coord) == 1)
			{
				setColour(coord, BACKGROUND_BLUE);
			}
		}
	}
}


void MapDisplayer::loadPath(const Path& path)
{
	const std::vector<Vector2i>* pathCoords = path.getPathCoords();
	for (auto coord : *pathCoords)
	{
		setChar(coord, 'x');
		setColour(coord, DEFAULT_COLOUR);
	}

	setChar(path.getStart(), 'S');
	setColour(path.getStart(), DEFAULT_COLOUR);

	setChar(path.getEnd(), 'E');
	setColour(path.getEnd(), DEFAULT_COLOUR);
}


void MapDisplayer::setChar(Vector2i coord, char character)
{
	intBuffer[coord.y * bufferSize.x + coord.x] = (int)character;
}


void MapDisplayer::setInt(Vector2i coord, int i)
{
	intBuffer[coord.y * bufferSize.x + coord.x] = i + 128;
}


void MapDisplayer::setColour(Vector2i coord, int colour)
{
	colourBuffer[coord.y * bufferSize.x + coord.x] = colour;
}


void MapDisplayer::print()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
	for (int x = 0; x < bufferSize.x + 2; x++)
	{
		cout << "  ";
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
	cout << endl;

	for (int y = 0; y < bufferSize.y; y++)
	{
		SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
		cout << "  ";

		for (int x = 0; x < bufferSize.x; x++)
		{
			int i = y * bufferSize.x + x;
			SetConsoleTextAttribute(hConsole, colourBuffer[i]);
			int j = intBuffer[i];
			// If it's a char
			if (j < 128) { cout << " " << (char)j; }
			// If it's a single digit int
			else if (j < 138) { cout << " " << j - 128; }
			// If it's a double digit int
			else if (j < 228) { cout << j - 128; }
			// If it's too large
			else { cout << " ?"; }
		}

		SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
		cout << "  ";

		SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, BORDER_COLOUR);
	for (int x = 0; x < bufferSize.x + 2; x++)
	{
		cout << "  ";
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOUR);
	cout << endl;
}