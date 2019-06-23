/*******************************************************************************
 * Project:  Logic
 * @file     CmdTestSsl.hpp
 * @brief 
 * @author   bwar
 * @date:    Feb 21, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef CMDTESTSSL_HPP_
#define CMDTESTSSL_HPP_

#include <actor/cmd/Cmd.hpp>

namespace logic
{

class CmdTestSsl: public neb::Cmd, public neb::DynamicCreator<CmdTestSsl, int32>
{
public:
    CmdTestSsl(int32 iCmd);
    virtual ~CmdTestSsl();

    virtual bool Init();
    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel, 
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);
};

} /* namespace logic */

#endif /* CMDTESTSSL_HPP_ */
