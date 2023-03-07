file(GLOB pofiles "*.po")
set(TEXTDOMAIN pak-gui)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale)
foreach(pofile IN LISTS pofiles)
  get_filename_component(lang ${pofile} NAME_WE)
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${lang})
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${TEXTDOMAIN}.mo
    DEPENDS
      ${pofile}
    COMMAND msgfmt -o
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${TEXTDOMAIN}.mo
      ${pofile})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${TEXTDOMAIN}.mo DESTINATION /usr/share/locale/${lang}/LC_MESSAGES/)
endforeach()
