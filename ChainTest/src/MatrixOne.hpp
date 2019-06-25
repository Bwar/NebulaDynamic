/*******************************************************************************
 * Project:  Nebula
 * @file     MatrixOne.hpp
 * @brief
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef MATRIXONE_HPP_
#define MATRIXONE_HPP_

#include <actor/matrix/Matrix.hpp>

namespace hello
{

class MatrixOne: public neb::Matrix, public neb::DynamicCreator<MatrixOne>
{
public:
    MatrixOne();
    virtual ~MatrixOne();

    virtual neb::E_CMD_STATUS Submit();
};

} /* namespace hello*/

#endif /* MATRIXONE_HPP_ */

