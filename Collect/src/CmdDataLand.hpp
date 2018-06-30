/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     CmdDataLand.hpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/

#ifndef COLLECT_CMDDATALAND_HPP
#define COLLECT_CMDDATALAND_HPP

#include <string>
#include <map>
#include <fstream>
#include <util/json/CJsonObject.hpp>
#include <actor/cmd/Cmd.hpp>

namespace collect
{

class CmdDataLand : public neb::Cmd, public neb::DynamicCreator<CmdDataLand, int32>
{
public:
    CmdDataLand(int32 iCmd);
    virtual ~CmdDataLand();

    virtual bool Init();

    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel, 
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);

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

#endif // COLLECT_CMDDATALAND_HPP