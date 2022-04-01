#pragma once

#include <optional>
#include <string>
#include <variant>

namespace lox {
using object = std::optional<std::variant<double, std::string>>;
} // namespace lox
