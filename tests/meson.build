catch2_tests_exe = executable('main',
                              'main.cpp',
                              'test_sha256.cpp',
                              link_with : [sha256_library],
                              include_directories : inc)

test('project tests', catch2_tests_exe)
