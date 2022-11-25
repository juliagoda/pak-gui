
set(PAK_FOUND 1)
set(PAK_INFO "")

find_program(PAK pacman /bin /usr/bin /usr/local/bin)

if(PAK-NOTFOUND)
  set(PAK_FOUND 0)
endif()
