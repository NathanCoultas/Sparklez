#include "Camera.h"
#include "Window.h"
#include "Colour.h"
#include "GameObject.h"
#include "glm\gtc/matrix_transform.hpp"
#include "glm\glm.hpp"

#include <memory>
#include <vector>

namespace sparklezEngine
{
	std::weak_ptr<GameObject> Camera::m_MainCamera;
	std::vector<std::weak_ptr<GameObject>> Camera::m_SceneCameras;

	Camera::~Camera()
	{

	}

	std::weak_ptr<Camera> Camera::GetMainCamera()
	{
		if (m_MainCamera.lock() == NULL)
		{
			return std::weak_ptr<Camera>();
		}

		return m_MainCamera.lock()->getComponent<Camera>();
	}
	std::vector<std::weak_ptr<GameObject>>& sparklezEngine::Camera::GetAllCameras()
	{
		return m_SceneCameras;
	}
	void Camera::SetasMainCamera(std::weak_ptr<GameObject> _Cam)
	{
		if (m_MainCamera.lock() == NULL)
		{
			m_MainCamera = _Cam;
		}
		
		m_MainCamera.lock()->getComponent<Camera>().lock()->m_IsMainCamera = false;
		_Cam = m_MainCamera;
		_Cam.lock()->getComponent<Camera>().lock()->m_IsMainCamera = true;
	}
	void Camera::SetCameraBackgroundColour(Colour _colour)
	{
		this->m_camBackgroundColour = _colour;
	}

	Colour Camera::GetBackgroundColour()
	{
		return m_camBackgroundColour;
	}

	void Camera::SetProjectionMatrix(glm::mat4 _projMat)
	{
		this->m_ProjectionMatrix = new glm::mat4();
		*this->m_ProjectionMatrix = _projMat;
	}

	void Camera::ResetProjectionMatrix()
	{
		this->m_ProjectionMatrix = NULL;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		if (m_ProjectionMatrix != NULL)
		{
			return *m_ProjectionMatrix;
		}

		if (m_IsOrthographic == true)
		{
			return glm::ortho(0, Window::getWidth(), Window::getHeight(), 0, -1, 1);
		}
		else
		{
			return glm::perspective(glm::radians(m_CameraFOV), (float)Window::getWidth() / (float)Window::getHeight(), m_NearClipPlane, m_FarClipPlane);	
		}

	}
	void Camera::Awake()
	{
		m_CameraFOV = 90.0f;
		m_IsOrthographic = false;
		m_OrthographicSize = 100;
		m_FarClipPlane = 500.0f;
		m_NearClipPlane = 0.3f;
		
		m_camBackgroundColour = Colour(65.0f / 255.0f, 40.0f / 255.0f, 96.0f / 255.0f, 1.0f);
		

      if (m_MainCamera.lock() == NULL)
      {
         Console::DebugMessage("MainCamera added");
         m_MainCamera = std::weak_ptr<GameObject>(getMyGameObject());
      }
      m_SceneCameras.push_back(std::weak_ptr<GameObject>(getMyGameObject()));
	}

	void Camera::Start()
	{
		
	}

	void Camera::Destroy()
	{
		if (m_IsMainCamera == true)
		{
			m_MainCamera = std::weak_ptr<GameObject>();
		}

		for (int i = 0; i < m_SceneCameras.size(); i++)
		{
			if (m_SceneCameras.at(i).lock() == getMyGameObject().lock())
			{
				m_SceneCameras.erase( m_SceneCameras.begin() + i);
				i--;
			}
		}
	}
}
