/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ModuleDataLand.hpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/

#ifndef COLLECT_MODULEDATALAND_HPP
#define COLLECT_MODULEDATALAND_HPP

#include <string>
#include <map>
#include <fstream>
#include <util/json/CJsonObject.hpp>
#include <actor/cmd/Module.hpp>

namespace collect
{

class ModuleDataLand : public neb::Module, public neb::DynamicCreator<ModuleDataLand, std::string>
{
public:
    ModuleDataLand(const std::string& strPath);
    virtual ~ModuleDataLand();

    virtual bool Init();

    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel, 
                    const HttpMsg& oHttpMsg);

protected:
    bool OpenDataFile();
    bool WriteData(neb::CJsonObject& oJson);

private:
    int32 m_iLogMaxFileSize;
    std::string m_strLogDataPath;
    std::string m_strLogFileName;
    std::string m_strLogDataFile;
    std::ofstream m_ofs;
};

}

#endif // COLLECT_MODULEDATALAND_HPP