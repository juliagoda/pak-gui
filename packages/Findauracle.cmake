
set(AURACLE_FOUND 1)
set(AURACLE_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
exec_program(${PACMAN} ARGS -Qi auracle-git OUTPUT_VARIABLE AURACLE_INFO)

if(${AURACLE_INFO} STREQUAL "error: package 'auracle-git' was not found")
  set(AURACLE_FOUND 0)
endif()
