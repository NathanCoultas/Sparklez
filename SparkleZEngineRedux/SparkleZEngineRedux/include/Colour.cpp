#include "Colour.h"

namespace sparklezEngine
{
	Colour::Colour()
	{
		this->m_a = 1.0f;
		this->m_r = 1.0f;
		this->m_g = 1.0f;
		this->m_b = 1.0f;
	}

	Colour::Colour(float _r, float _g, float _b)
	{
		this->m_a = 1.0f;
		this->m_r = _r;
		this->m_g = _g;
		this->m_b = _b;
	}

	Colour::Colour(float _r, float _g, float _b, float _a)
	{
		this->m_a = _a;
		this->m_r = _r;
		this->m_g = _g;
		this->m_b = _b;
	}
}