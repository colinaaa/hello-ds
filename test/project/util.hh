#ifndef TEST_UTIL_HH
#define TEST_UTIL_HH

#include <unistd.h>

#define MAGIC_ENUM_RANGE_MAX 256
#define MAGIC_ENUM_RANGE_MIN 0
#include <filesystem>
#include <magic_enum.hpp>

#include "Parser/Parser.hh"

const auto cwd = std::filesystem::current_path();

const auto root = cwd.filename() == "hello-ds" ? cwd : cwd.parent_path();

#ifdef COVERAGE
const auto exec = root / "cmake-build-cov" / "test" / "tcc";
#else
const auto exec = root / "build" / "tcc";
#endif

const auto test_case_path = root / "test" / "project" / "cases";

inline auto exec_cmd(const char* cmd) -> std::pair<std::string, int> {
  std::array<char, 128> buffer{};
  std::string result;
  int return_code = -1;
  auto pclose_wrapper = [&return_code](FILE* cmd) { return_code = pclose(cmd); };
  {  // scope is important, have to make sure the ptr goes out of scope first
    const std::unique_ptr<FILE, decltype(pclose_wrapper)> pipe(popen(cmd, "r"), pclose_wrapper);
    if (pipe) {
      while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
      }
    }
  }
  return std::make_pair(result, return_code);
}

inline auto tokenName(int tk) {
  return magic_enum::enum_name(static_cast<Project::Parser::Token>(tk));
}

#endif  // TEST_TUIL_HH
