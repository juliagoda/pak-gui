
set(DOWNGRADE_FOUND 1)
set(DOWNGRADE_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi downgrade OUTPUT_VARIABLE DOWNGRADE_INFO)

if(${DOWNGRADE_INFO} STREQUAL "error: package 'downgrade' was not found")
  set(DOWNGRADE_FOUND 0)
endif()
