#include "Console.h"

namespace sparklezEngine
{
  bool Console::m_ConsoleOpen;
  bool Console::m_DebugMode;

  void Console::ToggleConsole()
  {
	if (m_ConsoleOpen == true)
	{
	  //toggle console stuff
	  Console::m_ConsoleOpen = false;
	}
	else
	{
	  //toggle console stuff
	  Console::m_ConsoleOpen = true;
	}
  }
  void Console::DebugMessage(std::string _msg)
  {
	std::cout << "DEBUG: " << _msg << std::endl;
  }
  void Console::DebugMessage(std::string _msg, float _value)
  {
	std::cout << "DEBUG: " << _msg << _value << std::endl;
  }
  void Console::DebugMessage(std::string _msg, int _value)
  {
	std::cout << "DEBUG: " << _msg << _value << std::endl;;
  }
  void Console::DebugMessage(std::string _msg, double _value)
  {
	std::cout << "DEBUG: " << _msg << _value << std::endl;
  }
  void Console::DebugMessage(float _msg)
  {
	std::cout << "DEBUG: " << _msg << std::endl;
  }
  void Console::DebugMessage(int _msg)
  {
	std::cout << "DEBUG: " << _msg << std::endl;
  }
  void Console::DebugMessage(double _msg)
  {
	std::cout << "DEBUG: " << _msg << std::endl;
  }
  void Console::ErrorMessage(std::string _msg)
  {
	std::cout << "ERROR: " << _msg << std::endl;
  }

  bool Console::GetConsoleStatus()
  {
	return Console::m_ConsoleOpen;
  }
  bool Console::GetDebugStatus()
  {
	return Console::m_DebugMode;
  }
}