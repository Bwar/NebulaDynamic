/*******************************************************************************
 * Project:  Logic
 * @file     CmdHello.hpp
 * @brief 
 * @author   bwar
 * @date:    Feb 21, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDHELLO_CMDHELLO_HPP_
#define SRC_CMDHELLO_CMDHELLO_HPP_

#include <actor/cmd/Cmd.hpp>

namespace logic
{

class CmdHello: public neb::Cmd, public neb::DynamicCreator<CmdHello, int32>
{
public:
    CmdHello(int32 iCmd);
    virtual ~CmdHello();

    virtual bool Init();
    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel, 
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);
};

} /* namespace logic */

#endif /* SRC_CMDHELLO_CMDHELLO_HPP_ */
