# Install script for directory: C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/nau/contrib/glbinding-master/source/glbinding

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/Debug/glbindingd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/Release/glbinding.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/MinSizeRel/glbinding.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/RelWithDebInfo/glbinding.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/nau/contrib/glbinding-master/source/glbinding/include/glbinding")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/include/glbinding")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/glbinding/glbinding-export.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/glbinding/glbinding-export.cmake"
         "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/glbinding/glbinding-export-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/glbinding/glbinding-export.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/glbinding" TYPE FILE FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/glbinding" TYPE FILE FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/glbinding" TYPE FILE FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/glbinding" TYPE FILE FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake/glbinding" TYPE FILE FILES "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/source/glbinding/CMakeFiles/Export/cmake/glbinding/glbinding-export-release.cmake")
  endif()
endif()

