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

#include <cmath>

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

	srand(time(NULL));

	limpan::window frame("DVD bounce");
	sprite DVD(DVD_logo_png, DVD_logo_png_len, &frame);
	SDL_SetWindowMinimumSize(frame.getWindow(), frame.getImgWidth(), frame.getImgHeight());


	// int xPos = randNum(0, frame.getWindowHeight());
	// int yPos = randNum(0, frame.getWindowWidth());

	double rad = 200;

	long double xPos, yPos;

	// std::cout << "xpos: " << xPos << " Ypos: " << yPos << "\n";

	int xSpeed = 1.0;
	int ySpeed = 1.0;

	int red,green,blue = 255;

	std::tuple<int, int, int> color(red, green, blue);	

	color = pickColor(100, 255);

	const double TwoPi = 2.0 * std::acos(1.0);
	double t = 0.0;

	while (!frame.isClosed())
	{	
		// A debug cout to check the xpos and the ypos
		// std::cout << "xpos: " << xPos << " Ypos: " << yPos << "\n";

		// Check for events
		frame.windowEvents();

		// Regulate the actual speed of the moving logo
		std::this_thread::sleep_for(std::chrono::milliseconds(5));


		if (rad > frame.getWindowHeight())
		{
			rad =  frame.getWindowHeight() / 2;
		}
		else
		{
			rad = 200;
		}
		


		// Moving the Position of the DVD  in a circle
		xPos = (frame.getWindowWidth() / 2.0) + rad * std::cos(t);
		yPos = (frame.getWindowHeight() / 2.0) + rad * std::sin(t);

		t += 0.01;
		if( t > TwoPi ) t -= TwoPi;

		// std::cout << "xpos: " << xPos << " Ypos: " << yPos << "\n";

		// int xPos = (frame.getWindowWidth() - frame.getImgWidth() ) / 2;
		// int yPos = frame.getWindowHeight() / 2;

		// if (frame.getWindowWidth() <= xPos + frame.getImgWidth())
		// {
		// 	xSpeed = -xSpeed;
		// 	xPos = frame.getWindowWidth() - frame.getImgWidth();

		// 	color = pickColor(100, 255);
		// }
		// else if (xPos <= 0)
		// {
		// 	xPos = 0;
		// 	xSpeed = -xSpeed;
		// 	color = pickColor(100, 255);
		// }

		// if (yPos + frame.getImgHeight() >= frame.getWindowHeight())
		// {
		// 	ySpeed = -ySpeed;
		// 	yPos = frame.getWindowHeight() - frame.getImgHeight();

		// 	color = pickColor(100, 255);

		// }
		// else if (yPos <= 0)
		// {
		// 	yPos = 0;
		// 	ySpeed = -ySpeed;
		// 	color = pickColor(100, 255);

		// }

		// Set the background color to black
		frame.setWindowBGcolor(255, 255, 255, 255);	
		// Update logo (pos, size, color)
		DVD.setProperties(xPos, yPos, frame.getImgWidth(), frame.getImgHeight(), color);
	}


}