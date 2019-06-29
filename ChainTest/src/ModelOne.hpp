/*******************************************************************************
 * Project:  Nebula
 * @file     ModelOne.hpp
 * @brief
 * @author   Bwar
 * @date:    2019年6月22日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef MODELONE_HPP_
#define MODELONE_HPP_

#include <actor/matrix/Model.hpp>

namespace hello
{

class ModelOne: public neb::Model, public neb::DynamicCreator<ModelOne>
{
public:
    ModelOne();
    virtual ~ModelOne();

    virtual neb::E_CMD_STATUS Submit();
};

} /* namespace hello*/

#endif /* MODELONE_HPP_ */

