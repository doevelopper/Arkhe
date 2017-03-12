function(common_library Name)
    string(TOUPPER ${Name} NAME)

    set(INCLUDE_NAME ${${NAME}_INCLUDE_NAME})
    if(NOT INCLUDE_NAME)
        set(INCLUDE_NAME ${PROJECT_INCLUDE_NAME})
    endif()

    set(namespace ${${NAME}_NAMESPACE})

    if(NOT namespace)
        set(namespace ${PROJECT_namespace})
    endif()

    string(TOUPPER ${namespace} NAMESPACE)
    set(SOURCES ${${NAME}_SOURCES})
    set(HEADERS ${${NAME}_HEADERS})
    set(PUBLIC_HEADERS ${${NAME}_PUBLIC_HEADERS})
    set(LINK_LIBRARIES ${${NAME}_LINK_LIBRARIES})

    set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})
    configure_file("${PROJECT_SOURCE_DIR}/src/main/resources/Api.hpp.in"
                   "${PROJECT_SOURCE_DIR}/core/src/main/cpp/didactics/core/Api.hpp" 
                    @ONLY
    )
    configure_file(${CMAKE_SOURCE_DIR}/src/main/resources/Version.hpp
                   ${CMAKE_SOURCE_DIR}/core/src/main/cpp/didactics/core/Version.hpp @ONLY)
    configure_file(${CMAKE_SOURCE_DIR}/src/main/resources/Version.cpp
                   ${CMAKE_SOURCE_DIR}/core/src/main/cpp/didactics/core/Version.cpp @ONLY)
endfunction()

