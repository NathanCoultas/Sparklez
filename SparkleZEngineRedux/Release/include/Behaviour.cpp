#include "Behaviour.h"
#include "Component.h"
#include "Object.h"

namespace sparklezEngine
{
	void Behaviour::AwakeBehaviour()
	{
		Awake();
	}

	void Behaviour::UpdateBehaviour()
	{
		Update();
	}

	void Behaviour::DestroyBehaviour()
	{
		Destroy();
	}

	Behaviour::~Behaviour()
	{
      Destroy();
	}

	void Behaviour::Awake()
	{

	}

	void Behaviour::Start()
	{

	}

	void Behaviour::Update()
	{

	}

	void Behaviour::FixedUpdate()
	{

	}

	void Behaviour::Render()
	{

	}

	void Behaviour::Destroy()
	{
      SetDestroyed(true);
	}
}