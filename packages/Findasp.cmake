
set(ASP_FOUND 1)
set(ASP_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin )
exec_program(${PACMAN} ARGS -Qi asp OUTPUT_VARIABLE ASP_INFO)

if(${ASP_INFO} STREQUAL "error: package 'asp' was not found")
  set(ASP_FOUND 0)
endif()
