/*******************************************************************************
 * Project:  Nebula
 * @file     StepTestSsl.hpp
 * @brief    Http服务的异步步骤基类
 * @author   Bwar
 * @date:    2016年8月13日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef STEPTESTSSL_HPP_
#define STEPTESTSSL_HPP_

#include <actor/step/HttpStep.hpp>

namespace logic
{

class StepTestSsl: public neb::HttpStep, public neb::DynamicCreator<StepTestSsl, std::string>
{
public:
    StepTestSsl(const std::string& strContent);
    virtual ~StepTestSsl();

    virtual neb::E_CMD_STATUS Emit(int iErrno = neb::ERR_OK, const std::string& strErrMsg = "", void* data = NULL);
    virtual neb::E_CMD_STATUS Callback(
                    std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
                    const HttpMsg& oHttpMsg,
                    void* data = NULL);
    virtual neb::E_CMD_STATUS Timeout();

protected:
    std::string m_strContent;
    int32 m_iCmd;
    uint32 m_uiSeq;
};

} /* namespace neb */

#endif /* SRC_ACTOR_STEP_HTTPSTEP_HPP_ */
