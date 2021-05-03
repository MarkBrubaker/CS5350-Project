#pragma once

#include <chrono>
#include <random>

//Times a function in miliseconds
//Pass in a pointer to a function and it's paramaters
template<typename F, typename... Args>
constexpr double Time(F func, Args&&... args) {
	auto t1 = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	return (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
}

//Times a function in miliseconds
//Pass in an object, a pointer to a member function of that object and it's paramaters
template<typename O, typename F, typename... Args>
constexpr double TimeClass(O object, F func, Args&&... args) {
	auto t1 = std::chrono::high_resolution_clock::now();
	//No clue how I got this function pointer back magic to work
	(object->*func)(std::forward<Args>(args)...);
	return (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
}

//Times a function in miliseconds
//Pass in an object, a pointer to a member function of that object and nullptr
//Used when the function has no arguments
template<typename O, typename F, typename... Args>
constexpr double TimeClass(O object, F func, std::nullptr_t) {
	auto t1 = std::chrono::high_resolution_clock::now();
	(object->*func)();
	return (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
}

//https://stackoverflow.com/questions/32071721/error-in-using-mt19937-with-random-device-as-static-class-members
struct RandomNumberGenerator {
	static std::random_device   m_rd;
	static std::mt19937         m_rng;
public:
	static double getRandomNumber(const double& rangeStart, const double& rangeEnd);
	static double getNormalNumber(const double& max);
};