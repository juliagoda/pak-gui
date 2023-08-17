file(GLOB pofiles "*.po")
set(app pak-gui)

foreach(pofile IN LISTS pofiles)
  get_filename_component(lang ${pofile} NAME_WE)
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${lang})
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES)
    add_custom_command(
      OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${app}.mo
      DEPENDS
        ${pofile}
      COMMAND msgfmt -o
        ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${app}.mo
        ${pofile}
    )
    add_custom_target(gen_${lang} ALL DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${app}.mo
    )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/locale/${lang}/LC_MESSAGES/${app}.mo DESTINATION /usr/share/locale/${lang}/LC_MESSAGES/)
endforeach()
