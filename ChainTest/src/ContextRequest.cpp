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

void ContextRequest::AddToResult(const std::string& strActorName, uint32 uiActorSeq)
{
    neb::CJsonObject oNewBlock;
    oNewBlock.Add(strActorName, uiActorSeq);
    m_oJsonResult.Add(oNewBlock);
}

std::string ContextRequest::ChainBlockString()
{
    return(m_oJsonResult.ToFormatedString());
}

} /* namespace hello */
