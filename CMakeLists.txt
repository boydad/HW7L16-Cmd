cmake_minimum_required(VERSION 3.5)

project(HW7L16-Cmd)
set(EXECUTE_FILE_NAME bulk)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GetGitRevisionDescription)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${EXECUTE_FILE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${version_file})

set_target_properties(${EXECUTE_FILE_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_FLAGS "-Wpedantic -Wall -Wextra"
)


install(TARGETS ${EXECUTE_FILE_NAME} DESTINATION bin)

set(CPACK_PACKAGE_NAME ${EXECUTE_FILE_NAME})
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION ${VERSION_SHORT})
set(CPACK_PACKAGE_CONTACT xxx@xxx.xx)

include(CPack)
