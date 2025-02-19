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

#include <sofa/core/objectmodel/BaseObject.h>

namespace sofa::core::collision
{

class CollisionAlgorithm : public virtual objectmodel::BaseObject
{
public:
    SOFA_ABSTRACT_CLASS(CollisionAlgorithm, objectmodel::BaseObject);

    /// Collision 'pipeline' instance, allowing to store multiple internal states
    typedef void* Instance;
protected:
    /// Current collision 'pipeline' instance, allowing to store multiple internal states
    Instance instance;


    CollisionAlgorithm()
        : instance(nullptr)
    {
    }
public:
    /// Allow to store multiple internal states by specifying a different collision pipeline 'instance'
    virtual void setInstance(Instance inst)
    {
        if (instance == inst) return;
        changeInstance(inst);
        instance = inst;
    }

protected:
    virtual void changeInstance(Instance)=0;
};
} // namespace sofa::core::collision
