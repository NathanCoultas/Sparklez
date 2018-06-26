#include "Behaviour.h"
#include "GameObject.h"


namespace sparklezEngine
{
	class BehaviourTemplate : public Behaviour
	{
	public:
		
		//This function is called as soon as possible after the object has been made both in edit time and play time.
		void Awake()
		{
			//All behaviours must have their name set as their class name at runtime
			setName("BehaviourTemplate");
			//std::cout << typename(this) < std::endl;
		}

		//This function is called slightly after the Awake function and only during playtime
		//called when the first Update cycle gets to the behaviour
		void Start()
		{
			
		}

		//This function is called Every single frame
		void Update()
		{
        
		}

		//This function is called seperately over time and is not dependant on frame rate
		void FixedUpdate()
		{

		}

		//this function is called every render pass
		void Render()
		{

		}

		//called when the behaviour has been marked for destruction 
		//either by script or automatically
		void Destroy()
		{

		}

		//an example of a public function callable by other behaviours
		void PublicTemplateFunction()
		{

		}

		//an example of a public variable accessable by other behaviours
		int TemplatePublicInt = 4;

	private:
		//an example of a public variable unaccessable by other behaviours
		int TemplatePrivateInt = 4;
		
		//an example of a private function only callable by this behaviour
		void PrivateTemplateFunction()
		{

		}
	};

}