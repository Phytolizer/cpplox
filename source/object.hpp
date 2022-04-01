#pragma once

#include <optional>
#include <string>
#include <variant>

namespace lox {
using object = std::optional<std::variant<double, std::string>>;
namespace object_kind {
enum kind
{
    number = 0,
    string = 1,
};
} // namespace obj
} // namespace lox
