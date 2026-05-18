# xash3d's build system is kinda ass (and i couldn't figure out how to use it), so i made a cmake one :grin:
# could be cleaned up a bit but im a lazy guy

cmake_minimum_required(VERSION 3.20)
project(xash3d C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set the sources
file (GLOB CLIENT_SRCS
    ${PROJECT_SOURCE_DIR}/engine/client/*.c
    ${PROJECT_SOURCE_DIR}/engine/client/avi/*.c
    ${PROJECT_SOURCE_DIR}/engine/client/vgui/*.c
)
file (GLOB COMMON_SRCS
    ${PROJECT_SOURCE_DIR}/engine/common/*.c
    ${PROJECT_SOURCE_DIR}/engine/common/soundlib/*.c
    ${PROJECT_SOURCE_DIR}/engine/common/soundlib/libmpg/*.c
    ${PROJECT_SOURCE_DIR}/engine/common/imagelib/*.c
)
file (GLOB PLATFORM_SRCS
    ${PROJECT_SOURCE_DIR}/engine/platform/dsi/*.c
    ${PROJECT_SOURCE_DIR}/engine/platform/stub/*.c
    ${PROJECT_SOURCE_DIR}/engine/platform/misc/kmalloc.c
    ${PROJECT_SOURCE_DIR}/engine/platform/misc/lib_static.c
)
file (GLOB SERVER_SRCS
    ${PROJECT_SOURCE_DIR}/engine/server/*.c
)
file (GLOB PUBLIC_SRCS
    ${PROJECT_SOURCE_DIR}/public/*.c
)
file (GLOB SOFTWARE_SRCS
    ${PROJECT_SOURCE_DIR}/ref_soft/r_aclip.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_beams.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_bsp.c
    #${PROJECT_SOURCE_DIR}/ref_soft/r_context.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_decals.c
    #${PROJECT_SOURCE_DIR}/ref_soft/r_draw.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_edge.c
    #${PROJECT_SOURCE_DIR}/ref_soft/r_glblit.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_image.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_light.c
    #${PROJECT_SOURCE_DIR}/ref_soft/r_main.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_math.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_misc.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_part.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_polyse.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_rast.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_scan.c
    #${PROJECT_SOURCE_DIR}/ref_soft/r_sprite.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_studio.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_surf.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_triapi.c
    ${PROJECT_SOURCE_DIR}/ref_soft/r_vgui.c
)

add_executable(xashds ${CLIENT_SRCS} ${COMMON_SRCS} ${PLATFORM_SRCS} ${SERVER_SRCS} ${PUBLIC_SRCS} ${SOFTWARE_SRCS})

# oh my god bruh
target_include_directories(xashds PRIVATE
    ${PROJECT_SOURCE_DIR}/public
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_SOURCE_DIR}/pm_shared
    ${PROJECT_SOURCE_DIR}/engine
    ${PROJECT_SOURCE_DIR}/engine/common
    ${PROJECT_SOURCE_DIR}/engine/client
    ${PROJECT_SOURCE_DIR}/engine/client/vgui
    ${PROJECT_SOURCE_DIR}/engine/server
    ${PROJECT_SOURCE_DIR}/engine/platform
    ${PROJECT_SOURCE_DIR}/engine/platform/swap
    ${PROJECT_SOURCE_DIR}/engine/platform/dsi
)

target_compile_definitions(xashds PRIVATE XASH_DSI _NDS XASH_NO_NETWORK SINGLE_BINARY XASH_NO_ASYNC_NS_RESOLVE)
target_compile_definitions(xashds PRIVATE STDINT_H=<stdint.h>)

# Half-Life is a 1998 first-person shooter (FPS) game developed by John Valve
nds_create_rom(xashds
    NAME "Xash3D"
    AUTHOR "John Valve"
    ICON "icon-ds.png"
)
