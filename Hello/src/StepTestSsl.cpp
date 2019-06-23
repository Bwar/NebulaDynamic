/*******************************************************************************
 * Project:  Nebula
 * @file     StepTestSsl.cpp
 * @brief 
 * @author   Bwar
 * @date:    2016年8月13日
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepTestSsl.hpp"

namespace logic 
{

StepTestSsl::StepTestSsl(const std::string& strContent)
    : m_strContent(strContent)
{
}

StepTestSsl::~StepTestSsl()
{
}

neb::E_CMD_STATUS StepTestSsl::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    std::unordered_map<std::string, std::string> mapHeaders;
    mapHeaders.insert(std::make_pair("Content-Type", "application/json"));
    //HttpPost("https://analysis.jjcclife.com/collect", m_strContent, mapHeaders);
    HttpPost("https://192.168.157.166:16003/hello", m_strContent, mapHeaders);
    return(neb::CMD_STATUS_RUNNING);
}

neb::E_CMD_STATUS StepTestSsl::Callback(
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

neb::E_CMD_STATUS StepTestSsl::Timeout()
{
    LOG4_ERROR("Timeout");
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace neb */
