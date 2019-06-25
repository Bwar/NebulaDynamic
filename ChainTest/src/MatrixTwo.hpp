/*******************************************************************************
 * Project:  Nebula
 * @file     MatrixTwo.hpp
 * @brief
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef MATRIXTWO_HPP_
#define MATRIXTWO_HPP_

#include <actor/matrix/Matrix.hpp>

namespace hello
{

class MatrixTwo: public neb::Matrix, public neb::DynamicCreator<MatrixTwo>
{
public:
    MatrixTwo();
    virtual ~MatrixTwo();

    virtual neb::E_CMD_STATUS Submit();
};

} /* namespace hello*/

#endif /* MATRIXTWO_HPP_ */

