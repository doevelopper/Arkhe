# Locate the xenomai framework, to make user space program.
# 
# Defines the following variables
#
# XENOMAI_FOUND - Found the Xenomai framework
# XENOMAI_CONFIG_EXECUTABLE - path to the xeno-config executable
# XENOMAI_AVAILABLE_SKINS - A list of the available skins of xenomai
# XENOMAI_VERSION_STRING - 
#
# A set of the following variables, where YYY is a skin value
#
# XENOMAI_YYY_INCLUDE_DIRS
# XENOMAI_YYY_LIBRARIES
# XENOMAI_YYY_CFLAGS
# XENOMAI_DEFINITIONS
# XENOMAI_YYY_CFLAGS_OTHER
# XENOMAI_YYY_LDFLAGS
# XENOMAI_YYY_LDFLAGS_OTHER
# XENOMAI_YYY_FOUND - Xenomai skin YYY is found

# ==============================================================================
# Copyright (c) 2011 Alexandre Tuleu <alexandre.tuleu.2005@polytechnique.org>
#
# Distributed under the GPL v3 license
#
#

include(FindPackageMessage)
include(FindPackageHandleStandardArgs)

SET(XENOMAI_SEARCH_PATH /usr/include/xenomai /usr/local/xenomai /usr/xenomai /usr)
find_program(XENOMAI_CONFIG_EXECUTABLE xeno-config 
            PATHS /usr/bin /usr/local/bin 
                  /usr/local/xenomai/bin /usr/xenomai/bin)

if(XENOMAI_CONFIG_EXECUTABLE)
    set(XENOMAI_FIND_QUIETLY TRUE)
endif(XENOMAI_CONFIG_EXECUTABLE)

macro(get_xeno_conf OUT_VAR skin_name wanted)
    execute_process(
                    COMMAND ${XENOMAI_CONFIG_EXECUTABLE}
	                    --skin ${skin_name}
	                    ${wanted}
	            OUTPUT_VARIABLE ${OUT_VAR}
	            OUTPUT_STRIP_TRAILING_WHITESPACE)
endmacro(get_xeno_conf)

