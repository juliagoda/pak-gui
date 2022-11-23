
set(PAK_FOUND 1)
set(PAK_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin )
exec_program(${PACMAN} ARGS -Qi pak OUTPUT_VARIABLE PAK_INFO)

if(${PAK_INFO} STREQUAL "error: package 'pak' was not found")
  set(PAK_FOUND 0)
endif()
