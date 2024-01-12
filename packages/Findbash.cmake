
set(BASH_FOUND 1)
set(BASH_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi bash OUTPUT_VARIABLE BASH_INFO)

if(${BASH_INFO} STREQUAL "error: package 'bash' was not found")
  set(BASH_FOUND 0)
endif()

