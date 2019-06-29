/*******************************************************************************
 * Project:  Nebula
 * @file     ModelOne.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "ModelOne.hpp"
#include "ContextRequest.hpp"

namespace hello
{

ModelOne::ModelOne()
{
}

ModelOne::~ModelOne()
{
}

neb::E_CMD_STATUS ModelOne::Submit()
{
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    pSharedContext->AddToResult(GetActorName(), GetSequence(), "is a model.");
    return(neb::CMD_STATUS_COMPLETED);
}

} /* namespace hello */

