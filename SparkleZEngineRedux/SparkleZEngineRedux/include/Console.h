#ifndef SPARKLEZ_ENGINE_CONSOLE_H
#define SPARKLEZ_ENGINE_CONSOLE_H
#include <string>
#include <iostream>
//#include <sdl\include\SDL.h>

namespace sparklezEngine
{
  class Application;
  class Console
  {
	friend class sparklezEngine::Application;

  public:
	//implement lua Console to allow scripting beyond template functions?
	static void ToggleConsole();
	static void DebugMessage(std::string _msg);
	static void DebugMessage(std::string _msg, float _value);
	static void DebugMessage(std::string _msg, int _value);
	static void DebugMessage(std::string _msg, double _value);
	static void DebugMessage(std::string _msg, bool _bool);
	static void DebugMessage(float _msg);
	static void DebugMessage(int _msg);
	static void DebugMessage(double _msg);
	static void DebugMessage(bool _bool);

	static void ErrorMessage(std::string _msg);
	static void ErrorMessage(std::string _msg, float _value);
	static void ErrorMessage(std::string _msg, int _value);
	static void ErrorMessage(std::string _msg, double _value);
	static void ErrorMessage(std::string _msg, bool _bool);
	static void ErrorMessage(float _msg);
	static void ErrorMessage(int _msg);
	static void ErrorMessage(double _msg);
	static void ErrorMessage(bool _bool);

	static bool GetConsoleStatus();
	static bool GetDebugStatus();

  private:
	static bool m_ConsoleOpen;
	static bool m_DebugMode;
  };
}
#endif