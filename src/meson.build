sha256_library = library('sha256', 'sha256.cpp',
                           link_with : [],
                           include_directories : inc)

main_exe = executable('main', 'main.cpp',
                      link_with : [sha256_library],
                      include_directories : inc)
