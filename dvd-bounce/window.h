// #pragma once
#ifndef limpan_window_h
#define limpan_window_h

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>
#include <utility>
// #include <iostream>

#include <stdexcept>

namespace limpan
{
	class window {
	public:
		window(std::string title) : _title(title)
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0)
			{
				throw std::runtime_error("SDL failed to init\n");
			}
			if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
			{
				throw std::runtime_error("Failed to init SDL image\n");
			}


			SDL_DisplayMode DM;
			SDL_GetDesktopDisplayMode(0, &DM);	

			Uint32 FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;  
			
			_height = DM.h;
			// std::cout << _height << "\n";
			_width = DM.w;
			// std::cout << _width << "\n";

			// if ((_height == NULL || _height == 0) && (_width == NULL || _width == 0)) 
			// {
			// 	_height = 720;
			// 	_width = 1080;
			// }
			
			_window = SDL_CreateWindow(
				_title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				_width/2, _height/2,
				FLAGS
			);

			if (_window == nullptr) {
				throw std::runtime_error("SDL failed to create window\n");
			}

			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

			if (_renderer == nullptr) {
				throw std::runtime_error("SDL failed to create renderer\n");
			}

			
			
		}

		~window()
		{
			SDL_Delay(1);

			SDL_DestroyRenderer(_renderer);
			SDL_DestroyTexture(_texture);

			SDL_DestroyWindow(_window);
			IMG_Quit();
			SDL_Quit();
		}

		
		void windowEvents()
		{
			
			auto windowID = SDL_GetWindowID(_window);
			if (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					_closed = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_q:
						case SDLK_ESCAPE:
							_closed = true;
							break;

						default:
							_closed = false;
							break;
					}
					break;

				case SDL_WINDOWEVENT:  
					if (event.window.windowID == windowID)  {
						switch (event.window.event)  
						{
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
								// std::cout << "size changed to " << event.window.data1 << "x" << event.window.data2 << std::endl;
								_width = event.window.data1;
								_height = event.window.data2;
								// SDL_SetWindowSize(_window, _width, _height);
								break;
						}
					}
				break;
				default:
					break;
				}
			}
		}


		void setWindowBGcolor(int r, int g, int b, int a)
		{
			SDL_SetRenderDrawColor(_renderer, r, g, b, a);
			SDL_RenderClear(_renderer);
		}

		bool isClosed() const { return _closed; }

		// std::pair<int,int> getSize() const
		// {
		// 	int w,h;
		// 	SDL_GetWindowSize(_window, &w, &h);
		// 	return std::make_pair(w,h);
		// }

		int getImgHeight() const { return _imgHeight; }
		int getImgWidth() const { return _imgWidth; }
		int getWindowHeight() const { return _height; }
		int getWindowWidth() const { return _width; }

		SDL_Renderer* getRenderer() const
		{
			return _renderer;
		}

		SDL_Texture* getTexture() const
		{
			return _texture;
		}

		SDL_Window* getWindow() {return _window; }

	private:


		std::string _title = "NOT SET";


		int _height;
		int _width;

		bool _closed = false;

		int _imgHeight = 76;
		int _imgWidth = 128;

		SDL_Event event;
		SDL_Window* _window = nullptr;

		SDL_Renderer* _renderer = nullptr;

		SDL_Texture* _texture = nullptr;
	};
}

#endif