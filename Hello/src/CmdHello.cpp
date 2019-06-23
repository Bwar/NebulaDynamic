/*******************************************************************************
 * Project:  Logic
 * @file     CmdHello.cpp
 * @brief 
 * @author   bwar
 * @date:    Feb 21, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#include <fstream>
#include <sstream>
#include "util/json/CJsonObject.hpp"
#include "official.pb.h"
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
    offical_message_send oMsg;
    neb::CJsonObject oJson;
    std::ifstream fin("/home/bwar/factory/cplus/test/proto2.x/test/offical_msg.data");
    std::stringstream ssContent;
    ssContent << fin.rdbuf();
    oMsg.ParseFromString(ssContent.str());
    fin.close();
    oOutMsgBody.set_data("Nebula: hello!\n");
    oOutMsgBody.set_data(oMsg.DebugString());
    SendTo(pChannel, oMsgHead.cmd() + 1, oMsgHead.seq(), oOutMsgBody);
    return(true);
}

} /* namespace logic */
