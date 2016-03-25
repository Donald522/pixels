#include "app/Application.h"
#include <unistd.h>
#include <syslog.h>


int main(int argc, char* argv[])
{
	char optionString[] = "w:h:fd";
	int opt = getopt(argc, argv, optionString);

	Config_t cfg;

	while (opt != -1)
	{
		switch (opt)
		{
			case 'w':
				sscanf(optarg, "%d", &cfg.gWidth);
				break;
			case 'h':
				sscanf(optarg, "%d", &cfg.gHeight);
				break;
			case 'f':
				cfg.gFullscreen = true;
				break;
			case 'd':
				cfg.gDebug = true;
				break;
			default:
				break;
		}
		opt = getopt(argc, argv, optionString);
	}

	try
	{
		openlog("Pixels", LOG_PID | LOG_PERROR, LOG_USER);
		Application app(cfg);
		app.Run();
		closelog();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
