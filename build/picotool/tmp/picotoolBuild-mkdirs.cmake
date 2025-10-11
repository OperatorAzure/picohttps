# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/aydil/Documents/picohttps/build/_deps/picotool-src"
  "C:/Users/aydil/Documents/picohttps/build/_deps/picotool-build"
  "C:/Users/aydil/Documents/picohttps/build/_deps"
  "C:/Users/aydil/Documents/picohttps/build/picotool/tmp"
  "C:/Users/aydil/Documents/picohttps/build/picotool/src/picotoolBuild-stamp"
  "C:/Users/aydil/Documents/picohttps/build/picotool/src"
  "C:/Users/aydil/Documents/picohttps/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/aydil/Documents/picohttps/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/aydil/Documents/picohttps/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
