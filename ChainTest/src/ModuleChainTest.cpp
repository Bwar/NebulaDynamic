/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ModuleChainTest.cpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/
#include "ModuleChainTest.hpp"
#include <sstream>
#include <util/json/CJsonObject.hpp>
#include <actor/chain/Chain.hpp>
#include <actor/context/Context.hpp>

namespace hello
{

ModuleChainTest::ModuleChainTest(const std::string& strPath)
    : neb::Module(strPath)
{
}

ModuleChainTest::~ModuleChainTest()
{
}

bool ModuleChainTest::Init()
{
    return(true);
}


bool ModuleChainTest::AnyMessage(
                std::shared_ptr<neb::SocketChannel> pChannel,
                const HttpMsg& oHttpMsg)
{
    LOG4_TRACE("%s", oHttpMsg.body().c_str());
    neb::CJsonObject oJson;
    if (!oJson.Parse(oHttpMsg.body()))
    {
        LOG4_ERROR("failed to parse json!");
        return(false);
    }

    std::shared_ptr<neb::Context> pSharedContext = MakeSharedContext(
            "hello::ContextRequest", pChannel, oHttpMsg);
    SetContext(pSharedContext);  // set Context to ModuleHelloChain, then MakeSharedChain() will set Context to that Chain.
    std::shared_ptr<neb::Chain> pSharedChain = MakeSharedChain("neb::Chain", oJson("chain_flag"), (ev_tstamp)60.0); //"chain_1" comes from request param.
    if (nullptr != pSharedChain)
    {
        pSharedChain->Next();
        return(true);
    }
    return(false);
}

} /* namespace hello */

