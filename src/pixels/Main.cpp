#include "app/Application.h"

#include <stdexcept>
#include <iostream>
#include "log/Log.h"

int main()
{
	try
	{
		OpenLog( "Log.txt" );
		Application app;
		app.Run();
		CloseLog();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
