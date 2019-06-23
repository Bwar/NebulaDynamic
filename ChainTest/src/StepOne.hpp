/*******************************************************************************
 * Project:  Nebula
 * @file     StepOne.hpp
 * @brief    
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef STEPONE_HPP_
#define STEPONE_HPP_

#include <actor/step/HttpStep.hpp>

namespace logic
{

class StepOne: public neb::PbStep, public neb::DynamicCreator<StepOne, std::string>
{
public:
    StepOne();
    virtual ~StepOne();

    virtual neb::E_CMD_STATUS Emit(int iErrno = neb::ERR_OK, const std::string& strErrMsg = "", void* data = NULL);
    virtual neb::E_CMD_STATUS Callback(
                    std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
                    const HttpMsg& oHttpMsg,
                    void* data = NULL);
    virtual neb::E_CMD_STATUS Timeout();
};

} /* namespace neb */

#endif /* STEPONE_HPP_ */
