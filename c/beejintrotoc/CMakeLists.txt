cmake_minimum_required(VERSION 3.10)
project(beejintrotoc C)

# Set the C standard
set(CMAKE_C_STANDARD 99) # It's good practice to also add CMAKE_C_STANDARD_REQUIRED ON if you strictly need C99

# Define the source directories
set(SRC_DIRS
        "11-pointers-ii-arithmetic"
        "12_manual_memory_allocation"
        "16-type-qualifiers-and-specifiers" # Assuming your restrict_example.c is here or in a similar directory
        "23-pointers-to-pointers"
        "20-structs-ii-more-fun-with-structs"
        "27-unicode-wide-characters-and-all-that"
        "musl_vs_glibc"
)

# Iterate over each directory and create an executable for each .c file
foreach(DIR IN LISTS SRC_DIRS)
    file(GLOB SRC_FILES "${DIR}/*.c")

    foreach(SRC_FILE IN LISTS SRC_FILES)
        get_filename_component(EXE_NAME ${SRC_FILE} NAME_WE)
        add_executable(${EXE_NAME} ${SRC_FILE})

        # --- Add this line ---
        # This defines WITH_RESTRICT specifically for the target ${EXE_NAME}
        target_compile_definitions(${EXE_NAME} PRIVATE WITH_RESTRICT)
        # ---------------------

        set_target_properties(${EXE_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${DIR}
        )
    endforeach()
endforeach()