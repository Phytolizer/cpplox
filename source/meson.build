subdir('tool')

cpplox_lib = static_library(
    'cpplox',
    'lib.cpp',
    'scanner.cpp',
    'token.cpp',
    dependencies : [fmt_dep, magic_enum_dep],
)

cpplox_dep = declare_dependency(
    link_with : cpplox_lib,
)

cpplox_exe = executable(
    'cpplox',
    'main.cpp',
    dependencies : [fmt_dep, magic_enum_dep, cpplox_dep],
)
