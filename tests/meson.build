catch2_tests_exe = executable('main',
                              'main.cpp',
                              'test_sha256.cpp',
                              '../src/sha256.cpp',
                              '../src/block.cpp',
                              '../src/blockchain.cpp',
                              'bctest.cpp',
                              link_with : [],
                              include_directories : inc)

test('project tests', catch2_tests_exe)
