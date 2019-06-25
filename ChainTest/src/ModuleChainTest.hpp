/*******************************************************************************
 * Project:  NebulaDynamic
 * @file     ModuleChainTest.hpp
 * @brief    数据采集落地
 * @author   Bwar
 * @date:    2018年6月30日
 * @note     
 * Modify history:
 ******************************************************************************/

#ifndef HELLO_MODULECHAINTEST_HPP
#define HELLO_MODULECHAINTEST_HPP

#include <string>
#include <map>
#include <fstream>
#include <util/json/CJsonObject.hpp>
#include <actor/cmd/Module.hpp>

namespace hello
{

class ModuleChainTest : public neb::Module, public neb::DynamicCreator<ModuleChainTest, std::string>
{
public:
    ModuleChainTest(const std::string& strPath);
    virtual ~ModuleChainTest();

    virtual bool Init();

    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel,
                    const HttpMsg& oHttpMsg);
};

}

#endif // HELLO_MODULECHAINTEST_HPP
