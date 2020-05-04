#include "window.h"
// namespace limpan
// {
    class sprite
    {
        public:
            sprite(unsigned char* img, unsigned int imgLen, limpan::window* win_ptr)
                : _renderer(win_ptr->getRenderer()),
                _texture(win_ptr->getTexture())
            {
                
                //auto surface = IMG_Load(imgPath.c_str());
                auto surface = IMG_Load_RW( SDL_RWFromMem((void*)img, imgLen), 1);
                
                if (!surface) {
                	throw std::runtime_error("Failed to create surface\n");
                }

                _texture = SDL_CreateTextureFromSurface(_renderer, surface);

                if (!_texture) {
                	throw std::runtime_error("Failed to create texture\n");
                }

                SDL_FreeSurface(surface);

                
            }


            void setProperties(int xPos, int yPos, int height, int width, std::tuple<int, int, int> color)
            {
                SDL_Rect rect = { xPos /*- (width/2)*/, yPos /*- (height/2)*/, height, width };

                auto r = std::get<0>(color);
                auto g = std::get<1>(color);
                auto b = std::get<2>(color);

                if (_texture)
                {
                    SDL_SetTextureColorMod(_texture, r, g, b);
                    SDL_RenderCopy(_renderer, _texture, nullptr, &rect);
                }
                else
                {
                    SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
                    SDL_RenderFillRect(_renderer, &rect);
                    // SDL_RenderDrawRect(_renderer, &rect);
                }

                SDL_RenderPresent(_renderer);
            }

        private:
            SDL_Renderer* _renderer;
            SDL_Texture* _texture;

    };
// }
