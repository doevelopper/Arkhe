#source: http://kollide.net:8060/browse/Amarok-git/cmake/modules/FindGooglemock.cmake
# - Find Googlemock
# Find the google mock includes and the google mock libraries
# This module defines
# GOOGLEMOCK_INCLUDE_DIRS, root google mock & gtest include dirs
# GOOGLEMOCK_LIBRARY, the path to Google Mock library
# GOOGLEMOCK_LIBRARIES, the path to Google Mock and Google Test library
# GOOGLEMOCK_FOUND, whether Google Mock was found
#	   ~/usr/include
#	   /opt/local/include
#	   /usr/include
#	   /usr/local/include
#	   $ENV{GMOCK_ROOT}/include
# 		/opt/local/bin
# 		/usr/bin

# update this to include gtest too?
# for now the fallback seems to work on ubuntu
find_program(GMOCK-CONFIG_EXECUTABLE 
            NAMES gmock-config 
            PATHS ${TARGET_BUILD_DIRECTORY}/bin
)

if(GMOCK-CONFIG_EXECUTABLE)
	exec_program(${GMOCK-CONFIG_EXECUTABLE} ARGS --includedir OUTPUT_VARIABLE GOOGLEMOCK_INCLUDE_DIR)
	exec_program(${GMOCK-CONFIG_EXECUTABLE} ARGS --ldflags OUTPUT_VARIABLE GOOGLEMOCK_LDFLAGS)
	exec_program(${GMOCK-CONFIG_EXECUTABLE} ARGS --libs OUTPUT_VARIABLE GOOGLEMOCK_libs_tmp)
	set(GOOGLEMOCK_LIBRARIES ${GOOGLEMOCK_LDFLAGS} ${GOOGLEMOCK_libs_tmp})

	if(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARIES)
		set(GOOGLEMOCK_FOUND TRUE)
		message(STATUS "Found libgmock: ${GOOGLEMOCK_INCLUDE_DIR}, ${GOOGLEMOCK_LIBRARIES}")
	else(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARIES)
		set(GOOGLEMOCK_FOUND FALSE)
		if (GOOGLEMOCK_FIND_REQUIRED)
			message(FATAL_ERROR "Could NOT find required package Googlemock")
		endif(GOOGLEMOCK_FIND_REQUIRED)
	endif(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARIES)

else(GMOCK-CONFIG_EXECUTABLE)

	find_path(GOOGLEMOCK_INCLUDE_DIR 
		NAMES 	gmock/gmock.h
		HINTS 	${TARGET_BUILD_DIRECTORY}/include
		# ${TARGET_BUILD_DIRECTORY}
	)

	find_path(GOOGLEMOCK_GTEST_INCLUDE_DIR 
				NAMES gtest/gtest.h
				HINTS ${TARGET_BUILD_DIRECTORY}/include
	)

	find_library( GOOGLEMOCK_LIBRARY 
                NAMES gmock gmock.d
				PATHS ${TARGET_BUILD_DIRECTORY}/lib
	)

	find_library( GOOGLETEST_LIBRARY 
                NAMES gtest gtest.d
				PATHS ${TARGET_BUILD_DIRECTORY}/lib
	)

message( STATUS "TARGET_BUILD_DIRECTORY ${TARGET_BUILD_DIRECTORY}")
message( STATUS "GOOGLEMOCK_INCLUDE_DIR ${GOOGLEMOCK_INCLUDE_DIR}")
message( STATUS "GOOGLEMOCK_GTEST_INCLUDE_DIR ${GOOGLEMOCK_GTEST_INCLUDE_DIR}")
message( STATUS "GOOGLEMOCK_LIBRARY ${GOOGLEMOCK_LIBRARY}")
message( STATUS "GOOGLETEST_LIBRARY ${GOOGLETEST_LIBRARY}")

	# if( GMOCK_CMAKE_DEBUG )
		# message( STATUS "GMOK ${TARGET_BUILD_DIRECTORY}")
		# message( STATUS "GMOK ${TARGET_BUILD_DIRECTORY}/lib")
		# message("gmock root:  $ENV{GMOCK_ROOT}")
		# message("gmock inc: ${GOOGLEMOCK_INCLUDE_DIR}")
		# message("gmock lib: ${GOOGLEMOCK_LIBRARY}")
		# message("gmocks gtest include dir: ${GOOGLEMOCK_GTEST_INCLUDE_DIR}")
	# endif(GMOCK_CMAKE_DEBUG)

	# if(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARY AND GOOGLEMOCK_GTEST_INCLUDE_DIR GOOGLETEST_LIBRARY)
	   # set(GOOGLEMOCK_FOUND TRUE)
	   # set(GOOGLEMOCK_LIBRARIES ${GOOGLEMOCK_LIBRARY})
	   # set(GOOGLEMOCK_INCLUDE_DIRS ${GOOGLEMOCK_INCLUDE_DIR} ${GOOGLEMOCK_GTEST_INCLUDE_DIR})
##	    message(STATUS "Found libgmock: ${GOOGLEMOCK_INCLUDE_DIR}, ${GOOGLEMOCK_LIBRARIES}")
	# else(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARY  AND GOOGLEMOCK_GTEST_INCLUDE_DIR)
	   # set(GOOGLEMOCK_FOUND FALSE)
	   # if (GOOGLEMOCK_FIND_REQUIRED)
		  # message(FATAL_ERROR "Could NOT find required package Googlemock")
	   # endif(GOOGLEMOCK_FIND_REQUIRED)
	# endif(GOOGLEMOCK_INCLUDE_DIR AND GOOGLEMOCK_LIBRARY  AND GOOGLEMOCK_GTEST_INCLUDE_DIR)

endif(GMOCK-CONFIG_EXECUTABLE)


#find_library(GMOCK_LIBRARY            gmock)
#find_library(GMOCK_LIBRARY_DEBUG      gmockd)
#find_library(GMOCK_MAIN_LIBRARY       gmock_main)
#find_library(GMOCK_MAIN_LIBRARY_DEBUG gmock_maind)

mark_as_advanced(GOOGLEMOCK_INCLUDE_DIR GOOGLEMOCK_LIBRARIES GOOGLEMOCK_GTEST_INCLUDE_DIR GOOGLETEST_LIBRARY )

#message("gmock inc: ${GOOGLEMOCK_INCLUDE_DIR}")
#message("gmock lib: ${GOOGLEMOCK_LIBRARY}")