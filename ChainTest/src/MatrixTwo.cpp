/*******************************************************************************
 * Project:  Nebula
 * @file     MatrixTwo.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#include "MatrixTwo.hpp"
#include "ContextRequest.hpp"

namespace hello
{

MatrixTwo::MatrixTwo()
{
}

MatrixTwo::~MatrixTwo()
{
}

neb::E_CMD_STATUS MatrixTwo::Submit()
{
    std::shared_ptr<ContextRequest> pSharedContext
        = std::dynamic_pointer_cast<ContextRequest>(GetContext());
    pSharedContext->AddToResult(GetActorName(), GetSequence(), "is a matrix.");
    return(neb::CMD_STATUS_COMPLETED);
}

} /* namespace hello */

