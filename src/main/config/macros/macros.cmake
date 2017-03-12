function(targetName flag)
    if(${flag})
        if(NOT TARGET targetName)
            add_custom_target(targetName
                COMMENT "Running targetName ."
            )
        endif()
    endif(${flag})
endfunction()


