#include "Window.h"

namespace sparklezEngine
{
	int Window::m_width;
	int Window::m_height;

	int Window::getWidth()
	{
		return m_width;
	}

	int Window::getHeight()
	{
		return m_height;
	}

	void Window::setResolution(int _width, int _height, bool _fullscreen, int _preferredRefreshRate)
	{
		//Application::reshape(_width, _height);
	}

}