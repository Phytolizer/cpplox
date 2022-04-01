cpplox_lib = static_library(
    'cpplox',
    'lib.cpp',
    'scanner.cpp',
    'token.cpp',
    dependencies : [gsl_dep, fmt_dep, magic_enum_dep],
)

cpplox_dep = declare_dependency(
    link_with : cpplox_lib,
)

cpplox_exe = executable(
    'cpplox',
    'main.cpp',
    dependencies : [gsl_dep, fmt_dep, magic_enum_dep, cpplox_dep],
)
