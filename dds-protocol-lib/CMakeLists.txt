# Copyright 2014 GSI, Inc. All rights reserved.
#
#
project( dds-protocol-lib )

#
# Where to lookup modules
#
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

#
# Source files
#
set( SOURCE_FILES
	./src/ProtocolCommands.cpp
	./src/ProtocolMessage.cpp
)

set( SRC_HDRS
	./src/ProtocolCommands.h
	./src/ProtocolMessage.h
	./src/ConnectionImpl.h
)

include_directories(
	${PROJECT_SOURCE_DIR}
	${MiscCommon_LOCATION}
	${Boost_INCLUDE_DIRS}
)

#
# lib
#
if (CMAKE_GENERATOR STREQUAL "Xcode")
	add_library(dds-protocol-lib SHARED ${SOURCE_FILES} ${SRC_HDRS})
else (CMAKE_GENERATOR STREQUAL "Xcode")
	add_library(dds-protocol-lib SHARED ${SOURCE_FILES})
endif (CMAKE_GENERATOR STREQUAL "Xcode")

target_link_libraries (
	dds-protocol-lib
	${Boost_SYSTEM_LIBRARY}
)

# API headers
target_include_directories(dds-protocol-lib INTERFACE ${dds-protocol-lib_SOURCE_DIR}/src)

install(TARGETS dds-protocol-lib DESTINATION lib)


#
# Unit tests
#
if (BUILD_TESTS)
	message (STATUS "Build dds-protocol-lib tests - YES")
	add_subdirectory ( ${dds-protocol-lib_SOURCE_DIR}/tests ) 
else (BUILD_TESTS)
	message (STATUS "Build dds-protocol-lib tests - NO")
endif (BUILD_TESTS)
