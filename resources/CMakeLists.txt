
set(pak-gui_ICONS
  icons/app/16-apps-pak-gui.png
  icons/app/22-apps-pak-gui.png
  icons/app/32-apps-pak-gui.png
  icons/app/48-apps-pak-gui.png
  icons/app/64-apps-pak-gui.png
  icons/app/sc-apps-pak-gui.svgz
)

ecm_install_icons(ICONS ${pak-gui_ICONS} DESTINATION ${KDE_INSTALL_ICONDIR} THEME hicolor)

add_subdirectory(translations)
