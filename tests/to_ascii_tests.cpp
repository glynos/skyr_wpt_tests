// Copyright 2020 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <skyr/domain/domain.hpp>

// Tests using test data from W3C
// https://github.com/w3c/web-platform-tests/tree/master/url


using json = nlohmann::json;

namespace {
struct test_case_data {
  explicit test_case_data(json object) {
    input = object["input"].get<std::string>();
    auto output = object["output"];
    if (!output.is_null()) {
      expected_output = object["output"].get<std::string>();
    }
  }

  std::string input;
  std::optional<std::string> expected_output;
};

class TestCaseGenerator : public Catch::Generators::IGenerator<test_case_data> {
 public:
  explicit TestCaseGenerator(
      const std::string &filename) {
    std::ifstream fs{filename};
    json tests;
    fs >> tests;

    for (auto &&test_case_object : tests) {
      if (!test_case_object.is_string()) {
        test_case_data_.emplace_back(test_case_object);
      }
    }
    it_ = begin(test_case_data_);
  }

  const test_case_data &get() const override {  // NOLINT
    assert(it_ != test_case_data_.end());
    return *it_;
  }

  bool next() override {
    assert(it_ != test_case_data_.end());
    ++it_;
    return it_ != test_case_data_.end();
  }

 private:
  std::vector<test_case_data> test_case_data_;
  std::vector<test_case_data>::const_iterator it_;
};

auto test_case(const std::string &filename) {
  return Catch::Generators::GeneratorWrapper<test_case_data>(
      std::make_unique<TestCaseGenerator>(filename));
}
} // namespace

TEST_CASE("to_ascii", "[web_platform]") {
  auto test_case_data = GENERATE(test_case("toascii.json"));

  INFO("to_ascii(" << test_case_data.input << ") -> "
                   << (test_case_data.expected_output ? test_case_data.expected_output.value() : "null"));

  auto output = skyr::domain_to_ascii(test_case_data.input);
  REQUIRE(output.has_value() == test_case_data.expected_output.has_value());
  if (output.has_value()) {
    CHECK(test_case_data.expected_output.value() == output.value());
  }
}
