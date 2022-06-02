#include "Random.h"

std::mt19937 sbat::Random::random_generator = std::mt19937(static_cast<unsigned int>(time(0)));
std::random_device sbat::Random::device;

namespace sbat
{
	Random::Random()
	{
		random_generator.seed(device());
		
	}



}