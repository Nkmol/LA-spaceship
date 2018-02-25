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
		KEY_ROTATE_LEFT = SDLK_q,
		KEY_ROTATE_RIGHT = SDLK_e,
		KEY_LEFT_CAMERA_MOVE = SDLK_LEFT,
		KEY_RIGHT_CAMERA_MOVE = SDLK_RIGHT,
		KEY_UP_MOVE = SDLK_w,
		KEY_DOWN_MOVE = SDLK_s,
		KEY_UP_CAMERA_MOVE = SDLK_UP,
		KEY_DOWN_CAMERA_MOVE = SDLK_DOWN,
		KEY_SHOOT = SDLK_SPACE,
	};

	enum class events : int
	{
		EVENT_QUIT = SDL_QUIT
	};

	bool is_key_pressed(const keys& key) const;
	bool is_event(const events& event) const;
	bool poll();
}
;