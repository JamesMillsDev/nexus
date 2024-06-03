cmake_minimum_required(VERSION 3.10)

project(nexus VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# MACRO to add all directories in result
MACRO(SUBDIRLIST result firstdir curdir)
    file(GLOB ENDF6_SRC_TOP RELATIVE
        ${curdir} ${curdir}/*)
    file(GLOB_RECURSE ENDF6_SRC_NESTED ${curdir}/*)
    set(children ${ENDF6_SRC_TOP} ${ENDF6_SRC_NESTED})

    SET(dirlist "${firstdir}")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${curdir}/${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# MACRO to add all directories in result
MACRO(SOURCE_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.cpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        if(NOT ${dir_path} MATCHES "CMake")
            SET(dir_list ${dir_list} ${file_path})
        endif()
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

function(include_all_files)
    #argv[0] - result variable, argv[1] - add relative paths, set "" if you don't want it
    #argv[2] - path to folder with folders
    SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Nexus)
    SOURCE_DIRECTORIES(SUBFILES)
    
    add_library(nexus STATIC ${SUBFILES})
    
    target_include_directories(nexus PUBLIC ${SUBDIRS} ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml)

    FOREACH(subdir ${SUBDIRS})
        message("[INFO] found header directory: ${subdir}.")
    ENDFOREACH()

    FOREACH(subfile ${SUBFILES})
        message("[INFO] found source file: ${subfile}.")
    ENDFOREACH()
    
endfunction()

include_all_files()

add_subdirectory(tinyxml)