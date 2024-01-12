
set(FZF_FOUND 1)
set(FZF_INFO "")

find_program(PACMAN pacman /bin /usr/bin /usr/local/bin)
execute_process(COMMAND ${PACMAN} -Qi fzf OUTPUT_VARIABLE FZF_INFO)

if(${FZF_INFO} STREQUAL "error: package 'fzf' was not found")
  set(FZF_FOUND 0)
endif()
