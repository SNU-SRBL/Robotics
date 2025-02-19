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

#include <sofa/core/visual/VisualModel.h>

namespace sofa::core::visual
{

class VisualParams;

class SOFA_CORE_API VisualManager : public VisualModel
{
public:
    SOFA_CLASS(VisualManager, VisualModel);
    SOFA_BASE_CAST_IMPLEMENTATION(VisualManager)
protected:
    /// Destructor
    ~VisualManager() override { }
public:
    /**
     *  \brief Called before rendering the scene
     */
    virtual void preDrawScene(VisualParams* /*vparams*/) {}

    /**
     *  \brief Called after rendering the scene
     */
    virtual void postDrawScene(VisualParams* /*vparams*/) {}

    /**
     *  \brief Called instead of rendering the scene
     *
     *  Return true if this object actually did the rendering, or false if it wasn't done.
     */
    virtual bool drawScene(VisualParams* /*vparams*/) { return false; }


    bool insertInNode( objectmodel::BaseNode* node ) override;
    bool removeInNode( objectmodel::BaseNode* node ) override;
};
} // namespace sofa::core::visual
