set (QT_MOC moc)
set (QT_RCC rcc)
set (QT_UIC uic.exe)

set (QT_LRELEASE lrelease)
set (QT_LUPDATE lupdate)
set (QT_QSCXMLC qscxmlc) #Compiles the given input.scxml file to a header and a cpp file.

# for Windows operating system in general
if(WIN32)
    if(MSVS OR MSYS OR MINGW)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_DIR} )
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/Qt/Qt5.8.0/5.8/mingw53_32" ) # remember to add D:\Qt\Qt5.8.0\5.8\mingw53_32\bin to %PATH%
        SET(CMAKE_FIND_ROOT_PATH "D:/Qt/Qt5.8.0/5.8/mingw53_32" "D:/Qt/Qt5.8.0/Tools/mingw530_32" "D:/Qt/Qt5.8.0/Tools/mingw530_32/include")

        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
        # set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
        set(CMAKE_INCLUDE_CURRENT_DIR ON )
        set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON )
        set(CMAKE_AUTOMOC ON )
        set(CMAKE_AUTOMOC_MOC_OPTIONS "")
        set(CMAKE_AUTOMOC_RELAXED_MODE "")
        SET(CMAKE_AUTOUIC ON) 
        SET(CMAKE_AUTOUIC_OPTIONS "") 
        SET(CMAKE_AUTORCC ON) 
        SET(CMAKE_AUTORCC_OPTIONS "")
        set(CMAKE_MAKE_PROGRAM mingw32-make.exe)
        # set(CMAKE_C_COMPILER i686-w64-mingw32-gcc.exe)
        # set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++.exe)
    endif()
endif()

# for MacOS X
if(APPLE)
    
endif()

# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
    set(CMAKE_INCLUDE_CURRENT_DIR ON )
    # set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON )
    set(CMAKE_AUTOMOC ON )
    set(CMAKE_AUTOMOC_MOC_OPTIONS "")
    set(CMAKE_AUTOMOC_RELAXED_MODE "")
    set(CMAKE_AUTOUIC ON) 
    set(CMAKE_AUTOUIC_OPTIONS "") 
    set(CMAKE_AUTORCC ON) 
    set(CMAKE_AUTORCC_OPTIONS "") 
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
endif()


find_package( Qt5Core    REQUIRED )
find_package( Qt5Widgets REQUIRED )

