#include "InputHandler.h"
#include <iostream>

bool InputHandler::is_key_pressed(const keys& key) const
{
	//std::cout << e_.key.keysym.sym << " == " << static_cast<int>(key) << std::endl;
	return e_.type == SDL_KEYDOWN && e_.key.keysym.sym == static_cast<int>(key);
}

bool InputHandler::poll()
{
	return SDL_PollEvent(&e_);
}
