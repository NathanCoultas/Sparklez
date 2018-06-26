#ifndef SPARKLEZ_ENGINE_BOUNDS_BOX_H
#define SPARKLEZ_ENGINE_BOUNDS_BOX_H

#include <memory>
#include <Vector>
#include "glm\glm.hpp"

namespace sparklezEngine
{
  class Mesh;
  class GameObject;
  class BoundsBox 
  {
    friend class sparklezEngine::GameObject;
    friend class sparklezEngine::Mesh;
  public:
    glm::vec3 l_CenterVec;
    glm::vec3 l_MaxSize;
    
	BoundsBox(glm::vec3 _centerVec, glm::vec3 _size);

  private:
  };
}

#endif