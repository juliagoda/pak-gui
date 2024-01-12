
set(REFLECTOR_FOUND 1)
set(REFLECTOR_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin )
execute_process(COMMAND ${PACMAN} -Qi reflector OUTPUT_VARIABLE REFLECTOR_INFO)

if(${REFLECTOR_INFO} STREQUAL "error: package 'reflector' was not found")
  set(REFLECTOR_FOUND 0)
endif()
