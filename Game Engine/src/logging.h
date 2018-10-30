#pragma once

namespace engine {
	class Logging {
		public:
		static void print(const char* x);
		static void log(const char* log);
		static void warning(const char* warning);
		static void error(const char* error);
	};
}