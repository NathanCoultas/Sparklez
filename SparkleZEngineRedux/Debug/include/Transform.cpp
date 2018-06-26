#include "Transform.h"
#include "GameObject.h"
#include <memory>

#include "glm/gtx/quaternion.hpp"
#include "glm\gtx\rotate_vector.hpp"

namespace sparklezEngine
{
	void Transform::AwakeBehaviour()
	{

	}

	void Transform::DestroyBehaviour()
	{

	}

	Transform::Transform()
	{
		m_Parent = std::weak_ptr<Transform>();
		m_localPosition = glm::vec3(0, 0, 0);
		m_localRotation = glm::vec3(0, 0, 0);
		m_objectScale = glm::vec3(1, 1, 1);

		setName("Transform");
	}

	Transform::Transform(glm::vec3 _position)
	{
		m_Parent = std::weak_ptr<Transform>();
		m_localPosition = _position;
		m_localRotation = glm::vec3(0, 0, 0);
		m_objectScale = glm::vec3(1, 1, 1);
		setName("Transform");
	}

	Transform::Transform(glm::vec3 _position, glm::vec3 _rotation)
	{
		m_Parent = std::weak_ptr<Transform>();
		m_localPosition = _position;
		m_localRotation = _rotation;
		m_objectScale = glm::vec3(1, 1, 1);
		setName("Transform");
	}

	Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		m_Parent = std::weak_ptr<Transform>();
		m_localPosition = _position;
		m_localRotation = _rotation;
		m_objectScale = _scale;
		setName("Transform");
	}

	void Transform::SetPosition(float posX, float posY, float posZ)
	{
			m_localPosition.x = posX;
			m_localPosition.y = posY;
			m_localPosition.z = posZ;
	}

	void Transform::ModifyPosition(float posX, float posY, float posZ)
	{	
		m_localPosition.x += posX;
		m_localPosition.y += posY;
		m_localPosition.z += posZ;
	}

	void Transform::SetPosition(glm::vec3 _inputvec)
	{
		m_localPosition = _inputvec;
	}

	void Transform::ModifyPosition(glm::vec3 _inputvec)
	{
		m_localPosition += _inputvec;
	}

	void Transform::SetRotation(float rotX, float rotY, float rotZ)
	{
		m_localRotation.x = rotX;
		m_localRotation.y = rotY;
		m_localRotation.z = rotZ;
	}

	void Transform::ModifyRotation(float rotX, float rotY, float rotZ)
	{
		m_localRotation.x += rotX;
		m_localRotation.y += rotY;
		m_localRotation.z += rotZ;
	}

	void Transform::SetRotation(glm::vec3 _inputvec)
	{
		m_localRotation = _inputvec;	
	}

	void Transform::ModifyRotation(glm::vec3 _inputvec)
	{
		m_localRotation += _inputvec;
	}


   glm::vec3 Transform::GetPostion()
   {
      Transform* l_transform = this;
      glm::vec3 l_position = m_localPosition;

      /*
      while (m_Parent.lock())
      {
      //has parent
      l_position = l_position + l_transform->GetLocalPosition();
      l_transform = l_transform->GetParentTransform().lock();
      }*/

      return m_localPosition;
   }

   glm::vec3 Transform::GetRotation()
   {
      std::weak_ptr<Transform> l_transform;
      glm::vec3 l_rotation = m_localRotation;

      /*
      while (m_Parent.lock())
      {
      //has parent
      l_rotation = l_rotation + l_transform.lock()->GetLocalRotation();
      l_transform = l_transform.lock()->GetParentTransform().lock();
      }
      */

      return m_localRotation;
   }

	glm::vec3 Transform::GetLocalPosition()
	{
		return m_localPosition;
	}

	glm::vec3 Transform::GetLocalRotation()
	{
		return m_localRotation;
	}

	glm::vec3 Transform::GetForwardVector()
	{
		glm::vec3 l_DirectionVec = glm::vec3(0, 0, 1.0f);
		glm::mat4 l_Rotmat = glm::mat4(1.0f);
		glm::mat4 l_rotationMat = glm::rotate(l_Rotmat, glm::radians(GetRotation().z), glm::vec3(0, 0, 1.0f));
		l_rotationMat = glm::rotate(l_rotationMat, glm::radians(GetRotation().x), glm::vec3(1.0f, 0, 0));
		l_rotationMat = glm::rotate(l_rotationMat, glm::radians(GetRotation().y), glm::vec3(0, 1.0f, 0));
    return glm::normalize(glm::vec3(glm::vec4(l_DirectionVec, 1.0f) * l_rotationMat));;
		/*
    //REPLACE
		glm::vec3 l_rtrnVec = glm::vec3(0, 0, 1);
		if (GetRotation().x != 0)
		{
		l_rtrnVec.y = (cos(GetRotation().x) * l_DirectionVec.y) - (sin(GetRotation().x) * l_DirectionVec.z);
		l_rtrnVec.z = (sin(GetRotation().x) * l_DirectionVec.y) + (cos(GetRotation().x) * l_DirectionVec.z);
		}

		if (GetRotation().y != 0)
		{
		l_rtrnVec.z = (cos(GetRotation().y) * l_DirectionVec.z) - (sin(GetRotation().y) * l_DirectionVec.x);
		l_rtrnVec.x = (sin(GetRotation().y) * l_DirectionVec.z) + (cos(GetRotation().y) * l_DirectionVec.x);
		}

		if (GetRotation().z != 0)
		{
		l_rtrnVec.x = (cos(GetRotation().z) * l_DirectionVec.x) - (sin(GetRotation().z) * l_DirectionVec.y);
		l_rtrnVec.y = (sin(GetRotation().z) * l_DirectionVec.x) + (cos(GetRotation().z) * l_DirectionVec.y);
		}
		*/

	}

  glm::vec3 Transform::GetUpVector()
  {
	  glm::vec3 l_DirectionVec = glm::vec3(0,1.0f,0);
	  glm::mat4 l_Rotmat = glm::mat4(1.0f);
	  glm::mat4 l_rotationMat = glm::rotate(l_Rotmat, glm::radians(GetRotation().z), glm::vec3(0, 0, 1.0f));
    l_rotationMat = glm::rotate(l_rotationMat, glm::radians(GetRotation().x), glm::vec3(1.0f, 0, 0));
    l_rotationMat = glm::rotate(l_rotationMat, glm::radians(GetRotation().y), glm::vec3(0, 1.0f, 0));

	  return glm::normalize(glm::vec3(glm::vec4(l_DirectionVec, 1.0f) * l_rotationMat));
  }

  glm::vec3 Transform::GetRightVector()
  {
    return glm::cross(GetForwardVector(), GetUpVector());
  }

	glm::vec3 Transform::GetTransformScale()
	{
		return m_objectScale;
	}

	void Transform::SetTransformScale(glm::vec3 _inputvec)
	{
		m_objectScale = _inputvec;
	}

	void Transform::SetTransformScale(float _scaleX, float _scaleY, float _scaleZ)
	{
		m_objectScale.x = _scaleX;
		m_objectScale.y = _scaleY;
		m_objectScale.z = _scaleZ;
	}

	void Transform::SetTransformScale(float _scale)
	{
		m_objectScale.x = _scale;
		m_objectScale.y = _scale;
		m_objectScale.z = _scale;
	}

	void Transform::SetParent(std::weak_ptr<Transform> _transform)
	{
		//removes this transform from current parents children
		if (m_Parent.lock() != NULL)
		{
			for (int _i = 0; _i < this->m_Parent.lock()->m_Children.size(); _i++)
			{
				if (this->m_Parent.lock()->m_Children.at(_i).lock().get() == this)
				{
					this->m_Parent.lock()->m_Children.erase(this->m_Parent.lock()->m_Children.begin() + _i);
					break;
				}
			}
		}

		//adds this transform to the new parents children
		if (_transform.lock() != NULL)
		{
			_transform.lock()->m_Children.push_back(std::shared_ptr<Transform>(this));
		}

		//resets global position and then realigns it with new parent
		m_Parent = std::weak_ptr<Transform>();
		SetPosition(GetPostion());
		SetRotation(GetRotation());
		m_Parent = _transform;
		SetPosition(GetPostion());
		SetRotation(GetRotation());
	}

	std::weak_ptr<Transform> Transform::GetParentTransform()
	{
		return m_Parent;
	}

	int Transform::GetChildCount()
	{
		return m_Children.size();
	}

	std::weak_ptr<Transform> Transform::GetChildAt(int _index)
	{
		return m_Children.at(_index);
	}

	std::weak_ptr<Transform> Transform::FindChild(std::string _name)
	{
		for (int i = 0; i < m_Children.size(); i++)
		{
			if (m_Children.at(i).lock()->getMyGameObject().lock()->getName() == _name)
			{			
				return m_Children.at(i);
			}
		}

		return std::weak_ptr<Transform>();
	}

	void Transform::DetachChildren()
	{
		while (m_Children.size() > 0)
		{
			std::weak_ptr<Transform> m_childTransform = m_Children.at(0);
			m_childTransform.lock()->SetParent(std::weak_ptr<Transform>());

		}
		m_Children.clear();
	}

	void Transform::LookAt(glm::vec3 _worldPos)
	{
		//work on later
	}
	std::string Transform::GetGameObjectName()
	{
		return getMyGameObject().lock()->getName();
	}
}