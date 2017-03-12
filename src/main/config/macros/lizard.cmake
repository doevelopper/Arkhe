#Cyclomatic Complexity Analyzer 
set(LIZARD_OPTIONS  -l cpp 
                    --verbose
#                    --warnings_only
                    --working_threads ${Ncpu} 
                    --CCN 15 
                    --arguments 1 
                    --modified 
                    --sort nloc #cyclomatic_complexity, token_count, p#arameter_count
#                    --Threshold nloc=5
#                    cyclomatic_complexity --warnings_only
#                    --input_file=/home/happyman/NetBeansProjects/didactics/build/Debug/qa/cppcheck/SphynxCore/files.txt
#                    --html
)

if(ENABLE_CYCLOMATIC_COMPLEXITY)
    find_package(PythonInterp)

    if(PYTHONINTERP_FOUND)
        set(LIZARD_SCRIPT "${PROJECT_SOURCE_DIR}/src/main/resources/scripts/lizard-1.12.7/lizard.py")
        mark_as_advanced(LIZARD_SCRIPT LIZARD_OPTIONS)

        if(ENABLE_CYCLOMATIC_COMPLEXITY)
            set(RUN_LIZARD true)
        else(ENABLE_CYCLOMATIC_COMPLEXITY)
            message(STATUS "ENABLE_CYCLOMATIC_COMPLEXITY was not given. Skipped running cpplint")
            set(RUN_LIZARD false)
        endif(ENABLE_CYCLOMATIC_COMPLEXITY)

    else(PYTHONINTERP_FOUND)
        set(RUN_LIZARD OFF)
        message(STATUS "python executable not found. Skipped running Cyclomatic Complexity Analyzer ")
    endif(PYTHONINTERP_FOUND)

else(ENABLE_CYCLOMATIC_COMPLEXITY)
    message(STATUS "Skipped running CYCLOMATIC")
endif(ENABLE_CYCLOMATIC_COMPLEXITY)


function(CYCLOMATIC_COMPLEXITY_ANALYZER target_name bin_folder)

    if(RUN_LIZARD)
        set(WORKING_DIR "${TARGET_BUILD_DIRECTORY}/qa/lizard/${target_name}")
        if(NOT TARGET ${target_name}-cyclomatic)
            file(MAKE_DIRECTORY ${bin_folder})
            file(MAKE_DIRECTORY ${WORKING_DIR})
            add_custom_target(${target_name}-cyclomatic 
                         COMMAND ${PYTHON_EXECUTABLE} ${LIZARD_SCRIPT} ${LIZARD_OPTIONS}  ${bin_folder} --xml # > ${WORKING_DIR}/lizard.xml#--html #${WORKING_DIR}
#                         COMMAND ${PYTHON_EXECUTABLE} ${LIZARD_SCRIPT}   ${bin_folder}
#                         WORKING_DIRECTORY ${bin_folder}
                         WORKING_DIRECTORY ${WORKING_DIR}
                         COMMENT "[CYCLOMATIC-Target:${target_name}] ${bin_folder}"
            )
        endif()

    else(RUN_LIZARD)
        add_custom_target(${target_name}-cyclomatic COMMAND ${CMAKE_COMMAND} -E echo "NO Cyclomatic Complexity Analysis")
    endif(RUN_LIZARD)

    if(NOT TARGET cyclomatic)
        add_custom_target(cyclomatic
            COMMENT "Cyclomatic Complexity Analyzer."
        )
    endif()
    add_dependencies(cyclomatic ${target_name}-cyclomatic)
endfunction(CYCLOMATIC_COMPLEXITY_ANALYZER)