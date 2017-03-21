
add_executable(${PROJECT_NAME}-osgiTest.bin
	arkhe/osgi/osgiTest.cpp
	arkhe/osgi/core/BackTraceTest.cpp
)

include_directories(
    ${GOOGLEMOCK_INCLUDE_DIR}
)

target_link_libraries( ${PROJECT_NAME}-osgiTest.bin ${PROJECT_NAME}-osgi   ${GOOGLEMOCK_LIBRARIES}  gmock_main.d)