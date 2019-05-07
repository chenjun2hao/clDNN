/*
// Copyright (c) 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../C/reshape.h"
#include "primitive.hpp"

namespace cldnn
{
/// @addtogroup cpp_api C++ API
/// @{
/// @addtogroup cpp_topology Network Topology
/// @{
/// @addtogroup cpp_primitives Primitives
/// @{

/// @brief Changes information about inputs's layout effectively creating new memory which share underlaying buffer
/// but is interpreted in a different way (different shape).
/// @note reshape primitive is supposed only to reinterpret shape of the memory therefore it's not possible to change
/// neither data type nor format of the input buffer and total number of elements in input and output (excluding paddings) must match.
/// Please note that there is no guarantee that underlying data will be in proper format if primitive was explicitly added to output list.
struct reshape : public primitive_base<reshape, CLDNN_PRIMITIVE_DESC(reshape)>
{
    CLDNN_DECLARE_PRIMITIVE(reshape)

    /// @brief Constructs reshape primitive.
    /// @param id This primitive id.
    /// @param input Input primitive id.
    /// @param output_shape Requested memory shape (excluding padding).
    /// A dimension could be 0, in this case,  the value is taken from the input tensor.
    /// At most one dimension of the new shape can be -1. In this case, the value is inferred from the size of the tensor and the remaining dimensions.
    /// @param output_padding Requested memory padding.
    reshape(
        const primitive_id& id,
        const primitive_id& input,
        const tensor& output_shape,
        const padding& output_padding = padding()
    )
        : primitive_base(id, { input }, output_padding)
        , output_shape(output_shape)
    {
    }

    /// @brief Constructs a copy from basic C API @CLDNN_PRIMITIVE_DESC{reshape}
    reshape(const dto* dto)
        : primitive_base(dto)
        , output_shape(dto->output_shape)
    {
    }

    /// @brief Requested memory shape.
    tensor output_shape;

protected:
    void update_dto(dto& dto) const override
    {
        dto.output_shape = output_shape;
    }
private:
    reshape() : primitive_base() {} // Constructor necessary for serialization process
    CLDNN_SERIALIZATION_MEMBERS(
        ar & CLDNN_SERIALIZATION_BASE_OBJECT_NVP_PRIMITIVE_BASE(reshape) & CLDNN_SERIALIZATION_NVP(output_shape);
    )
};

/// @}
/// @}
/// @}
}
CLDNN_SERIALIZATION_EXPORT_NODE_KEY(reshape)