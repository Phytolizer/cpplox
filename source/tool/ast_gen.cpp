#include <cassert>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fstream>
#include <ostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

static int define_ast(std::string_view output_directory, std::string_view base_name,
        std::vector<std::string_view>&& types);
static void define_type(std::ostream& hpp_writer, std::ostream& cpp_writer,
        std::string_view base_name, std::string_view class_name, std::string_view field_list);

int main(int argc, char** argv) {
    std::span args{argv, static_cast<std::size_t>(argc)};

    if (args.size() != 2) {
        fmt::print(stderr, "Usage: {} <output_directory>\n", args[0]);
        return 64;
    }

    std::string_view output_directory = args[1];

    int ret = define_ast(output_directory, "expr",
            {
                    "binary : expr left, token op, expr right",
                    "grouping : expr expression",
                    "literal : object value",
                    "unary : token op, expr right",
            });
    if (ret != 0) {
        return ret;
    }
}

inline int define_ast(std::string_view output_directory, std::string_view base_name,
        std::vector<std::string_view>&& types) {
    auto hpp_path = std::filesystem::path{output_directory} / (std::string{base_name} + ".hpp");
    auto cpp_path = std::filesystem::path{output_directory} / (std::string{base_name} + ".cpp");

    auto hpp_writer = std::ofstream{hpp_path};
    if (!hpp_writer) {
        fmt::print(stderr, "Could not open {}\n", hpp_path.string());
        return 74;
    }
    auto cpp_writer = std::ofstream{cpp_path};
    if (!cpp_writer) {
        fmt::print(stderr, "Could not open {}\n", cpp_path.string());
        return 74;
    }

    fmt::print(cpp_writer, "#include \"{}.hpp\"\n", base_name);

    fmt::print(hpp_writer, "#pragma once\n\n");
    fmt::print(hpp_writer, "#include <object.hpp>\n");
    fmt::print(hpp_writer, "#include <memory>\n");
    fmt::print(hpp_writer, "\n");
    fmt::print(hpp_writer, "namespace lox {{\n");
    fmt::print(hpp_writer, "\n");
    fmt::print(hpp_writer, "class {} {{\n", base_name);
    fmt::print(hpp_writer, "    virtual ~{}() = default;\n", base_name);
    fmt::print(hpp_writer, "}};\n");
    fmt::print(hpp_writer, "\n");
    for (auto type : types) {
        auto colon = std::find(type.begin(), type.end(), ':');
        assert(colon != type.end());
        auto class_name = std::string_view{type.begin(), colon - 1};
        auto fields = std::string_view{colon + 2, type.end()};
        define_type(hpp_writer, cpp_writer, base_name, class_name, fields);
    }
    fmt::print(hpp_writer, "}} // namespace lox\n");

    return 0;
}

inline void define_type(std::ostream& hpp_writer, std::ostream& cpp_writer,
        std::string_view base_name, std::string_view class_name, std::string_view field_list) {
    fmt::print(hpp_writer, "class {}_{} final : public {} {{\n", class_name, base_name, base_name);
    fmt::print(hpp_writer, "}};\n");
}
