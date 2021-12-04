#pragma once
#include <limits>
enum class Tempolimit {
	innerorts = 50,
	landstrasse = 100,
	autobahn = std::numeric_limits<int>::max()
};