sha256_library = library('sha256', 'sha256.cpp',
                           link_with : [],
                           include_directories : inc)

bank_library = library('bank',
                       'bank.cpp',
                       'bank_operations.cpp',
                       'block.cpp',
                       'blockchain.cpp',
                       'util.cpp',
                       link_with : [sha256_library],
                       include_directories : inc)

httplib_library = library('httplib',
                          'httplib.cpp',
                          include_directories : inc)

server_exe = executable('server',
                        'server.cpp',
                        link_with : [bank_library,
                                     httplib_library],
                        include_directories : inc)

main_exe = executable('main',
                      'main.cpp',
                      'sha256.cpp',
                      'bank.cpp',
                      'block.cpp',
                      'blockchain.cpp',
                      'util.cpp',
                      link_with : [],
                      include_directories : inc)
