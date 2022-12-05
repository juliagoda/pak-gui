
set(KSSHASKPASS_FOUND 1)
set(KSSHASKPASS_INFO "")

find_program(KSSHASKPASS ksshaskpass /bin /usr/bin /usr/local/bin)

if(KSSHASKPASS-NOTFOUND)
  set(KSSHASKPASS_FOUND 0)
endif()
