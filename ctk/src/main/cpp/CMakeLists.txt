# add_subdirectory (arkhe/osgi/core/workflow)

include_directories(.)
# Work arorund for  #include <bfd.h> on windows
# include_directories(D:/Qt/Qt5.8.0/Tools/mingw530_32/include
# )
add_library(${PROJECT_NAME}-ctk
	arkhe/ctk/ScopedQPointer.cpp
)

target_link_libraries( ${PROJECT_NAME}-ctk Qt5::Core )