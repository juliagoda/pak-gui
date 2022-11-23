
set(KDESU_FOUND 1)
set(KDESU_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
exec_program(${PACMAN} ARGS -Qi kdesu OUTPUT_VARIABLE KDESU_INFO)

if(${KDESU_INFO} STREQUAL "error: package 'kdesu' was not found")
  set(KDESU_FOUND 0)
endif()

