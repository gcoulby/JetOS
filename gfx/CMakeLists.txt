# Video subdirectory CMake configuration

# Add sources specific to video
target_sources(jet-os PRIVATE
    cvideo.c
    renderer.c
)

pico_generate_pio_header(jet-os
        ${CMAKE_CURRENT_LIST_DIR}/cvideo.pio
)

# Link libraries specific to video
target_link_libraries(jet-os
        hardware_dma
        hardware_pio
        hardware_timer
        hardware_clocks
)
