# You can set verbose cmake messages:
set(AL_VERBOSE_OUTPUT 1)


set(allolib_directory allolib)

set(app_files_list
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb.hpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb.cpp
)

# other directories to include. You can use relative paths to the
# source file being built.
set(app_include_dirs extra
)

# other libraries to link
set(app_link_libs
)

# definitions. Prepend -D to any defines
set(app_definitions
    -DUSE_COLOR
)

# compile flags
# This flag ignores unused variable warning. You probably don't want to do this...
set(app_compile_flags
    -Wno-unused-variable
)

# linker flags, with `-` in the beginning
set(app_linker_flags
)
