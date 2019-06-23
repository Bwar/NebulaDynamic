/*******************************************************************************
 * Project:  Logic
 * @file     CmdTestSsl.cpp
 * @brief 
 * @author   bwar
 * @date:    Feb 21, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#include "CmdTestSsl.hpp"
#include "StepTestSsl.hpp"

namespace logic
{

CmdTestSsl::CmdTestSsl(int32 iCmd)
    : neb::Cmd(iCmd)
{
}

CmdTestSsl::~CmdTestSsl()
{
}

bool CmdTestSsl::Init()
{
    return(true);
}

bool CmdTestSsl::AnyMessage(
                std::shared_ptr<neb::SocketChannel> pChannel, 
                const MsgHead& oMsgHead, const MsgBody& oMsgBody)
{
    /*
    MsgBody oOutMsgBody;
    oOutMsgBody.set_data("Nebula: hello!\n");
    SendTo(pChannel, oMsgHead.cmd() + 1, oMsgHead.seq(), oOutMsgBody);
    */
    LOG4_TRACE("%s", oMsgBody.data().c_str());
    std::stringstream ssSessionId;
    ssSessionId << "neb::Context:" << GetSequence();
    std::shared_ptr<neb::Context> pCurrentContext = std::dynamic_pointer_cast<neb::Context>(MakeSharedSession(
        "neb::Context", ssSessionId.str(), pChannel, oMsgHead.cmd(), oMsgHead.seq(), oMsgBody));
    if (nullptr == pCurrentContext)
    {
        return(false);
    }

    std::shared_ptr<neb::Step> pStep = MakeSharedStep("logic::StepTestSsl",
            pChannel, oMsgBody.data(), (int32)oMsgHead.cmd(), (uint32)oMsgHead.seq());
    pStep->Emit();

    return(true);
}

} /* namespace logic */
