#ifndef SPARKLEZ_ENGINE_WINDOW_H
#define SPARKLEZ_ENGINE_WINDOW_H

namespace sparklezEngine
{
	class Application;

	class Window
	{
		friend class sparklezEngine::Application;

	public:
		static int getWidth();
		static int getHeight();
		static void setResolution(int _width, int _height, bool _fullscreen, int _preferredRefreshRate = 0);

	private:
		static int m_width;
		static int m_height;
	};
}
#endif