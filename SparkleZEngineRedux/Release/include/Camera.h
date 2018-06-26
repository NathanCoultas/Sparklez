#pragma once
#ifndef SPARKLEZ_ENGINE_CAMERA_H
#define SPARKLEZ_ENGINE_CAMERA_H
#include "Behaviour.h"
#include "Colour.h"

#include "glm\gtc/matrix_transform.hpp"
#include "glm\glm.hpp"

#include <memory>
#include <vector>

namespace sparklezEngine 
{
	class sparklezEngine::Application;

	class Camera : public Behaviour
	{
		friend class sparklezEngine::Application;

	public:
		virtual ~Camera();
		
		static std::weak_ptr<Camera> GetMainCamera();
		static std::vector<std::weak_ptr<GameObject>> &GetAllCameras();
		static void SetasMainCamera(std::weak_ptr<GameObject> _Cam);

		void SetCameraBackgroundColour(Colour _colour);
		Colour GetBackgroundColour();

		void SetProjectionMatrix(glm::mat4 _projMat);
		void ResetProjectionMatrix();
		glm::mat4 GetProjectionMatrix();

	private:
		virtual void Awake();
		virtual void Start();
		virtual void Destroy();

		Colour m_camBackgroundColour;
		glm::mat4* m_ProjectionMatrix;

		float m_NearClipPlane;
		float m_FarClipPlane;
		float m_CameraFOV;
		float m_OrthographicSize;

		bool m_IsOrthographic;
		bool m_IsMainCamera;

		static std::weak_ptr<GameObject> m_MainCamera;
		static std::vector<std::weak_ptr<GameObject>> m_SceneCameras;
	};
}

#endif 