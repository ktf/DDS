// Copyright 2014 GSI, Inc. All rights reserved.
//
//
//

#ifndef __DDS__InfoChannel__
#define __DDS__InfoChannel__
// DDS
#include "ConnectionImpl.h"

namespace dds
{
    class CInfoChannel : public CConnectionImpl<CInfoChannel>
    {
        CInfoChannel(boost::asio::io_service& _service)
            : CConnectionImpl<CInfoChannel>(_service)
            , m_isHandShakeOK(false)
        {
        }

        REGISTER_DEFAULT_ON_DISCONNECT_CALLBACKS

      public:
        BEGIN_MSG_MAP(CInfoChannel)
        MESSAGE_HANDLER(cmdREPLY_HANDSHAKE_OK, on_cmdREPLY_HANDSHAKE_OK)
        MESSAGE_HANDLER(cmdSIMPLE_MSG, on_cmdSIMPLE_MSG)
        MESSAGE_HANDLER(cmdREPLY_PID, on_cmdREPLY_PID)
        END_MSG_MAP()

      private:
        // Message Handlers
        int on_cmdREPLY_HANDSHAKE_OK(const CProtocolMessage& _msg);
        int on_cmdSIMPLE_MSG(const CProtocolMessage& _msg);
        int on_cmdREPLY_PID(const CProtocolMessage& _msg);

        // On connection handles
        void onConnected()
        {
        }
        void onFailedToConnect()
        {
            LOG(MiscCommon::log_stdout) << "Failed to connect to commander server.";
        }

      private:
        bool m_isHandShakeOK;
        std::string m_sTopoFile;
    };
}

#endif