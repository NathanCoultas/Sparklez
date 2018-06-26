#include "Application.h"
#include <iostream>

using namespace sparklezEngine;

void safemain(int argc, char* argv[])
{
	Application::Init(argc, argv);
	Application::Run();
	Application::Destroy();
}

int main(int argc, char* argv[])
{
	safemain(argc, argv);
	return 0;
}
