/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ModuleDataLand.cpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/
#include <sys/stat.h>       //need int mkdir(const char *pathname, mode_t mode)
#include <sys/types.h>      //need int mkdir(const char *pathname, mode_t mode)
#include <chrono>
#include <iomanip>
#include <sstream>
#include "ModuleDataLand.hpp"

namespace collect
{

ModuleDataLand::ModuleDataLand(const std::string& strPath)
    : neb::Module(strPath)
{
}

ModuleDataLand::~ModuleDataLand()
{
    if (m_ofs.is_open())
    {
        m_ofs.flush();
        m_ofs.close();
    }
}

bool ModuleDataLand::Init()
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


bool ModuleDataLand::AnyMessage(
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
    if (!oJson.Parse(oHttpMsg.body()))
    {
        LOG4_ERROR("error json format!");
        oHttpResponseMsg.set_body("{\"code\": 10001, \"msg\": \"error json format!\"");
        SendTo(pChannel, oHttpResponseMsg);
        return(false);
    }
    else
    {
        oHttpResponseMsg.set_body("{\"code\": 0, \"msg\": \"ok\"");
        SendTo(pChannel, oHttpResponseMsg);
    }
    return(WriteData(oJson));
}

bool ModuleDataLand::WriteData(neb::CJsonObject& oJson)
{
    LOG4_TRACE("%s", oJson.ToString().c_str());
    if (!OpenDataFile())
    {
        return(false);
    }
    
    for (int i = 0; i < oJson.GetArraySize(); ++i)
    {
        m_ofs << oJson[i]("event_id") << "|" << oJson[i]("event_type") << "|" << oJson[i]("time") << "|"
            << oJson[i]("page") << "|" << oJson[i]("referer") << "|" << oJson[i]("session_id") << "|" 
            << oJson[i]("user_id") << "|" << oJson[i]("device_id") << "|" << oJson[i]("plat") << "|"
            << oJson[i]("explorer") << std::endl;
    }
    return(true);
}

bool ModuleDataLand::OpenDataFile()
{
    if (m_ofs.is_open())
    {
        if (m_ofs.tellp() < m_iLogMaxFileSize)
        {
            return(true);
        }
        m_ofs.flush();
        m_ofs.close();
    }
    auto time_now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(time_now);
    std::ostringstream osDataFile;
    osDataFile << m_strLogDataPath << "/" << m_strLogFileName << "." << std::put_time(std::localtime(&t), "%Y-%m-%d");
    m_strLogDataFile = osDataFile.str();
    for (int i = 1; ; ++i)
    {
        if (access(m_strLogDataFile.c_str(), F_OK) != 0)
        {
            break;
        }
        m_strLogDataFile = osDataFile.str() + std::string(".") + std::to_string(i);
    }
    m_ofs.open(m_strLogDataFile, std::ios::app);
    if (!m_ofs.good())
    {
        LOG4_ERROR("failed to open file \"%s\"", m_strLogDataFile.c_str());
        return(false);
    }
    LOG4_TRACE("open file \"%s\" successful.", m_strLogDataFile.c_str());
    return(true);
}

} /* namespace collect */
