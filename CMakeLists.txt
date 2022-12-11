cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)
set(BOARD pico-w)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(main
    main.cpp
)
add_subdirectory(modules/pico-onewire)
# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib pico_cyw43_arch_none pico_one_wire)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)




if (TARGET tinyusb_device)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(main 1)
    pico_enable_stdio_uart(main 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(main)

    # # add url via pico_set_program_url
    # example_auto_set_url(main)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building main because TinyUSB submodule is not initialized in the SDK")
endif()

add_definitions(-DPICO_ENTER_USB_BOOT_ON_EXIT)