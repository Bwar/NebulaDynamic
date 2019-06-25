/*******************************************************************************
 * Project:  Nebula
 * @file     MatrixOne.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "MatrixOne.hpp"
#include "ContextRequest.hpp"

namespace hello
{

MatrixOne::MatrixOne()
{
}

MatrixOne::~MatrixOne()
{
}

neb::E_CMD_STATUS MatrixOne::Submit()
{
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    pSharedContext->AddToResult(GetActorName(), GetSequence(), "is a matrix.");
    return(neb::CMD_STATUS_COMPLETED);
}

} /* namespace hello */

