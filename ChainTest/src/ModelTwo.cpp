/*******************************************************************************
 * Project:  Nebula
 * @file     ModelTwo.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "ModelTwo.hpp"
#include "ContextRequest.hpp"

namespace hello
{

ModelTwo::ModelTwo()
{
}

ModelTwo::~ModelTwo()
{
}

neb::E_CMD_STATUS ModelTwo::Submit()
{
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    pSharedContext->AddToResult(GetActorName(), GetSequence(), "is a model.");
    return(neb::CMD_STATUS_COMPLETED);
}

} /* namespace hello */

