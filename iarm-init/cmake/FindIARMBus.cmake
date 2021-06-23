find_package(PkgConfig)

find_library(IARMBUS_LIBRARIES NAMES IARMBus)
find_path(IARMBUS_INCLUDE_DIRS NAMES libIARM.h PATH_SUFFIXES rdk/iarmbus)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IARMBUS DEFAULT_MSG IARMBUS_INCLUDE_DIRS IARMBUS_LIBRARIES)

mark_as_advanced(
    IARMBUS_FOUND
    IARMBUS_INCLUDE_DIRS
    IARMBUS_LIBRARIES
    IARMBUS_LIBRARY_DIRS
    IARMBUS_FLAGS)
