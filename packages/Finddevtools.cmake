
set(DEVTOOLS_FOUND 1)
set(DEVTOOLS_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
exec_program(${PACMAN} ARGS -Qi devtools OUTPUT_VARIABLE DEVTOOLS_INFO)

if(${DEVTOOLS_INFO} STREQUAL "error: package 'devtools' was not found")
  set(DEVTOOLS_FOUND 0)
endif()
