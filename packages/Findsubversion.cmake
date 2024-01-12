
set(SUBVERSION_FOUND 1)
set(SUBVERSION_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi subversion OUTPUT_VARIABLE SUBVERSION_INFO)

if(${SUBVERSION_INFO} STREQUAL "error: package 'subversion' was not found")
  set(SUBVERSION_FOUND 0)
endif()
