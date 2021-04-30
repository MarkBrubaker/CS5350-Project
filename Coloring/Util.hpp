#pragma once

#include <chrono>
#include <random>

template<typename F, typename... Args>
double Time(F func, Args&&... args) {
	auto t1 = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
}

//https://stackoverflow.com/questions/32071721/error-in-using-mt19937-with-random-device-as-static-class-members
struct RandomNumberGenerator {
	static std::random_device   m_rd;
	static std::mt19937         m_rng;
public:
	static double getRandomNumber(const double& rangeStart, const double& rangeEnd);
};