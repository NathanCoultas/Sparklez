#ifndef SPARKLEZ_ENGINE_COMPONENT_AUDIO_SOURCE_H
#define SPARKLEZ_ENGINE_COMPONENT_AUDIO_SOURCE_H
#include "Behaviour.h"
#include "Console.h"

namespace sparklezEngine
{
  class GameObject;
  class AudioSource : public Behaviour
  {
    friend class GameObject;
  public:

    virtual ~AudioSource();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void Destroy();
  private:
   
  };
}
#endif