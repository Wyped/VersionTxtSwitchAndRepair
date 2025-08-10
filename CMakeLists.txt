cmake_minimum_required(VERSION 3.11)

project(VersionTxtSwitchAndRepair)

add_executable(${PROJECT_NAME} main.c fileio.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    psppower
    pspctrl
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wno-int-conversion -trigraphs)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/eboot/ICON0.png"
    BACKGROUND_PATH "${CMAKE_CURRENT_SOURCE_DIR}/eboot/PIC1.png"
    TITLE "Version.txt Switch and Repair"
    VERSION 01.00
)
