project(
    'cpplox',
    'cpp',
    default_options : ['cpp_std=c++20', 'warning_level=3'],
    version : '0.1.0'
)

gsl_proj = subproject('gsl')
gsl_dep = gsl_proj.get_variable('gsl_dep')
fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')

subdir('source')
