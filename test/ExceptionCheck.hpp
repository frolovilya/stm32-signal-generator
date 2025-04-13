#ifndef EXCEPTIONCHECK_HPP
#define EXCEPTIONCHECK_HPP

#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <functional>
#include <string>

template <typename T>
void checkConversionError(
    //     std::function<T(const std::string)> conversionFunction,
    T&& conversionFunction,
    const std::string input, const std::string expectedExceptionText) {
  try {
    auto f = std::function(std::forward<T>(conversionFunction));
    f(input);
    BOOST_ERROR("Expecting conversion to fail");
  } catch (const std::exception &e) {
    BOOST_TEST(e.what() == expectedExceptionText);
  }
}

#endif