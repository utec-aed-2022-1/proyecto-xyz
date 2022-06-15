sha256_library = library('sha256', 'sha256.cpp',
                           link_with : [],
                           include_directories : inc)

main_exe = executable('main',
                      'main.cpp',
                      'sha256.cpp',
                      'block.cpp',
                      'blockchain.cpp',
                      'bank.cpp',
                      'util.cpp',
                      link_with : [],
                      include_directories : inc)
