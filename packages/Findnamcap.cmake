
set(NAMCAP_FOUND 1)
set(NAMCAP_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin )
execute_process(COMMAND ${PACMAN} -Qi namcap OUTPUT_VARIABLE NAMCAP_INFO)

if(${NAMCAP_INFO} STREQUAL "error: package 'namcap' was not found")
  set(NAMCAP_FOUND 0)
endif()
