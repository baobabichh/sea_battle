#ifndef SBAT_RANDOM_H
#define SBAT_RANDOM_H

#include <random>
#include <ctime>

namespace sbat
{

	class Random
	{
	public:

		Random();

		virtual ~Random() = default;

		template<typename T>
		static T rand(const T& left, const T& right);

	private:
		static std::mt19937 random_generator;
		static std::random_device device;
	};

	template<typename T>
	static T Random::rand(const T& left, const T& right)
	{
		std::uniform_int_distribution<T> range(left, right);
		return range(random_generator);
	}
}



#endif // !SBAT_RANDOM_H

