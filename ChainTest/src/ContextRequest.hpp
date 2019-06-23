/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ContextRequest.hpp
 * @brief    网络请求上下文信息
 * @author   Bwar
 * @date:    2019年6月22日
 * @note     
 * Modify history:
 ******************************************************************************/
#ifndef HELLO_CONTEXTREQUEST_HPP_
#define HELLO_CONTEXTREQUEST_HPP_

#include "actor/context/HttpContext.hpp"
#include "util/json/CJsonObject.hpp"

namespace hello
{

class ContextRequest: public neb::HttpContext,
    public neb::DynamicCreator<ContextRequest,
              std::shared_ptr<neb::SocketChannel>, HttpMsg>
{
public:
    ContextRequest(
            std::shared_ptr<neb::SocketChannel> pChannel,
            const HttpMsg& oHttpMsg);
    virtual ~ContextRequest();

    void AddToResult(const std::string& strActorName, uint32 uiActorSeq);

    std::string ChainBlockString();

private:
    neb::CJsonObject m_oJsonResult;
};

} /* namespace hello */

#endif /* HELLO_CONTEXTREQUEST_HPP_ */
