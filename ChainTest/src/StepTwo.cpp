/*******************************************************************************
 * Project:  Nebula
 * @file     StepTwo.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepTwo.hpp"
#include "ContextRequest.hpp"

namespace hello
{

StepTwo::StepTwo()
{
}

StepTwo::~StepTwo()
{
}

neb::E_CMD_STATUS StepTwo::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    MsgBody oMsgBody;
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    uint32 uiCmd = 65531;
    oMsgBody.set_data(pSharedContext->GetHttpMsg().body());
    if (SendRoundRobin("LOGIC", uiCmd, GetSequence(), oMsgBody))
    {
        return(neb::CMD_STATUS_RUNNING);
    }
    return(neb::CMD_STATUS_FAULT);
}

neb::E_CMD_STATUS StepTwo::Callback(
        std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
        const MsgHead& oInMsgHead,
        const MsgBody& oInMsgBody,
        void* data)
{
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    pSharedContext->AddToResult(GetActorName(), GetSequence(), oInMsgBody.data());
    return(neb::CMD_STATUS_COMPLETED);
}

neb::E_CMD_STATUS StepTwo::Timeout()
{
    LOG4_ERROR("Timeout");
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace hello */

