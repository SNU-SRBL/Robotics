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
#ifndef SOFA_SIMULATION_TREE_TOPOLOGYCHANGEACTION_H
#define SOFA_SIMULATION_TREE_TOPOLOGYCHANGEACTION_H

#include <sofa/simulation/Visitor.h>

namespace sofa
{

namespace simulation
{

class SOFA_SIMULATION_CORE_API TopologyChangeVisitor : public Visitor
{

public:
    TopologyChangeVisitor(const sofa::core::ExecParams* params, sofa::core::topology::Topology* source);

    ~TopologyChangeVisitor() override {}

    virtual void processTopologyChange(simulation::Node* node, sofa::core::objectmodel::BaseObject* obj);

    Result processNodeTopDown(simulation::Node* node) override;
    void processNodeBottomUp(simulation::Node* node) override;

    /// Specify whether this action can be parallelized.
    bool isThreadSafe() const override { return true; }

    /// Return a category name for this action.
    /// Only used for debugging / profiling purposes
    const char* getCategoryName() const override { return "topologyChange"; }
    const char* getClassName() const override { return "TopologyChangeVisitor"; }
    std::string getInfos() const override;
protected:
    sofa::core::topology::Topology* m_source;
};


} // namespace simulation

} // namespace sofa

#endif
