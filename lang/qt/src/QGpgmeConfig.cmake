include(CMakeFindDependencyMacro)
find_dependency(Qt5Core 5.12.0)
find_dependency(Gpgmepp 1.11.1)

include("${CMAKE_CURRENT_LIST_DIR}/QGpgmeTargets.cmake")
