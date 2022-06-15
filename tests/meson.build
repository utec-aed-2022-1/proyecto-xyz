catch2_tests_exe = executable('main',
                              'main.cpp',
                              'test_sha256.cpp',
                              'test_block.cpp',
                              'test_blockchain.cpp',
                              '../src/sha256.cpp',
                              '../src/block.cpp',
                              '../src/blockchain.cpp',
                              '../src/bank.cpp',
                              '../src/util.cpp',
                              'bctest.cpp',
                              link_with : [],
                              include_directories : inc)

test('project tests', catch2_tests_exe)
