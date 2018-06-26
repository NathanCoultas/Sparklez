#ifndef SPARKLEZ_ENGINE_INPUT_H
#define SPARKLEZ_ENGINE_INPUT_H

#include <vector>
#include <string>
#include "glm\glm.hpp"
#include "sdl\include\SDL.h"

namespace sparklezEngine
{
  class Application;

  class Input
  {
	friend class sparklezEngine::Application;

  public:

	static bool getKeyState(std::string _keyCode);
	static bool getKeyDown(std::string _keyCode);
	static bool getKeyUp(std::string _keyCode);

	static bool MouseInWindow();

	static glm::vec2 GetMousPos();
	static glm::vec2 GetMouseMotion();

	static void keyUp(SDL_Scancode _key);
	static void keyDown(SDL_Scancode  _key);

	static void UpdateMousePosition(float _X, float _Y);
	static void UpdateMouseMotion(float _X, float _Y);

	static void clearUpKeys();
	static void clearDownKeys();

  private:
	static std::vector<SDL_Scancode> m_keys;
	static std::vector<SDL_Scancode> m_upKeys;
	static std::vector<SDL_Scancode> m_downKeys;

	static glm::vec2 m_MousePosition;
	static glm::vec2 m_MouseMotion;

	static bool m_MouseInWindow;

  };
}
#endif