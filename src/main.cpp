#include "ChunkHandler.hpp"
#include "Window.hpp"
#include <stdlib.h>

Player					g_player;
float					g_deltaTime;

int		main(int ac, char **av)
{
	Window			window;

	try
	{
		window.init();
		if (ac == 2)
			window.loop(true, (unsigned int)strtoul(av[1], NULL, 10));
		else
			window.loop(false, 0);
	}
	catch (VoxException & e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	catch (std::bad_alloc & e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	exit(0);
	return 0;
}
