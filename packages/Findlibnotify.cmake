
set(LIBNOTIFY_FOUND 1)
set(LIBNOTIFY_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
exec_program(${PACMAN} ARGS -Qi libnotify OUTPUT_VARIABLE LIBNOTIFY_INFO)

if(${LIBNOTIFY_INFO} STREQUAL "error: package 'libnotify' was not found")
  set(LIBNOTIFY_FOUND 0)
endif()
