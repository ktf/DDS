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
	./src/BasicCmd.cpp
	./src/AgentsInfoCmd.cpp
	./src/SimpleMsgCmd.cpp
	./src/UUIDCmd.cpp
	./src/AssignUserTaskCmd.cpp
	./src/BinaryAttachmentCmd.cpp
	./src/HostInfoCmd.cpp
	./src/SubmitCmd.cpp
	./src/VersionCmd.cpp
	./src/BinaryAttachmentReceivedCmd.cpp
	./src/BinaryAttachmentStartCmd.cpp
	./src/UpdateKeyCmd.cpp
	./src/DeleteKeyCmd.cpp
	./src/ProgressCmd.cpp
	./src/UserTaskDoneCmd.cpp
	./src/GetPropValuesCmd.cpp
	./src/SetTopologyCmd.cpp
)

set( SRC_HDRS
	./src/ProtocolCommands.h
	./src/ProtocolMessage.h
	./src/BaseChannelImpl.h
	./src/ClientChannelImpl.h
	./src/ServerChannelImpl.h
	./src/ChannelEventsImpl.h
	./src/CommandAttachmentImpl.h
	./src/ConnectionManagerImpl.h
	./src/BasicCmd.h
	./src/AgentsInfoCmd.h
	./src/SimpleMsgCmd.h
	./src/UUIDCmd.h
	./src/AssignUserTaskCmd.h
	./src/BinaryAttachmentCmd.h
	./src/HostInfoCmd.h
	./src/SubmitCmd.h
	./src/VersionCmd.h
	./src/BinaryAttachmentReceivedCmd.h
	./src/BinaryAttachmentStartCmd.h
	./src/UpdateKeyCmd.h
	./src/DeleteKeyCmd.h
	./src/ProgressCmd.h
	./src/UserTaskDoneCmd.h
	./src/GetPropValuesCmd.h
	./src/SetTopologyCmd.h
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

target_include_directories(dds-protocol-lib
	PRIVATE
		$<TARGET_PROPERTY:dds-user-defaults-lib,INTERFACE_INCLUDE_DIRECTORIES>
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

