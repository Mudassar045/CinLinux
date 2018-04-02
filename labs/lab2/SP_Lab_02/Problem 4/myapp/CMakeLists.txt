cmake_minimum_required (VERSION 3.2.2)
project(ex1_cmakeproject)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCES src/driver.c)
add_executable(myexe ${PROJECT_SOURCE_DIR}/${SOURCES})

target_link_libraries(myexe libmyfuncs.so libmyfuncs.a)

install(TARGETS myexe DESTINATION /usr/bin)
install(FILES man/myexe.3 DESTINATION /usr/share/man/man3)


include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Mudassar Ali")
include(CPack)
