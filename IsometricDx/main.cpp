#include "Engine.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>

int main(int argc, char* args[]) {
	srand(time(NULL));

	Engine* engine = new Engine();
	engine->Go();
	delete engine;

	std::string abc;
	std::cin >> abc;

	return 0;
}