/*******************************************************************************
 * Project:  Nebula
 * @file     ModelTwo.hpp
 * @brief
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef MODELTWO_HPP_
#define MODELTWO_HPP_

#include <actor/matrix/Model.hpp>

namespace hello
{

class ModelTwo: public neb::Model, public neb::DynamicCreator<ModelTwo>
{
public:
    ModelTwo();
    virtual ~ModelTwo();

    virtual neb::E_CMD_STATUS Submit();
};

} /* namespace hello*/

#endif /* MODELTWO_HPP_ */

