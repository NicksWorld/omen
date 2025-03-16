project(
  'omen',
  'cpp',
  meson_version : '>=1.1',
  version : '0.0.0',
  default_options : [
    'cpp_std=c++20'
  ],
)

# Directory where main executable and dependencies should be installed
omen_binary_install_dir = 'engine'

cpp = meson.get_compiler('cpp')

# Extra warnings, intended for development
if get_option('pedantic')
  add_project_arguments(
    cpp.get_supported_arguments(
      # gcc-like
      '-Wshadow',
      '-Wconversion',
      '-Wsign-conversion',
      '-pedantic',
      '-Wold-style-cast',
      '-Woverloaded-virtual',
      '-Wimplicit-fallthrough',
      '-Wcast-align',
      '-Wsign-compare',
    ),
    language : [ 'c', 'cpp' ],
  )
endif

# Targets
subdir('common')
subdir('engine')
subdir('launcher')

if get_option('tests')
  subdir('test')
endif
