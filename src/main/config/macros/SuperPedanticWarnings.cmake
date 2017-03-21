# Module to enable hyper pedantic warning
# if defines the function :
#   super_pedantic_warning() - tests and enable super pedantic warning

#if (CMAKE_SYSTEM_NAME STREQUAL GNU)
#    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pthread")
#    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -pthread")
#endif()


include(CMakeParseArguments)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-Wall" CXX_COMPILER_HAS_WALL)
CHECK_CXX_COMPILER_FLAG("-Wextra" CXX_COMPILER_WALL_HAS_WEXTRA)
CHECK_CXX_COMPILER_FLAG("-fvisibility=hidden" CXX_COMPILER_HAS_FVISIBILITY)
CHECK_CXX_COMPILER_FLAG("-fvisibility-inlines-hidden" CXX_COMPILER_HAS_FVISIBILITY_INLINE)

if(COMPILER_SUPPORTS_CXX17)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 or later support. Please use a different C++ compiler.")
endif()


# find a way to use "add_compile_options()"

# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libstdc++") ;# Fails on Windows

set(COMMON_CMAKE_CXX_FLAGS 
    # "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wfatal-errors"
    "${CMAKE_CXX_FLAGS} -Wfatal-errors"
)

set(PARANO_CMAKE_CXX_FLAGS 
    "-Werror -pedantic" 
)

set(GCC_COMMON_WARNING_FLAGS 
    "${COMMON_CMAKE_CXX_FLAGS} "
    # "-Wcast-align -Wchar-subscripts"
    # "-Wformat-security -Wno-long-long"
    # "-Wdelete-non-virtual-dtor"
    # "-Winit-self"
	###
    # "-Wpointer-arith -Wundef"
    # "-Wzero-as-null-pointer-constant" 
    # "-W -Wshadow -Wunused-variable  -Wunused-parameter" 
    # "-Wunused-function -Wunused -Wno-system-headers" 
    # "-Wno-deprecated -Woverloaded-virtual -Wwrite-strings"
    # "-Wredundant-decls -Wconversion -Wswitch-enum -Wold-style-cast"
    "-Wunreachable-code"
)
string(REPLACE ";" " " GCC_COMMON_WARNING_FLAGS "${GCC_COMMON_WARNING_FLAGS}")

## turn on some more warnings
# SET(CMAKE_C_FLAGS_DEBUG "${COMMON_CMAKE_CXX_FLAGS}")
# SET(CMAKE_CXX_FLAGS_DEBUG "${COMMON_CMAKE_CXX_FLAGS}")
# SET(CMAKE_C_FLAGS_RELEASE "${COMMON_CMAKE_CXX_FLAGS}")
# SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_CMAKE_CXX_FLAGS}")

## support building for coverage analysis
set(COVERAGE_FLAGS "-g -O0 --coverage -Wall") # -ftime-report -fmem-report -fvar-tracking -fvar-tracking-assignments
set(COVERAGE_LINK_FLAGS "--coverage") #-lgcov -Q ftime-report -fmem-report

# SET(CMAKE_C_FLAGS_COVERAGE          "${CMAKE_C_FLAGS_DEBUG} ${COVERAGE_FLAGS}")
# SET(CMAKE_CXX_FLAGS_COVERAGE        "${CMAKE_CXX_FLAGS_DEBUG} ${COVERAGE_FLAGS}")
# SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${COVERAGE_LINK_FLAGS}")

 
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMMON_WARNING_FLAGS} -Wmissing-format-attribute")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=implicit-function-declaration") # Make some warnings errors
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMMON_WARNING_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")    # Make some warnings errors
endif()

# set(CMAKE_CXX_FLAGS   "${COMMON_CMAKE_CXX_FLAGS} 
                    # -fno-strict-aliasing 
                   ## -std=c++14 -O3 
                    # -Wno-missing-braces -Wconversion -Wsign-conversion 
                    # -Wctor-dtor-privacy -Wshadow -Wnon-virtual-dtor 
                    # -Wold-style-cast -Wcast-align -Woverloaded-virtual
                    # -fdiagnostics-show-option
                    # -Wchar-subscripts
                    # -Winit-self
                    # -Wswitch-enum
                    # -Wstrict-aliasing=3
                    # -Wstrict-overflow=5
                    # -Wundef
                    # -Wno-endif-labels
                    # -Wshadow
                    # -Wno-system-headers
                    # -Wno-builtin-macro-redefined
                    # -Wmissing-declarations
                    # -Wsign-conversion
                    # -Wcast-qual
                    # -Waggregate-return
                    # -Wdisabled-optimization 
                   ## -Wformat=2 
                    # -Wformat-nonliteral -Wformat-security -Wformat-y2k
                    # -Wimport  -Winit-self  -Winline -Winvalid-pch -Wlong-long 
                    # -Wmissing-field-initializers -Wmissing-format-attribute
                    # -Wpointer-arith -Wredundant-decls -Wshadow
                    # -Wswitch-default -Wswitch-enum
                    # -Wunused-parameter -Wvariadic-macros -Wwrite-strings
                    # -Wstack-protector -Wunused
# "
# )

# set(HAHAHA_CXX_FLAGS "${COMMON_CMAKE_CXX_FLAGS}
    # -Wno-error=shadow
    # -Wno-error=long-long
    # -Wno-error=aggregate-return
    # -Wno-error=unused-variable
    # -Wno-error=unused-parameter
    # -Wno-error=deprecated-declarations
    # -Wno-error=missing-include-dirs
    # -Wno-error=packed
    # -Wno-error=switch-default
    # -Wno-error=float-equal
    # -Wno-error=invalid-pch
    # -Wno-error=cast-qual
    # -Wno-error=conversion
    # -Wno-error=switch-enum
    # -Wno-error=redundant-decls
    # -Wno-error=stack-protector
    # -Wno-error=extra
    # -Wno-error=unused-result
    # -Wno-error=sign-compare
    # -Wno-error=address
    # -Wno-error=cast-qual
    # -Wno-error=missing-field-initializers
    # -Wno-error=write-strings
    # -Wno-error=format-nonliteral
    # -Wno-error=sign-conversion
    # -Wno-error=suggest-attribute=format
    # -Wno-error=suggest-attribute=noreturn
    # -Wno-aggregate-return
    # -Wno-long-long
    # -Wno-shadow
    # -Wno-strict-aliasing
    # -Wno-error=inline
    # -Wno-error=maybe-uninitialized
    # -Wno-error=unused-but-set-variable
    # -Wno-error=unused-local-typedefs"
# )
# add_definitions(-Wno-error=float-conversion)




