
set(DOWNGRADE_FOUND 1)
set(DOWNGRADE_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
exec_program(${PACMAN} ARGS -Qi downgrade OUTPUT_VARIABLE DOWNGRADE_INFO)

if(${DOWNGRADE_INFO} STREQUAL "error: package 'downgrade' was not found")
  set(DOWNGRADE_FOUND 0)
endif()
