# Video subdirectory CMake configuration

# Add sources specific to video
target_sources(jet-os PRIVATE
    ramon.c
)

# Link libraries specific to video
# target_link_libraries(jet-os
#         hardware_dma
#         hardware_pio
#         hardware_timer
#         hardware_clocks
# )
