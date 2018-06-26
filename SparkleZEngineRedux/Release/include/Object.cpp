#include "Object.h"
#include "GameObject.h"

namespace sparklezEngine
{
	Object::Object()
	{
		m_Name = "";
		m_destroyed = false;
		m_destroyOnLoad = true;
	}

	Object::~Object()
	{

	}

	std::string Object::getName()
	{
		return m_Name;
	}

	void Object::setName(std::string _name)
	{
		m_Name = _name;
	}

	void Object::DestroyOnLoad(bool _state)
	{
		m_destroyOnLoad = _state;
	}

   bool Object::CheckIfDestroyed()
   {
      return m_destroyed;
   }

   void Object::SetDestroyed(bool _State)
   {
      m_destroyed = _State;
   }

	void Object::DestroyOnLoad(std::weak_ptr<GameObject> m_GameObj, bool _state)
	{
		m_GameObj.lock()->m_destroyOnLoad = _state;
	}

	void Object::Destroy()
	{
		m_destroyed = true;
	}

	void Object::Instantiate()
	{
		//Put to console, Instantiation of Object is not supported.
	}
}

