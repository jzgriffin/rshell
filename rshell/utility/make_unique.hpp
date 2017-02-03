// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017

// This file provides a compatibility bridge between C++11 and C++14 standard
// libraries by implementing the make_unique function where it is not
// provided or using the native implementation where it is.

#ifndef hpp_utility_make_unique
#define hpp_utility_make_unique

#include <memory>
#include <utility>

namespace utility {

#if __cpp_lib_make_unique
using std::make_unique;
#else
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

} // namespace utility

#endif // hpp_utility_make_unique
