// Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef ROCRAND_BENCHMARK_TUNING_DISTRIBUTION_TRAITS_HPP_
#define ROCRAND_BENCHMARK_TUNING_DISTRIBUTION_TRAITS_HPP_

#include "rng/distributions.hpp"

#include "benchmark_rocrand_utils.hpp"

#include <string>

namespace benchmark_tuning
{

template<class T>
struct type_name
{
    // always fails
    static_assert(sizeof(T) == 0,
                  "A specialization of type_name is not implemented for this type.");
};

template<>
struct type_name<unsigned int>
{
    std::string operator()()
    {
        return "unsigned_int";
    }
};

template<>
struct type_name<unsigned char>
{
    std::string operator()()
    {
        return "unsigned_char";
    }
};

template<>
struct type_name<unsigned short>
{
    std::string operator()()
    {
        return "unsigned_short";
    }
};

template<>
struct type_name<unsigned long long>
{
    std::string operator()()
    {
        return "unsigned_long_long";
    }
};

template<>
struct type_name<float>
{
    std::string operator()()
    {
        return "float";
    }
};

template<>
struct type_name<half>
{
    std::string operator()()
    {
        return "half";
    }
};

template<>
struct type_name<double>
{
    std::string operator()()
    {
        return "double";
    }
};

template<class Distribution>
struct distribution_name
{
    // always fails
    static_assert(sizeof(Distribution) == 0,
                  "A specialization of distribution_name is not implemented for this type.");
};

template<class T, class U>
struct distribution_name<uniform_distribution<T, U>>
{
    std::string operator()()
    {
        return "uniform_" + type_name<T>{}();
    }
};

template<class T, class U, unsigned int I>
struct distribution_name<normal_distribution<T, U, I>>
{
    std::string operator()()
    {
        return "normal_" + type_name<T>{}();
    }
};

template<class T, class U, unsigned int I>
struct distribution_name<log_normal_distribution<T, U, I>>
{
    std::string operator()()
    {
        return "log_normal_" + type_name<T>{}();
    }
};

template<>
struct distribution_name<rocrand_poisson_distribution<ROCRAND_DISCRETE_METHOD_ALIAS>>
{
    std::string operator()()
    {
        return "poisson_unsigned_int";
    }
};

template<class Distribution>
struct default_distribution
{
    // always fails
    static_assert(sizeof(Distribution) == 0,
                  "A specialization of default_distribution is not implemented for this type.");
};

template<class T, class U>
struct default_distribution<uniform_distribution<T, U>>
{
    auto operator()(const benchmark_config& /*config*/)
    {
        return uniform_distribution<T, U>{};
    }
};

template<class T, class U, unsigned int I>
struct default_distribution<normal_distribution<T, U, I>>
{
    auto operator()(const benchmark_config& /*config*/)
    {
        const T mean   = 0;
        const T stddev = 1;
        return normal_distribution<T, U, I>(mean, stddev);
    }
};

template<class T, class U, unsigned int I>
struct default_distribution<log_normal_distribution<T, U, I>>
{
    auto operator()(const benchmark_config& /*config*/)
    {
        const T mean   = 0;
        const T stddev = 1;
        return log_normal_distribution<T, U, I>(mean, stddev);
    }
};

template<>
struct default_distribution<rocrand_poisson_distribution<ROCRAND_DISCRETE_METHOD_ALIAS>>
{
    auto operator()(const benchmark_config& config)
    {
        return rocrand_poisson_distribution<ROCRAND_DISCRETE_METHOD_ALIAS>(config.lambda);
    }
};

} // namespace benchmark_tuning

#endif // ROCRAND_BENCHMARK_TUNING_DISTRIBUTION_TRAITS_HPP_
