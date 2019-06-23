/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ModuleChainTest.cpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/
#include <sstream>
#include "ModuleChainTest.hpp"

namespace collect
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
    neb::CJsonObject oJson = GetCustomConf();
    oJson["collect"].Get("data_path", m_strLogDataPath);
    oJson["collect"].Get("data_file_name", m_strLogFileName);
    oJson["collect"].Get("data_file_size", m_iLogMaxFileSize);
    if (m_strLogDataPath[0] != '/')
    {
        m_strLogDataPath = GetWorkPath() + std::string("/") + m_strLogDataPath;
    }
    if (access(m_strLogDataPath.c_str(), W_OK) != 0)
    {
        if (mkdir(m_strLogDataPath.c_str(), S_IRWXU) != 0)
        {
            LOG4_ERROR("create dir %s error!", m_strLogDataPath.c_str());
            return(false);
        }
    }
    LOG4_DEBUG("collect_data_path = %s", m_strLogDataPath.c_str());

    return(OpenDataFile());
}


bool ModuleChainTest::AnyMessage(
                std::shared_ptr<neb::SocketChannel> pChannel, 
                const HttpMsg& oHttpMsg)
{
    HttpMsg oHttpResponseMsg;
    oHttpResponseMsg.set_type(HTTP_RESPONSE);
    oHttpResponseMsg.set_status_code(200);
    oHttpResponseMsg.set_http_major(oHttpMsg.http_major());
    oHttpResponseMsg.set_http_minor(oHttpMsg.http_minor());
    neb::CJsonObject oJson;
    LOG4_TRACE("%s", oHttpMsg.body().c_str());

    neb::Context pSharedContext = MakeSharedContext(
            "hello::ContextRequest", oHttpMsg);
    SetContext(pSharedContext);  // set Context to ModuleHelloChain, then MakeSharedChain() will set Context to that Chain.
    neb::Chain pSharedChain = MakeSharedChain("neb::Chain", "chain_1"); //"chain_1" comes from request param.
    if (null_ptr != pSharedChain)
    {
        pSharedChain->NextBlock();
    }

    if (oJson.Parse(oHttpMsg.body()) && oJson.ToString().length() > 2) // there is a bug in cJSON_Parse(), we have to add "&& oJson.ToString().length() > 2" in order to avoid this bug.
    {
        oHttpResponseMsg.set_body("{\"code\": 0, \"msg\": \"ok\"}");
        SendTo(pChannel, oHttpResponseMsg);
    }
    else
    {
        LOG4_ERROR("error json format!");
        oHttpResponseMsg.set_body("{\"code\": 10001, \"msg\": \"error json format!\"}");
        SendTo(pChannel, oHttpResponseMsg);
        return(false);
    }
    return(WriteData(oJson));
}

} /* namespace collect */
