#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <iostream>
#include "StringConvertor.h"
#include <string>
#include <random>
#include <limits>
double rand_real_minus10000_10000() {
    static thread_local std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> dist(
        -10000,
        std::nextafter(10000.0, std::numeric_limits<double>::infinity()));
    return dist(rng);
}

int main()
{

    ke::OwnedStringA test = ke::StringConvertor::convertToString(-0.0, 6);
    std::cout << test.c_str() << std::endl;

    for (int idx = 0; idx < 100000; ++idx)
    {
        double testValue = rand_real_minus10000_10000();
        test = ke::StringConvertor::convertToString(testValue, 6);
        if (strcmp(std::to_string(testValue).c_str(), test.c_str()))
        {
            std::cout << std::to_string(testValue) << " -> " << test.c_str() << std::endl;
        }
	}
}