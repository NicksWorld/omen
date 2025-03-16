sources = [
  'src/hash.cpp',
]

omen_common_inc = include_directories('include')

# TODO: Make omen_common export a C-style api, to allow for a shared library.
omen_common_lib = static_library(
  'omen_common',
  sources,
  include_directories : omen_common_inc,
)
omen_common_dep = declare_dependency(
  link_with : omen_common_lib,
  include_directories : omen_common_inc,
)
