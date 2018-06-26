#include "Behaviour.h"
#include "GameObject.h"
namespace sparklezEngine
{
  class Editor : public Behaviour
  {
  public:

    void Awake();
    void Start();
    void Update();
    void FixedUpdate();

    void Destroy();
  private:
  };
}