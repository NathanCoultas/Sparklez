#include "Application.h"
#include "Input.h"
#include "Window.h"
#include "SceneManager.h"
#include "Console.h"
#include "GameObject.h"
#include "Component.h"
#include "Behaviour.h"
#include "Camera.h"
#include "Colour.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "GraphicsCache.h"
#include "Shader.h"
#include "Material.h"
#include "Rigidbody.h"
#include "AudioSource.h"
#include "BoundsBox.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Light.h"
#include "CharacterController.h"
#include "Transform.h"

//behaviours
#include "Editor.h"

#include "gl\glew.h"
#include "sdl\include\SDL.h"
#include "bullet\btBulletDynamicsCommon.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <fstream>

namespace sparklezEngine
{
  //std::shared_ptr<Context> Application::m_context;
  float Application::m_lasttime;
  float Application::m_time;
  float Application::m_Fixedtime;
  int Application::m_FrameCount;
  bool Application::m_IsRunning;
  SDL_Surface* Application::m_surface;
  SDL_Window* Application::m_window;
  SDL_Renderer* Application::m_renderer;
  SDL_GLContext Application::m_glContext;
  int Application::m_argc;
  std::vector<std::string> Application::m_argv;

  std::string Application::getArgv(int _i)
  {
    return m_argv.at(_i);
  }

  int Application::getArgc()
  {
    return m_argc;
  }

  void Application::setTitle(std::string _title)
  {
    SDL_SetWindowTitle(m_window, _title.c_str());
  }

  void Application::Init(int _agrc, char* _agrv[])
  {
    m_IsRunning = true;
    m_argc = _agrc;

    for (int i = 0; i < _agrc; i++)
    {
      m_argv.push_back(_agrv[i]);
    }

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
      Console::ErrorMessage("Failed to initialize SDL");
    }

    m_window = SDL_CreateWindow("SparkleZEngine", 50, 50, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    m_glContext = SDL_GL_CreateContext(m_window);

    if (m_window == NULL)
    {
      Console::ErrorMessage("Failed to create SDL window");
    }
    SDL_GL_MakeCurrent(m_window, m_glContext);

    SceneManager::m_EditMode = false;
    SceneManager::m_Runtime = true;
    SceneManager::m_SceneLoading = false;

    Window::m_width = 800;
    Window::m_height = 600;

    Console::m_ConsoleOpen = false;
    Console::m_DebugMode = false;

    glewInit();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //physics init
    
    SceneManager::InitPhysicsWorld(0,-10,0);

    GraphicsCache::SetupShaders();
    //--- 
    //spawn in some objs
    new GameObject("Cube"); 
    new GameObject("Cube1"); 
    new GameObject("Sphere");
    new GameObject("floor");
    new GameObject("MainCamera");
	SceneManager::FindGameObjectByName("floor").lock()->SetStatic(true);
	SceneManager::FindGameObjectByName("Sphere").lock()->GetTransform().lock()->SetRotation(glm::vec3(90, 0, 0));
	SceneManager::FindGameObjectByName("Cube").lock()->GetTransform().lock()->SetPosition(glm::vec3(0, 32, 0));
	SceneManager::FindGameObjectByName("Cube1").lock()->GetTransform().lock()->SetPosition(glm::vec3(0, 30, 0));
	SceneManager::FindGameObjectByName("Sphere").lock()->GetTransform().lock()->SetPosition(glm::vec3(1, 5, 0));
	SceneManager::FindGameObjectByName("floor").lock()->GetTransform().lock()->SetPosition(glm::vec3(0, -2, 0));
	SceneManager::FindGameObjectByName("floor").lock()->GetTransform().lock()->SetTransformScale(glm::vec3(50, 1, 50));
	SceneManager::FindGameObjectByName("MainCamera").lock()->GetTransform().lock()->SetPosition(glm::vec3(0, 0, 0));
	SceneManager::FindGameObjectByName("MainCamera").lock()->GetTransform().lock()->SetRotation(glm::vec3(0, 0, 0));
    SceneManager::FindGameObjectByName("Cube").lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/cube.obj");
    SceneManager::FindGameObjectByName("Cube1").lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/cube.obj");
    SceneManager::FindGameObjectByName("Sphere").lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/sphere.obj");
	SceneManager::FindGameObjectByName("floor").lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/cube.obj");
    SceneManager::FindGameObjectByName("floor").lock()->getComponent<MeshRenderer>().lock()->SetMaterial(GraphicsCache::GetMaterial("DefaultMat2"));
    SceneManager::FindGameObjectByName("Sphere").lock()->getComponent<MeshRenderer>().lock()->SetMaterial(GraphicsCache::GetMaterial("DefaultMat3"));

	SceneManager::FindGameObjectByName("floor").lock()->addComponent<BoxCollider>();
	SceneManager::FindGameObjectByName("Cube").lock()->addComponent<BoxCollider>();
	SceneManager::FindGameObjectByName("Cube1").lock()->addComponent<BoxCollider>();
	SceneManager::FindGameObjectByName("Sphere").lock()->addComponent<SphereCollider>();

    
    SceneManager::FindGameObjectByName("MainCamera").lock()->addComponent<Camera>(); 
    SceneManager::FindGameObjectByName("MainCamera").lock()->addComponent<Editor>();

	//SceneManager::FindGameObjectByName("MainCamera").lock()->addComponent<SphereCollider>().lock()->SetKimetic(true);


	m_time = 0;
	m_Fixedtime = 0;
	m_FrameCount = 0;
	m_lasttime = SDL_GetTicks();

	//vysnc interval
	SDL_GL_SetSwapInterval(1.0f);
  }

