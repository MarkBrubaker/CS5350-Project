#include "Util.hpp"

std::random_device   Random::m_rd;
std::mt19937         Random::m_rng(Random::m_rd());

//between start and end
//includeive of start but not end
double Random::getRandomNumber(const double& rangeStart, const double& rangeEnd) {
	std::uniform_real_distribution<> randomizer(rangeStart, rangeEnd);
	return randomizer(m_rng);
}

double Random::getNormalNumber(const double& max) {
	double sum = 0;
	for(int x = 0; x < 3; x++) {
		sum += Random::getRandomNumber(0, 1);
	}
	return sum / 3 * max;
}