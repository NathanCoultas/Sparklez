#pragma once
#ifndef SPARKLEZ_ENGINE_GAMEOBJECT_H
#define SPARKLEZ_ENGINE_GAMEOBJECT_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "Application.h"
#include "SceneManager.h"
#include "Component.h"

namespace sparklezEngine
{
	class Component;
	class Transform;
	class Application;

	class GameObject : public Object
	{
		friend class sparklezEngine::Application;
		friend class sparklezEngine::Transform;

	public:
		GameObject();
		GameObject(std::string _name);	
		~GameObject();

		//loop functions
		void Awake();
		void Start();
		void Update();
		void FixedUpdate();
		void Render();

		void Destroy();
		void Instantiate();
		void SetActive(bool _ActiveState);
    void SetStatic(bool _IsStaticState);
		bool IsActive();
    bool IsStatic();

		template <class T>
		std::weak_ptr<T> addComponent()
		{
			std::shared_ptr<T> l_c(new T());
			m_Components.push_back(l_c); 	
			l_c->setName(typeid(T).name());
			l_c->m_MyGameObject = SceneManager::FindGameObjectByName(getName());
			l_c->AwakeBehaviour();
			return l_c;
		};

		template<class T>
		std::weak_ptr<T> getComponent()
		{
			for (int l_i = 0; l_i < m_Components.size(); l_i++)
			{
				std::weak_ptr<T> l_t = std::dynamic_pointer_cast<T>(m_Components.at(l_i));
				if (l_t.lock())
				{
					return l_t; 
				}				
			}
			return std::weak_ptr<T>();	
		};

		std::weak_ptr<Transform> GetTransform();

	private:
		int m_Layer;
		bool m_IsActive;
    bool m_IsStatic;
    bool m_Awake;
		std::vector<std::shared_ptr<Component>> m_Components;

	};
}
#endif