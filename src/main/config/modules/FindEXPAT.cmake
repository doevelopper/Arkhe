find_library(EXPAT_LIBRARY 
            NAMES expat expat.d libexpat libexpat.d
            HINTS ${TARGET_BUILD_DIRECTORY}/lib
            NO_DEFAULT_PATH
)
find_program(EXPAT_EXECUTABLE 
            NAMES xmlwf
            PATHS /usr/local/apr/bin  
            ${TARGET_BUILD_DIRECTORY}/bin
)
#get_filename_component(EXPAT_LIBRARY_DIRS ${EXPAT_LIBRARY} PATH)
#get_filename_component(EXPAT_BINARY_PATH ${EXPAT_EXECUTABLE} PATH)

#message(STATUS "EXPAT_LIBRARY ${EXPAT_LIBRARY}")
#message(STATUS "EXPAT_EXECUTABLE ${EXPAT_EXECUTABLE}")
#message(STATUS "EXPAT_LIBRARY_DIRS ${EXPAT_LIBRARY_DIRS}")
#message(STATUS "EXPAT_BINARY_PATH ${EXPAT_BINARY_PATH}")
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Expat DEFAULT_MSG EXPAT_LIBRARY) # EXPAT_EXECUTABLE)
mark_as_advanced(EXPAT_LIBRARY EXPAT_EXECUTABLE)

