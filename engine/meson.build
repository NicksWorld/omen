sources = [
  'src/application.cpp',
  'src/settings.cpp',
]

omen_engine_inc = include_directories('include')

tomlplusplus_subproject = subproject(
  'tomlplusplus',
  default_options : ['default_library=static'] # Static is header-only
)
tomlplusplus_dep = tomlplusplus_subproject.get_variable('tomlplusplus_dep')

omen_engine_lib = static_library(
  'omen_engine',
  sources,
  include_directories : omen_engine_inc,
  dependencies : [ tomlplusplus_dep, omen_common_dep ],
)
omen_engine_dep = declare_dependency(
  link_with : omen_engine_lib,
  include_directories : omen_engine_inc,
)
