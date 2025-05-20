#ifndef EXCEPTIONCHECK_HPP
#define EXCEPTIONCHECK_HPP

#include "../src/shared/StringFormat.hpp"
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <functional>
#include <string>

template <typename T>
void checkConversionError(T &&conversionFunction, const std::string input,
                          const std::string expectedExceptionText) {
  try {
    auto f = std::function(std::forward<T>(conversionFunction));
    f(input);
    BOOST_ERROR(stringFormat("Expecting conversion '%s' to fail with '%s'",
                             input.c_str(), expectedExceptionText.c_str()));
  } catch (const std::exception &e) {
    BOOST_TEST(e.what() == expectedExceptionText);
  }
}

#endif