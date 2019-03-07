
#ifndef __utilities_h
#define __utilities_h

#include <random>

/**
 * In order to generate random numbers of different types, 
 * i.e. int, unsigned int, float, double, etc. with a uniform distribution,
 * we need a templated generator.
 * 
 * We define a generic templated UniformDistribution struct which is specialized
 * with different types.
 */
template <typename T>
struct UniformDistribution
{
  using type = void;
};

template <>
struct UniformDistribution <int>
{
  using type = std::uniform_int_distribution<int>;
};

template <>
struct UniformDistribution <unsigned int>
{
  using type = std::uniform_int_distribution<unsigned int>;
};

template <>
struct UniformDistribution <float>
{
  using type = std::uniform_real_distribution<float>;
};

template <>
struct UniformDistribution <double>
{
  using type = std::uniform_real_distribution<double>;
};

class RandomDevice
{
  public:
    /**
     * Get a random number of type @tparam T uniformly distributed on
     * the closed interval [@p minimum, @p maximum].
     */
    template <typename T>
    T get_random_number (T minimum, T maximum)
    {
      std::mt19937 mersenne_engine (device());
      typename UniformDistribution<T>::type generator (minimum, maximum);
      return generator(mersenne_engine);
    }

  private:
    std::random_device device;
};


/**
 * Fill a given STL container with random integers.
 */
template <
          typename                              value_type,
          template<typename, typename> typename ContainerType
         >
void
fill_random (ContainerType<value_type, std::allocator<value_type>> &container,
             const unsigned int maximum)
{
  RandomDevice rd;

  for (auto & element : container)
    element = rd.get_random_number<value_type> (0,maximum);
}


#endif // __utilities_h