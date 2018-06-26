#ifndef SPARKLEZ_ENGINE_COMPONENT_TRANSFORM_H
#define SPARKLEZ_ENGINE_COMPONENT_TRANSFORM_H

#include "glm\glm.hpp"
#include "glm\gtc/matrix_transform.hpp" 
#include "glm\gtc/type_ptr.hpp"
#include <memory>
#include <vector>

#include "Behaviour.h"
#include "Object.h"
namespace sparklezEngine
{
	class Transform : public Behaviour
	{
		friend class GameObject;
	public:

		Transform();
		Transform(glm::vec3 _position);
		Transform(glm::vec3 _position, glm::vec3 _rotation);
		Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

		void SetPosition(float posX, float posY, float posZ);
		void ModifyPosition(float posX, float posY, float posZ);

		void SetPosition(glm::vec3 _inputvec);
		void ModifyPosition(glm::vec3 _inputvec);

		void SetRotation(float rotX, float rotY, float rotZ);
		void ModifyRotation(float rotX, float rotY, float rotZ);

		void SetRotation(glm::vec3 _inputvec);
		void ModifyRotation(glm::vec3 _inputvec);;

		glm::vec3 GetForwardVector();
		glm::vec3 GetUpVector();
	    glm::vec3 GetRightVector();

		glm::vec3 GetTransformScale();
		
    //modify this so that it includes the position calculation from it's parent
		glm::vec3 GetPostion();
		glm::vec3 GetRotation();

		glm::vec3 GetLocalPosition();
		glm::vec3 GetLocalRotation();

		void SetTransformScale(glm::vec3 _inputvec);
		void SetTransformScale(float _scaleX, float _scaleY, float _scaleZ);
		void SetTransformScale(float _scale);

		void SetParent(std::weak_ptr<Transform> _transform);
		std::weak_ptr<Transform> GetParentTransform();

		int GetChildCount();
		std::weak_ptr<Transform> GetChildAt(int _index);
		std::weak_ptr<Transform> FindChild(std::string _name);
		void DetachChildren();

		void LookAt(glm::vec3 _worldPos);
		std::string GetGameObjectName();

	private:

		// Position of the model
		glm::vec3 m_localPosition;

		// Orientation of the model
		glm::vec3 m_localRotation;

		//doesn't inherit scale from parent right now could change this
		glm::vec3 m_objectScale;

		std::weak_ptr<Transform> m_Parent;
		std::vector<std::weak_ptr<Transform>> m_Children;

		virtual void AwakeBehaviour();
		virtual void DestroyBehaviour();
	};
}
#endif