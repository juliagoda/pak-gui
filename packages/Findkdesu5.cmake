
set(KDESU5_FOUND 1)
set(KDESU5_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi kdesu5 OUTPUT_VARIABLE KDESU5_INFO)

if(${KDESU5_INFO} STREQUAL "error: package 'kdesu5' was not found")
  set(KDESU5_FOUND 0)
endif()

