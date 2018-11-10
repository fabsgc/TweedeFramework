function (strip_symbols targetName outputFilename)
    if (UNIX)
        if (CMAKE_BUILD_TYPE STREQUAL Release)
            set(fileToStrip $<TARGET_FILE:${targetName}>)

            # macOS
            if (CMAKE_SYSTEM_NAME STREQUAL Darwin)
                set(symbolsFile ${fileToStrip}.dwarf)

                add_custom_command (
                    TARGET ${targetName}
                    POST_BUILD
                    VERBATIM 
                    COMMAND ${DSYMUTIL_TOOL} --flat --minimize ${fileToStrip}
                    COMMAND ${STRIP_TOOL} -u -r ${fileToStrip}
                    COMMENT Stripping symbols from ${fileToStrip} into file ${symbolsFile}
                )
            
            # Linux
            else ()
                set(symbolsFile ${fileToStrip}.dbg)

                add_custom_command (
                    TARGET ${targetName}
                    POST_BUILD
                    VERBATIM 
                    COMMAND ${OBJCOPY_TOOL} --only-keep-debug ${fileToStrip} ${symbolsFile}
                    COMMAND ${OBJCOPY_TOOL} --strip-unneeded ${fileToStrip}
                    COMMAND ${OBJCOPY_TOOL} --add-gnu-debuglink=${symbolsFile} ${fileToStrip}
                    COMMENT Stripping symbols from ${fileToStrip} into file ${symbolsFile}
                )
            endif (CMAKE_SYSTEM_NAME STREQUAL Darwin)

            set (${outputFilename} ${symbolsFile} PARENT_SCOPE)
        endif ()
    endif ()
endfunction ()

function (install_tef_target targetName)
    strip_symbols (${targetName} symbolsFile)
    
    install(
        TARGETS ${targetName}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )       
    
    if (MSVC)
        install(
            FILES $<TARGET_PDB_FILE:${targetName}> 
            DESTINATION bin 
            OPTIONAL
        )
    else ()
        install(
            FILES ${symbolsFile} 
            DESTINATION lib
            OPTIONAL)
    endif ()
endfunction()

function (target_link_framework TARGET FRAMEWORK)
    find_library (FM_${FRAMEWORK} ${FRAMEWORK})

    if (NOT FM_${FRAMEWORK})
        message (FATAL_ERROR "Cannot find ${FRAMEWORK} framework.")
    endif ()

    target_link_libraries (${TARGET} PRIVATE ${FM_${FRAMEWORK}})
    mark_as_advanced (FM_${FRAMEWORK})
endfunction ()