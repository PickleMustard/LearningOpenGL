########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND glew_COMPONENT_NAMES GLEW::glew_s)
list(REMOVE_DUPLICATES glew_COMPONENT_NAMES)
if(DEFINED glew_FIND_DEPENDENCY_NAMES)
  list(APPEND glew_FIND_DEPENDENCY_NAMES mesa-glu opengl_system)
  list(REMOVE_DUPLICATES glew_FIND_DEPENDENCY_NAMES)
else()
  set(glew_FIND_DEPENDENCY_NAMES mesa-glu opengl_system)
endif()
set(mesa-glu_FIND_MODE "NO_MODULE")
set(opengl_system_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(glew_PACKAGE_FOLDER_RELEASE "/home/picklemustard/.conan2/p/b/glew1ae525c7e68e1/p")
set(glew_BUILD_MODULES_PATHS_RELEASE )


set(glew_INCLUDE_DIRS_RELEASE "${glew_PACKAGE_FOLDER_RELEASE}/include")
set(glew_RES_DIRS_RELEASE )
set(glew_DEFINITIONS_RELEASE )
set(glew_SHARED_LINK_FLAGS_RELEASE )
set(glew_EXE_LINK_FLAGS_RELEASE )
set(glew_OBJECTS_RELEASE )
set(glew_COMPILE_DEFINITIONS_RELEASE )
set(glew_COMPILE_OPTIONS_C_RELEASE )
set(glew_COMPILE_OPTIONS_CXX_RELEASE )
set(glew_LIB_DIRS_RELEASE "${glew_PACKAGE_FOLDER_RELEASE}/lib")
set(glew_BIN_DIRS_RELEASE )
set(glew_LIBRARY_TYPE_RELEASE STATIC)
set(glew_IS_HOST_WINDOWS_RELEASE 0)
set(glew_LIBS_RELEASE GLEW)
set(glew_SYSTEM_LIBS_RELEASE )
set(glew_FRAMEWORK_DIRS_RELEASE )
set(glew_FRAMEWORKS_RELEASE )
set(glew_BUILD_DIRS_RELEASE )
set(glew_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(glew_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${glew_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${glew_COMPILE_OPTIONS_C_RELEASE}>")
set(glew_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${glew_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${glew_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${glew_EXE_LINK_FLAGS_RELEASE}>")


set(glew_COMPONENTS_RELEASE GLEW::glew_s)
########### COMPONENT GLEW::glew_s VARIABLES ############################################

set(glew_GLEW_glew_s_INCLUDE_DIRS_RELEASE "${glew_PACKAGE_FOLDER_RELEASE}/include")
set(glew_GLEW_glew_s_LIB_DIRS_RELEASE "${glew_PACKAGE_FOLDER_RELEASE}/lib")
set(glew_GLEW_glew_s_BIN_DIRS_RELEASE )
set(glew_GLEW_glew_s_LIBRARY_TYPE_RELEASE STATIC)
set(glew_GLEW_glew_s_IS_HOST_WINDOWS_RELEASE 0)
set(glew_GLEW_glew_s_RES_DIRS_RELEASE )
set(glew_GLEW_glew_s_DEFINITIONS_RELEASE )
set(glew_GLEW_glew_s_OBJECTS_RELEASE )
set(glew_GLEW_glew_s_COMPILE_DEFINITIONS_RELEASE )
set(glew_GLEW_glew_s_COMPILE_OPTIONS_C_RELEASE "")
set(glew_GLEW_glew_s_COMPILE_OPTIONS_CXX_RELEASE "")
set(glew_GLEW_glew_s_LIBS_RELEASE GLEW)
set(glew_GLEW_glew_s_SYSTEM_LIBS_RELEASE )
set(glew_GLEW_glew_s_FRAMEWORK_DIRS_RELEASE )
set(glew_GLEW_glew_s_FRAMEWORKS_RELEASE )
set(glew_GLEW_glew_s_DEPENDENCIES_RELEASE opengl::opengl mesa-glu::mesa-glu)
set(glew_GLEW_glew_s_SHARED_LINK_FLAGS_RELEASE )
set(glew_GLEW_glew_s_EXE_LINK_FLAGS_RELEASE )
set(glew_GLEW_glew_s_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(glew_GLEW_glew_s_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${glew_GLEW_glew_s_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${glew_GLEW_glew_s_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${glew_GLEW_glew_s_EXE_LINK_FLAGS_RELEASE}>
)
set(glew_GLEW_glew_s_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${glew_GLEW_glew_s_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${glew_GLEW_glew_s_COMPILE_OPTIONS_C_RELEASE}>")