  void Application::Destroy()
  {
	Exit();
    //m_context.reset();
  }

  void Application::Run()
  {
    if (m_IsRunning == false)
    {
      return;
    }

    while (m_IsRunning == true)
    {
      engineloop();
    }

    m_IsRunning = false;
  }

  void Application::Exit()
  {
    m_IsRunning = false;
    SDL_Quit();
  }

  void Application::display()
  {
    glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, Window::getWidth(), Window::getHeight());

    if (Camera::GetMainCamera().lock().get() != NULL && Camera::GetMainCamera().lock()->getMyGameObject().lock()->IsActive() == true)
    {

      Colour m_ClearC = Camera::GetMainCamera().lock()->GetBackgroundColour();
      glClearColor(m_ClearC.m_r, m_ClearC.m_g, m_ClearC.m_b, m_ClearC.m_a);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //render call
      for (size_t l_i = 0; l_i < sparklezEngine::SceneManager::m_SceneObjects.size(); l_i++)
      {
        sparklezEngine::SceneManager::m_SceneObjects.at(l_i)->Render();
      }
    }

    //post render / gui call should be here
    
  }

  void Application::engineloop()
  {
	//SDL handles vysnc
	SDL_GL_SwapWindow(m_window);
	//newframe
	m_FrameCount++;

	//input handler
	SDL_Event m_event;
    while (SDL_PollEvent(&m_event))
    {
      
      if (m_event.type == SDL_QUIT)
      {
        m_IsRunning = false;
      }
      if(m_event.type == SDL_WINDOWEVENT)
      {     
        if (m_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
          reshape(m_event.window.data1, m_event.window.data2);
        }
        if (m_event.window.event == SDL_WINDOWEVENT_ENTER)
        {
          Input::m_MouseInWindow = true;
        }
        if (m_event.window.event == SDL_WINDOWEVENT_LEAVE)
        {
          Input::m_MouseInWindow = false;
        }
      }
      else if (m_event.type == SDL_MOUSEMOTION)
      {
        Input::UpdateMouseMotion(m_event.motion.xrel, m_event.motion.yrel);
        Input::UpdateMousePosition(m_event.motion.x, m_event.motion.y);
      }
      else if (m_event.type == SDL_MOUSEBUTTONDOWN)
      {
        //mouse(m_event.button.button, SDL_MOUSEBUTTONDOWN, Input::mousePosition.x,Input::mousePosition.y);
      }
      else if (m_event.type == SDL_MOUSEBUTTONUP)
      {
        //mouse(m_event.button.button, SDL_MOUSEBUTTONUP, Input::mousePosition.x,Input::mousePosition.y);
      }
      else if (m_event.type == SDL_KEYDOWN)
      {
        Input::keyDown(m_event.key.keysym.scancode);
      }
      else if (m_event.type == SDL_KEYUP)
      {
        Input::keyUp(m_event.key.keysym.scancode);
      }
    }
	//scene update
	update();
	//render 
    display();
  }

  void Application::reshape(int _width, int _height)
  {
    Window::m_width = _width;
    Window::m_height = _height;
  }

  void Application::update()
  {
	float l_time = SDL_GetTicks();
	float l_diff = l_time - m_lasttime;
	SceneManager::m_deltaTime = l_diff;
	m_lasttime = l_time;
	if ((l_time / 1000.0f) >= m_time)
	{
	  m_time += 1.0f;
	  Console::DebugMessage("FPS: ",m_FrameCount);
	  m_FrameCount = 0;
	}

    if (SceneManager::m_EditMode == true && SceneManager::m_Runtime == false)
    {
      //editor mode

    }
    else if (SceneManager::m_EditMode == false && SceneManager::m_Runtime == true)
    {
      //runtime mode 
      for (size_t l_i = 0; l_i < sparklezEngine::SceneManager::m_SceneObjects.size(); l_i++)
      {
        sparklezEngine::SceneManager::m_SceneObjects.at(l_i)->Update();
      }
      //fixed update  
	  if ((l_time / 1000.0f) >= m_Fixedtime)
	  {
		m_Fixedtime += 0.02f;
		//Console::DebugMessage("FixedUpdate");
		SceneManager::m_dynamicsWorld->stepSimulation(1 / 60.f, 10);
		for (size_t l_i = 0; l_i < sparklezEngine::SceneManager::m_SceneObjects.size(); l_i++)
		{
		
		  sparklezEngine::SceneManager::m_SceneObjects.at(l_i)->FixedUpdate();
		  //Console::DebugMessage(sparklezEngine::SceneManager::m_SceneObjects.at(l_i)->GetTransform().lock()->GetPostion().y);
		}
	
	  }
    }

    //clearing destroyed objects
    for (size_t l_i = 0; l_i < SceneManager::m_SceneObjects.size(); l_i++)
    {
      if (SceneManager::m_SceneObjects.at(l_i)->m_destroyed == true)
      {
        SceneManager::m_SceneObjects.at(l_i)->Destroy();

        SceneManager::m_SceneObjects.erase(SceneManager::m_SceneObjects.begin() + l_i);
        l_i--;
      }
    }

	//clear and reset input
	Input::m_MouseMotion = glm::vec2(0, 0);
    Input::m_downKeys.clear();
    Input::m_upKeys.clear();
  }
}
