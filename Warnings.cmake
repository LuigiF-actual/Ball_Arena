

if(LINUX)
    # Had problems building the first on Linux (Mint 22) time so decided to include this
    find_path(X11_INCLUDE_DIR X11/Xlib.h)
    if(NOT X11_INCLUDE_DIR)
        message(FATAL_ERROR 
            "\n[ERROR] Missing X11 development libraries!\n"
            "Please run the following command in your terminal to fix this\n"

            "==================================================================================================\n"

            "sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev\n"
            
            "==================================================================================================\n"
            
            "see more at https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#wayland"
        )
    endif()
endif()


