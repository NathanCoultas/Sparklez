#pragma once
#ifndef SPARKLEZ_ENGINE_OBJECT_H
#define SPARKLEZ_ENGINE_OBJECT_H

#include <string>
#include <memory>


namespace sparklezEngine
{

	class Application;
	class GameObject;
	class Component;

	class Object
	{
		friend class Application;
		friend class GameObject;
		friend class Component;

	public:
		Object();
		virtual ~Object();

		std::string getName();
		void setName(std::string _name);

		void DestroyOnLoad(std::weak_ptr<GameObject> m_GameObj, bool _state);
		void DestroyOnLoad(bool _state);
		
		bool CheckIfDestroyed();
		void SetDestroyed(bool _State);

		//revist
		virtual void Destroy();
		virtual void Instantiate();

	private:
		//Object Name, could just make this public
		std::string m_Name;

		bool m_destroyOnLoad;
		bool m_destroyed;

	};
}

#endif