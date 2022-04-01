project(
    'cpplox',
    'cpp',
    default_options : ['cpp_std=c++20', 'warning_level=3'],
    version : '0.1.0'
)

fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')
magic_enum_proj = subproject('magic_enum')
magic_enum_dep = magic_enum_proj.get_variable('magic_enum_dep')

subdir('source')
