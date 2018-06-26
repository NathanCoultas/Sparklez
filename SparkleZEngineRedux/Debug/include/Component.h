#ifndef SPARKLEZ_ENGINE_COMPONENT_H
#define SPARKLEZ_ENGINE_COMPONENT_H
#include "Object.h"
#include <memory>

namespace sparklezEngine
{
	class GameObject;
	class Application;

	class Component : public Object
	{
		friend class GameObject;
		friend class Application;

	public:

		virtual ~Component();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void SaveComponent();
		virtual void loadComponent();

		void Instantiate();

		void SetActive(bool _ActiveState);
		bool IsActive();

		std::weak_ptr<GameObject> getMyGameObject();

	private:
		std::weak_ptr<GameObject> m_MyGameObject;

		bool m_IsActive;
	};
}

#endif