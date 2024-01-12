
set(PACMAN-CONTRIB_FOUND 1)
set(PACMAN_CONTRIB_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi pacman-contrib OUTPUT_VARIABLE PACMAN_CONTRIB_INFO)

if(${PACMAN_CONTRIB_INFO} STREQUAL "error: package 'pacman-contrib' was not found")
  set(PACMAN-CONTRIB_FOUND 0)
endif()
