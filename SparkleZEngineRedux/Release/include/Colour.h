#pragma once
#ifndef SPARKLEZ_ENGINE_COLOUR_H
#define SPARKLEZ_ENGINE_COLOUR_H

namespace sparklezEngine
{
	class Colour
	{
	public:
		Colour();
		Colour(float _r, float _g, float _b);
		Colour(float _r, float _g, float _b, float _a);

		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};
}
#endif 
