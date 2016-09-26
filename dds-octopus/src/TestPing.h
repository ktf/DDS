// Copyright 2016 GSI, Inc. All rights reserved.
//
//
//
#ifndef DDS_OCTOPUS_TESTPING_H
#define DDS_OCTOPUS_TESTPING_H

#include "OctopusTestImpl.h"

namespace dds
{
    namespace dds_octopus
    {
        //
        // Send "get_ping" -->
        // Receive "ping" <---
        //
        class CTestPing : public COctopusTestImpl<CTestPing>
        {
          public:
            CTestPing(const SOptions_t& _options);

          public:
            BEGIN_OCTOPUS_MSG_MAP("Ping")
            OCTOPUS_MSG_HANDLER(onPingCmd, SOctopusProtocol_Ping)
            END_OCTOPUS_MSG_MAP

          public:
            void _init();
            void onPingCmd(const SOctopusProtocol_Ping& _ping, uint64_t _senderId);

          private:
            size_t m_nConfirmedPings;
        };
    }
}
#endif