macro(set_std_var_from_cflags_ldflags skin cflags_var ldflags_var)
    string(TOUPPER ${skin} SKIN)
    string(TOLOWER ${skin} skin)
    set(PREFIX_NAME XENOMAI_${SKIN})
    string(REGEX MATCHALL "[-][I]([^ ;])+" ${PREFIX_NAME}_INCLUDE_DIRS "${${cflags_var}}")
    string(REGEX REPLACE "[-][I]" ";" ${PREFIX_NAME}_INCLUDE_DIRS "${${PREFIX_NAME}_INCLUDE_DIRS}")
	# remove directories definition from the cflags
    string(REGEX REPLACE "[-][I]([^ ;])+" "" ${cflags_var}_OTHER "${${cflags_var}}")

	#get the libraries declaration
    string(REGEX MATCHALL "[-][l]([^ ;])+" ${PREFIX_NAME}_LIBRARIES_TMP "${${ldflags_var}}")
    string(REGEX REPLACE "[-][l]" ";" ${PREFIX_NAME}_LIBRARIES_TMP "${${PREFIX_NAME}_LIBRARIES_TMP}")
	# remove all libraries definition from the command line
    string(REGEX REPLACE "[-][lL]([^ ;])+" "" ${ldflags_var}_OTHER "${${ldflags_var}}")

	#get the full path to the libraries
    foreach(skinlib ${${PREFIX_NAME}_LIBRARIES_TMP})
    	find_library(TMP_${PREFIX_NAME}_${skinlib} ${skinlib} PATHS ${XENOMAI_PREFIX}/lib)

    	if(TMP_${PREFIX_NAME}_${skinlib})
            list(APPEND ${PREFIX_NAME}_LIBRARIES ${TMP_${PREFIX_NAME}_${skinlib}})
	endif(TMP_${PREFIX_NAME}_${skinlib})
    endforeach(skinlib ${${PREFIX_NAME}_LIBRARIES_TMP})

    string(REGEX REPLACE "[ ][ ]+" " "  ${ldflags_var}_OTHER "${${ldflags_var}_OTHER}")
    string(REGEX REPLACE "[ ][ ]+" " "  ${cflags_var}_OTHER "${${cflags_var}_OTHER}")

    string(REGEX REPLACE "(^ $)|(^ )|( $)" ""  ${ldflags_var}_OTHER "${${ldflags_var}_OTHER}")
    string(REGEX REPLACE "(^ $)|(^ )|( $)" ""  ${cflags_var}_OTHER "${${cflags_var}_OTHER}")

    set(XENOMAI_${SKIN}_DEFINITIONS ${${cflags_var}_OTHER})

    if(NOT XENOMAI_FIND_QUIETLY)
    	message(STATUS "Found xenomai skin ${skin} : 
                --   Include=[${${PREFIX_NAME}_INCLUDE_DIRS}]
                --   Library=[${${PREFIX_NAME}_LIBRARIES}]
                --   cflags=[${${PREFIX_NAME}_CFLAGS}]
                --   ldflags=[${${PREFIX_NAME}_LDFLAGS}]
                --   definitions=[${XENOMAI_${SKIN}_DEFINITIONS}]")
    endif(NOT XENOMAI_FIND_QUIETLY)

    set(XENOMAI_${SKIN}_FOUND 1)

    mark_as_advanced(XENOMAI_${SKIN}_LDFLAGS
                     XENOMAI_${SKIN}_CFLAGS
                     XENOMAI_${SKIN}_LDFLAGS_OTHER
	             XENOMAI_${SKIN}_CFLAGS_OTHER
	             XENOMAI_${SKIN}_LIBRARIES
	             XENOMAI_${SKIN}_DEFINITIONS
	             XENOMAI_${SKIN}_INCLUDE_DIRS
                     XENOMAI_${SKIN}_FOUND)
endmacro(set_std_var_from_cflags_ldflags)

macro(make_standards_variables_for_skin skin)
	# get the upper name
    string(TOUPPER ${skin} SKIN)
	# get the CFlags
    get_xeno_conf(XENOMAI_${SKIN}_CFLAGS ${skin} --cflags)
    get_xeno_conf(XENOMAI_${SKIN}_LDFLAGS ${skin} --ldflags)
    set_std_var_from_cflags_ldflags(${skin} XENOMAI_${SKIN}_CFLAGS XENOMAI_${SKIN}_LDFLAGS)
endmacro(make_standards_variables_for_skin)

if(XENOMAI_CONFIG_EXECUTABLE)
    execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --prefix 
                    OUTPUT_VARIABLE XENOMAI_PREFIX
	            OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --version
	            OUTPUT_VARIABLE XENOMAI_VERSION_STRING
	            ERROR_VARIABLE XENOMAI_VERSION_STRING)
    execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --help
                    OUTPUT_VARIABLE XENOMAI_HELP_MESSAGE
	            ERROR_VARIABLE XENOMAI_HELP_MESSAGE)

    if(${XENOMAI_VERSION_STRING} VERSION_GREATER "2.5")
	string(REGEX MATCH "[-][-]skin [^\n]*" XENOMAI_AVAILABLE_SKINS ${XENOMAI_HELP_MESSAGE})
	string(REGEX REPLACE "[-][-]skin ([^\n]*)" "\\1" XENOMAI_AVAILABLE_SKINS ${XENOMAI_AVAILABLE_SKINS})
	string(REGEX REPLACE "[|]" ";" XENOMAI_AVAILABLE_SKINS ${XENOMAI_AVAILABLE_SKINS})

	foreach(skin ${XENOMAI_AVAILABLE_SKINS})
            make_standards_variables_for_skin(${skin})
	endforeach(skin ${XENOMAI_AVAILABLE_SKINS})

    else(${XENOMAI_VERSION_STRING} VERSION_GREATER "2.5")
        set(XENOMAI_AVAILABLE_SKINS "native" "posix")
        execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --xeno-cflags
                        OUTPUT_VARIABLE XENOMAI_NATIVE_CFLAGS
		        OUTPUT_STRIP_TRAILING_WHITESPACE)

        execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --xeno-ldflags
		        OUTPUT_VARIABLE XENOMAI_NATIVE_LDFLAGS
		        OUTPUT_STRIP_TRAILING_WHITESPACE)

        set(XENOMAI_NATIVE_LDFLAGS "${XENOMAI_NATIVE_LDFLAGS} -lnative")

