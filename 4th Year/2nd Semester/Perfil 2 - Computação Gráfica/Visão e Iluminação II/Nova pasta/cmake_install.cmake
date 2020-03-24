# Install script for directory: C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/nau

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/glbinding-master/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/tinyxml/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/assimp3.3.1/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/contrib/freeglut-3.0.0/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/nau/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/plugins/passDepthMap/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/plugins/bullet/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/plugins/physx/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/nauGlut/cmake_install.cmake")
  include("C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/composerImGui/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/diogo/Desktop/MIEI/4th Year/2nd Semester/Perfil 2 - Computação Gráfica/Visão e Iluminação II/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
