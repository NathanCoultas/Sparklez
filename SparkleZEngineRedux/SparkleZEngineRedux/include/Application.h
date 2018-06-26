#ifndef SPARKLEZ_ENGINE_APPLICATION_H
#define SPARKLEZ_ENGINE_APPLICATION_H

/*
Main Runtime/loop file, handles engine looping.
*/

#include <string>
#include <vector>
#include <memory>
#include "Object.h"
#include "sdl\include\SDL.h"
//#include "bullet\src\btBulletDynamicsCommon.h"
//use doxygen for auto documentation


namespace sparklezEngine
{
  class Window;
  class SceneManager;
  class Console;
  class Input;
  class GameObject;
  class CharacterController;
  class Resources;
  class Camera;
  class Application;
  class Mesh;
  class Material;
  class MeshRenderer;

  class Application
  {
	friend class sparklezEngine::Window;
	friend class sparklezEngine::Console;
	friend class sparklezEngine::SceneManager;
	friend class sparklezEngine::Input;
	friend class sparklezEngine::Camera;
	friend class sparklezEngine::MeshRenderer;
	friend class sparklezEngine::GameObject;

  public:
	//init needs to call scenemanager::newscene at startup
	static void Init(int _argc, char* _argv[]);
	static void Destroy();
	static void Run();
	static void Exit();

	static int getArgc();
	static std::string getArgv(int _i);
	static void setTitle(std::string _title);

  private:
	static void reshape(int _width, int _height);
	static void display();
	static void engineloop();
	static void update();

	//static std::shared_ptr<Context> m_context;

	static float m_lasttime;
	static float m_time;
	static float m_Fixedtime;
	static int m_FrameCount;

	static bool m_IsRunning;
	static SDL_Surface* m_surface;
	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;
	static SDL_GLContext m_glContext;
	static int m_argc;
	static std::vector<std::string> m_argv;
  };
}
#endif