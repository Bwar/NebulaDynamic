/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ContextRequest.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "ContextRequest.hpp"
#include <sstream>

namespace hello
{

ContextRequest::ContextRequest(
        std::shared_ptr<neb::SocketChannel> pChannel, const HttpMsg& oHttpMsg)
    : neb::HttpContext(pChannel, oHttpMsg)
{
    m_oJsonResult.Parse("[]");
}

ContextRequest::~ContextRequest()
{
}

void ContextRequest::Done()
{
    Response(m_oJsonResult.ToFormattedString());
}

void ContextRequest::AddToResult(const std::string& strActorName,
        uint32 uiActorSeq, const std::string& strCallbackData)
{
    neb::CJsonObject oNewBlock;
    std::ostringstream oss;
    oss << strActorName << ":" << uiActorSeq;
    oNewBlock.Add(oss.str(), strCallbackData);
    m_oJsonResult.Add(oNewBlock);
}

} /* namespace hello */
