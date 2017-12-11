#pragma once
#include <SDL.h>

class InputHandler
{
public:
	static InputHandler& instance()
	{
		static InputHandler instance;
		return instance;
	}
private:
	InputHandler() {}

	SDL_Event e_;
public:
	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;

	// Key mapping
	enum class keys : int
	{
		KEY_ACCELERATE = SDLK_LSHIFT,
		KEY_LEFT_ROLL = SDLK_q,
		KEY_RIGHT_ROLL = SDLK_e,
		KEY_LEFT_MOVE = SDLK_a,
		KEY_RIGHT_MOVE = SDLK_d,
		KEY_UP_MOVE = SDLK_w,
		KEY_DOWN_MOVE = SDLK_s,
		KEY_SHOOT = SDLK_SPACE,
	};

	bool is_key_pressed(const keys& key) const;
	bool poll();
}
;