#include "BoundsBox.h"
namespace sparklezEngine
{
  BoundsBox::BoundsBox(glm::vec3 _centerVec, glm::vec3 _size)
  {
    l_CenterVec = _centerVec;
    l_MaxSize = _size;
  }
}