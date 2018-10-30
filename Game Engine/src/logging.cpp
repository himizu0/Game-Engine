#include "logging.h"
#include <iostream>

namespace engine {
	void Logging::print(const char* x) {
		printf("%s\n", x);
	}

	void Logging::log(const char* log) {
		printf("[Message] %s\n", log);
	}

	void Logging::warning(const char* warning) {
		printf("[Warning] %s\n", warning);
	}

	void Logging::error(const char* error) {
		printf("[Error] %s\n", error);
	}
}