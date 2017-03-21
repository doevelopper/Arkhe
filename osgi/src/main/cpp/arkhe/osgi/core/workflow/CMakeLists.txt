# include_directories(.)
add_library(${PROJECT_NAME}-workflow
	WorkflowInterstepTransition.cpp
	# WorkflowInterstepTransitionEvent.cpp
)

# target_include_directories( ${PROJECT_NAME}-workflow PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries( ${PROJECT_NAME}-workflow Qt5::Core)