sources = [
  'src/hash.cpp',
  'src/settings.cpp',
]

gtest_dep = dependency('gtest_main', main : true, required : true)
omen_test = executable(
  'omen_test',
  sources,
  dependencies : [ gtest_dep, omen_engine_dep, omen_common_dep ],
)

test('omen_test', omen_test)
