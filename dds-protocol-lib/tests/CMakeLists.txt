# Copyright 2014 GSI, Inc. All rights reserved.
#
#
project( dds-protocol-lib-tests )


include_directories(
	${Boost_INCLUDE_DIRS}
)

##################################################################
# Test_ProtocolMessage
##################################################################

set( CLNT_SOURCE_FILES
	./Test_ProtocolMessage.cpp
)

add_executable(dds-protocol-lib-ProtocolMessage-tests ${CLNT_SOURCE_FILES})

target_link_libraries (
	dds-protocol-lib-ProtocolMessage-tests
	dds-protocol-lib
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_include_directories(dds-protocol-lib-ProtocolMessage-tests
    PRIVATE
        $<TARGET_PROPERTY:dds-protocol-lib,INTERFACE_INCLUDE_DIRECTORIES>
	PRIVATE
		$<TARGET_PROPERTY:dds-user-defaults-lib,INTERFACE_INCLUDE_DIRECTORIES>
)

install(TARGETS dds-protocol-lib-ProtocolMessage-tests DESTINATION tests)

