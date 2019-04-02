
#include "../include/utilities.h"

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <map>
#include <unordered_map>

template <
          typename                              value_type,
          template<typename, typename> typename ContainerType
         >
void
fill_random (ContainerType<value_type, std::allocator<value_type>> &container,
             typename ContainerType<value_type, std::allocator<value_type>>::size_type container_size,
             const unsigned int maximum)
{
  RandomDevice rd;
  using size_type = typename ContainerType<value_type, std::allocator<value_type>>::size_type;

  for (size_type i = 0; i < container_size; ++i)
    container.insert(std::end(container), rd.get_random_number<value_type> (0,maximum));
}


#define TEMPLATE_INSTANTIATE(T) \
template \
void \
fill_random (T&, T::size_type, const unsigned int);


TEMPLATE_INSTANTIATE(std::deque<int>);
TEMPLATE_INSTANTIATE(std::list<int>);
TEMPLATE_INSTANTIATE(std::vector<int>);
