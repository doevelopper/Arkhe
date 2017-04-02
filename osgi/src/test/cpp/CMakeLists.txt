# include_directories(.)
message (STATUS "TEST FLD GOOGLEMOCK_INCLUDE_DIR  ${GOOGLEMOCK_INCLUDE_DIR} ")
include_directories( BEFORE SYSTEM
					# Work arorund for  #include <bfd.h> on windows
					# D:/Qt/Qt5.8.0/Tools/mingw530_32/include
					# ${CORE_MODULE_ROOT_CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/
					"H:/levitics/Arkhe/amd64-windows-Debug/Windows-GNU_GCC_5.3.0-AMD64-Debug/include"
					"H:/levitics/Arkhe/amd64-windows-Debug/Windows-GNU_GCC_5.3.0-AMD64-Debug/include"
					# ${GOOGLEMOCK_INCLUDE_DIR}
					# ${GOOGLEMOCK_GTEST_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}-osgiTest.bin
# add_library(${PROJECT_NAME}-osgiTest.bin
	arkhe/osgi/osgiTest.cpp
	arkhe/osgi/core/BackTraceTest.cpp
	arkhe/osgi/core/CallbackTest.cpp
)

target_link_libraries( ${PROJECT_NAME}-osgiTest.bin Qt5::Core ${PROJECT_NAME}-osgi ${GOOGLEMOCK_LIBRARIES} ${GOOGLETEST_LIBRARY} )
