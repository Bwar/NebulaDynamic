/*******************************************************************************
 * Project:  Nebula
 * @file     StepOne.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepOne.hpp"

namespace logic 
{

StepOne::StepOne()
{
}

StepOne::~StepOne()
{
}

neb::E_CMD_STATUS StepOne::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    std::unordered_map<std::string, std::string> mapHeaders;
    mapHeaders.insert(std::make_pair("Content-Type", "application/json"));
    //HttpPost("https://analysis.jjcclife.com/collect", m_strContent, mapHeaders);
    HttpPost("https://192.168.157.166:16003/hello", m_strContent, mapHeaders);
    return(neb::CMD_STATUS_RUNNING);
}

neb::E_CMD_STATUS StepOne::Callback(
                    std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
                    const HttpMsg& oHttpMsg,
                    void* data)
{
    MsgBody oOutMsgBody;
    //oOutMsgBody.set_data("Nebula: hello!\n");
    oOutMsgBody.set_data(oHttpMsg.body());
    SendTo(GetContext()->GetChannel(), GetContext()->GetCmd() + 1, GetContext()->GetSeq(), oOutMsgBody);
    return(neb::CMD_STATUS_COMPLETED);
}

neb::E_CMD_STATUS StepOne::Timeout()
{
    LOG4_ERROR("Timeout");
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace neb */
