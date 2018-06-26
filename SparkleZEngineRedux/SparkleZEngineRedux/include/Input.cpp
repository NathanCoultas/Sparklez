#include "Input.h"

namespace sparklezEngine
{
  std::vector<SDL_Scancode> Input::m_keys;
  std::vector<SDL_Scancode> Input::m_upKeys;
  std::vector<SDL_Scancode> Input::m_downKeys;
  glm::vec2 Input::m_MousePosition;
  glm::vec2 Input::m_MouseMotion;
  bool Input::m_MouseInWindow;


  void Input::clearUpKeys()
  {
	m_upKeys.clear();
  }

  void Input::clearDownKeys()
  {
	m_downKeys.clear();
  }

  bool Input::getKeyState(std::string _key)
  {
	for (int i = 0; i < m_keys.size(); i++)
	{
	  if (SDL_GetKeyName(SDL_GetKeyFromScancode(m_keys.at(i))) == _key)
	  {
		return true;
	  }
	}
	return false;
  }

  bool Input::getKeyUp(std::string _key)
  {
	for (int i = 0; i < m_upKeys.size(); i++)
	{
	  if (SDL_GetKeyName(SDL_GetKeyFromScancode(m_upKeys.at(i))) == _key)
	  {
		return true;
	  }
	}
	return false;
  }

  bool Input::MouseInWindow()
  {
	return false;
  }

  bool Input::getKeyDown(std::string _key)
  {
	for (int i = 0; i < m_downKeys.size(); i++)
	{
	  if (SDL_GetKeyName(SDL_GetKeyFromScancode(m_downKeys.at(i))) == _key)
	  {
		return true;
	  }
	}
	return false;
  }

  glm::vec2 Input::GetMousPos()
  {
	if (m_MouseInWindow == false)
	{
	  return glm::vec2();
	}
	return m_MousePosition;
  }

  glm::vec2 Input::GetMouseMotion()
  {
	if (m_MouseInWindow == false)
	{
	  return glm::vec2();
	}

	glm::vec2 l_rtnvec;
	l_rtnvec.x = m_MouseMotion.x;
	l_rtnvec.y = m_MouseMotion.y;
	return m_MouseMotion;
  }

  void Input::keyUp(SDL_Scancode _key)
  {
	for (size_t i = 0; i < m_keys.size(); i++)
	{
	  if (m_keys.at(i) == _key)
	  {
		m_keys.erase(m_keys.begin() + i);
		i--;
	  }
	}
	m_upKeys.push_back(_key);

  }

  void Input::keyDown(SDL_Scancode _key)
  {
	for (size_t i = 0; i < Input::m_keys.size(); i++)
	{
	  if (Input::m_keys.at(i) == _key)
	  {
		return;
	  }
	}
	m_keys.push_back(_key); // Add key to currently pressed keys
	m_downKeys.push_back(_key); // Register that this key was pressed this frame (will be cleared when display refreshes next frame)

  }

  void Input::UpdateMousePosition(float _X, float _Y)
  {
	m_MousePosition.x = _X;
	m_MousePosition.y = _Y;
  }
  void Input::UpdateMouseMotion(float _X, float _Y)
  {
	m_MouseMotion.x = _X;
	m_MouseMotion.y = _Y;
  }
}