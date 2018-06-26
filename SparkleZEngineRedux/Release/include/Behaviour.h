#ifndef SPARKLEZ_ENGINE_COMPONENT_BEHAVIOUR_H
#define SPARKLEZ_ENGINE_COMPONENT_BEHAVIOUR_H
#include "Component.h"
#include "Console.h"

namespace sparklezEngine
{

	class Behaviour : public Component
	{
		friend class GameObject;
	public:
    
		virtual ~Behaviour();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();
		
	private:
	
		void AwakeBehaviour();
		void UpdateBehaviour();
		void DestroyBehaviour();

	};

}

#endif