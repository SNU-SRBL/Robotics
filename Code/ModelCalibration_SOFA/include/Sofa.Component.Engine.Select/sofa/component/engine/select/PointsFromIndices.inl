/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once
#include <sofa/component/engine/select/PointsFromIndices.h>
#include <sofa/core/visual/VisualParams.h>

namespace sofa::component::engine::select
{

template <class DataTypes>
PointsFromIndices<DataTypes>::PointsFromIndices()
    : f_X( initData (&f_X, "position", "Position coordinates of the degrees of freedom") )
    , f_indices( initData(&f_indices,"indices","Indices of the points") )
    , f_indices_position( initData (&f_indices_position, "indices_position", "Coordinates of the points contained in indices"))
{
    addInput(&f_X);
    addInput(&f_indices);
    addOutput(&f_indices_position);
}

template <class DataTypes>
void PointsFromIndices<DataTypes>::init()
{
    if (f_X.getValue().empty())
    {
        sofa::core::behavior::MechanicalState<DataTypes>* mstate;
        this->getContext()->get(mstate);
        if (mstate)
        {
            sofa::core::objectmodel::BaseData* parent = mstate->findData("position");
            if (parent)
            {
                f_X.setParent(parent);
                f_X.setReadOnly(true);
            }
        }
    }

    setDirtyValue();
}

template <class DataTypes>
void PointsFromIndices<DataTypes>::reinit()
{
    update();
}

template <class DataTypes>
bool PointsFromIndices<DataTypes>::contains(VecCoord& v, Coord c)
{
    for( unsigned i=0; i<v.size(); ++i )
    {
        if (c == v[i]) return true;
    }
    return false;
}

template <class DataTypes>
void PointsFromIndices<DataTypes>::doUpdate()
{
    const SetIndex& indices = f_indices.getValue();
    const VecCoord& x = f_X.getValue();

    VecCoord& indices_position = *(f_indices_position.beginWriteOnly());

    if(!x.empty())
    {
        indices_position.clear();
        //indices_position.resize(indices.size());

        for( unsigned i=0; i<indices.size(); ++i )
        {
            if (!contains(indices_position, x[indices[i]]))
                indices_position.push_back(x[indices[i]]);
        }

    }

    f_indices_position.endEdit();
}

} //namespace sofa::component::engine::select
