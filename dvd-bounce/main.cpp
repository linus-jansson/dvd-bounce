#include "window.h"
#include "sprite.h"
#include "DVD_logo.h"
#include <chrono>
#include <thread>
// #include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>

int randNum(int min, int max)
{
	return rand() % max + min;
}

std::tuple<int, int, int> pickColor(int min, int max)
{

	int r = rand() % max + min;
	int g = rand() % max + min;
	int b = rand() % max + min;

	return std::tuple<int, int, int>(r, g, b);
}

int main()
{		
	// try
	// {

	srand(time(NULL));

	limpan::window frame("DVD bounce");
	sprite DVD(DVD_logo_png, DVD_logo_png_len, &frame);
	SDL_SetWindowMinimumSize(frame.getWindow(), frame.getImgWidth(), frame.getImgHeight());


	int xPos = randNum(0, frame.getWindowHeight());
	int yPos = randNum(0, frame.getWindowWidth());

	int xSpeed = 2;
	int ySpeed = 2;

	int r,g,b = 255;

	std::tuple<int, int, int> color(r, g, b);	

	color = pickColor(100, 255);
	// std::cout << "hello\n";
	while (!frame.isClosed())
	{	
		// Check for events
		frame.windowEvents();

		// Regulate the actual speed of the moving logo
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		// Moving the Position of the DVD 
		xPos = xPos + xSpeed;
		yPos = yPos + ySpeed;

		if (frame.getWindowWidth() <= xPos + frame.getImgWidth())
		{
			xSpeed = -xSpeed;
			xPos = frame.getWindowWidth() - frame.getImgWidth();

			color = pickColor(100, 255);
			

		}
		else if (xPos <= 0)
		{
			xPos = 0;
			xSpeed = -xSpeed;
			color = pickColor(100, 255);
		}

		if (yPos + frame.getImgHeight() >= frame.getWindowHeight())
		{
			ySpeed = -ySpeed;
			yPos = frame.getWindowHeight() - frame.getImgHeight();

			color = pickColor(100, 255);

		}
		else if (yPos <= 0)
		{
			yPos = 0;
			ySpeed = -ySpeed;
			color = pickColor(100, 255);

		}

		// Set the background color to black
		frame.setWindowBGcolor(0, 0, 0, 255);	
		// Update logo (pos, size, color)
		DVD.setProperties(xPos, yPos, frame.getImgWidth(), frame.getImgHeight(), color);

		// color = pickColor(100, 255);
		// xPos = randNum(0, frame.getWindowHeight());
		// yPos = randNum(0, frame.getWindowWidth());
	}

	// }
	// catch (const std::exception & e)
	// {
	// 	std::ofstream f("exceptions.txt", std::ios::app);
	// 	f << e.what() << '\n';
	// 	return 1;
	// }
}