#		execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --posix-cflags
#		              OUTPUT_VARIABLE XENOMAI_POSIX_CFLAGS
#		              OUTPUT_STRIP_TRAILING_WHITESPACE)
#		execute_process(COMMAND ${XENOMAI_CONFIG_EXECUTABLE} --posix-ldflags
#		              OUTPUT_VARIABLE XENOMAI_POSIX_LDFLAGS
#		              OUTPUT_STRIP_TRAILING_WHITESPACE)

        set_std_var_from_cflags_ldflags(native XENOMAI_NATIVE_CFLAGS XENOMAI_NATIVE_LDFLAGS)
	#set_std_var_from_cflags_ldflags(posix XENOMAI_POSIX_CFLAGS XENOMAI_POSIX_LDFLAGS)
    endif(${XENOMAI_VERSION_STRING} VERSION_GREATER "2.5")
endif(XENOMAI_CONFIG_EXECUTABLE)

if(XENOMAI_FIND_VERSION)
    if(XENOMAI_FIND_VERSION_EXACT AND NOT XENOMAI_VERSION_STRING EQUAL XENOMAI_FIND_VERSION)
        set(XENOMAI_VERSION_STRING )
    endif(XENOMAI_FIND_VERSION_EXACT AND NOT XENOMAI_VERSION_STRING EQUAL XENOMAI_FIND_VERSION)  
    if(XENOMAI_FIND_VERSION VERSION_GREATER XENOMAI_VERSION_STRING)
        set(XENOMAI_VERSION_STRING )
    endif(XENOMAI_FIND_VERSION VERSION_GREATER XENOMAI_VERSION_STRING)
endif(XENOMAI_FIND_VERSION)

find_package_handle_standard_args(Xenomai DEFAULT_MSG
                                 XENOMAI_CONFIG_EXECUTABLE 
                                 XENOMAI_NATIVE_LIBRARIES 
                                 XENOMAI_NATIVE_INCLUDE_DIRS)
if(XENOMAI_FOUND)
	mark_as_advanced(XENOMAI_CONFIG_EXECUTABLE XENOMAI_VERSION_STRING)
endif(XENOMAI_FOUND)


#if( UNIX_BLABLABLABLA )
#
#    # Get hint from environment variable (if any)
#    if(NOT $ENV{XENOMAI_ROOT_DIR} STREQUAL "")
#        set(XENOMAI_ROOT_DIR $ENV{XENOMAI_ROOT_DIR} CACHE PATH "Xenomai base directory location (optional, used for nonstandard installation paths)" FORCE)
#        mark_as_advanced(XENOMAI_ROOT_DIR)
#    endif()
#    # set the search paths
#
#    FIND_PATH(XENOMAI_INCLUDE_DIR_DIR xeno_config.h ${XENOMAI_SEARCH_PATH} 
#              PATH_SUFFIXES xenomai 
#              include xenomai/include 
#              include/xenomai)
#    #set( Xenomai_SEARCH_PATH /usr/local/xenomai /usr/xenomai /usr/include/xenomai $ENV{XENOMAI_ROOT_DIR})
#
#    find_package_handle_standard_args(Xenomai DEFAULT_MSG
#        Xenomai_ROOT_DIR
#        Xenomai_INCLUDE_DIR
#        Xenomai_LIBRARY_XENOMAI
#        Xenomai_LIBRARY_RTDK)
#  
#    set(Xenomai_FOUND ${XENOMAI_FOUND}) # Set appropriately cased variable
#    if(Xenomai_LIBRARY_XENOMAI AND Xenomai_LIBRARY_NATIVE) 
#        message(STATUS "Xenomai Native skin found")
#        set(Xenomai_NATIVE_FOUND True)
#    endif()
#  
#    if(Xenomai_LIBRARY_XENOMAI AND Xenomai_LIBRARY_PTHREAD_RT) 
#        message(STATUS "Xenomai POSIX skin found")
#        set(Xenomai_POSIX_FOUND True)
#    endif()
#  
#    if(Xenomai_LIBRARY_XENOMAI AND Xenomai_LIBRARY_RTDM) 
#        message(STATUS "Xenomai RTDM skin found")
#        set(Xenomai_RTDM_FOUND True)
#    endif()
#endif(UNIX)
