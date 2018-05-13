/*******************************************************************************
 * Project:  Logic
 * @file     CmdHello.cpp
 * @brief 
 * @author   bwar
 * @date:    Feb 21, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#include "CmdHello.hpp"

namespace logic
{

CmdHello::CmdHello(int32 iCmd)
    : neb::Cmd(iCmd)
{
}

CmdHello::~CmdHello()
{
}

bool CmdHello::Init()
{
    return(true);
}

bool CmdHello::AnyMessage(
                std::shared_ptr<neb::SocketChannel> pChannel, 
                const MsgHead& oMsgHead, const MsgBody& oMsgBody)
{
    MsgBody oOutMsgBody;
    oOutMsgBody.set_data("Nebula: hello!\n");
    SendTo(pChannel, oMsgHead.cmd() + 1, oMsgHead.seq(), oOutMsgBody);
    return(true);
}

} /* namespace logic */
