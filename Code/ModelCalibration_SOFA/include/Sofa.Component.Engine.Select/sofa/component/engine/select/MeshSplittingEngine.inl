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
#include <sofa/component/engine/select/MeshSplittingEngine.h>

namespace sofa::component::engine::select
{

template <class container>
inline void parseIndices(type::vector<unsigned int>& pairs, const container& indices, const unsigned int parentIndex)
{
    for(size_t i=0;i<indices.size();++i)
        if(2*indices[i]<pairs.size())
            pairs[2*indices[i]]=parentIndex;
}

template <class container1,class container2>
inline void parseIndices(type::vector<unsigned int>& pairs, const container1& indices,const container2& cells, const unsigned int parentIndex)
{
    for(size_t i=0;i<indices.size();++i)
        for(size_t j=0;j<cells[indices[i]].size();++j)
            if(2*cells[indices[i]][j]<pairs.size())
                pairs[2*cells[indices[i]][j]]=parentIndex;
}

template <class DataTypes>
MeshSplittingEngine<DataTypes>::MeshSplittingEngine()
    : Inherited()
    , inputPosition(initData(&inputPosition,"position","input vertices"))
    , inputEdges(initData(&inputEdges,"edges","input edges"))
    , inputTriangles(initData(&inputTriangles,"triangles","input triangles"))
    , inputQuads(initData(&inputQuads,"quads","input quads"))
    , inputTets(initData(&inputTets,"tetrahedra","input tetrahedra"))
    , inputHexa(initData(&inputHexa,"hexahedra","input hexahedra"))
    , nbInputs (initData(&nbInputs, (unsigned)0, "nbInputs", "Number of input vectors"))
    , indices(this, "indices", "input vertex indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , edgeIndices(this, "edgeIndices", "input edge indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , triangleIndices(this, "triangleIndices", "input triangle indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , quadIndices(this, "quadIndices", "input quad indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , tetrahedronIndices(this, "tetrahedronIndices", "input tetrahedron indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , hexahedronIndices(this, "hexahedronIndices", "input hexahedron indices", sofa::core::objectmodel::DataEngineDataType::DataEngineInput)
    , indexPairs( initData( &indexPairs, type::vector<unsigned>(), "indexPairs", "couples for input vertices: ROI index + index in the ROI"))
    , position(this, "position", "output vertices", sofa::core::objectmodel::DataEngineDataType::DataEngineOutput)
{
    resizeData();
}

template <class DataTypes>
MeshSplittingEngine<DataTypes>::~MeshSplittingEngine()
{
}

template <class DataTypes>
void MeshSplittingEngine<DataTypes>::doUpdate()
{
    helper::ReadAccessor<Data< SeqPositions > > i_pos(this->inputPosition);
    const size_t& nb = nbInputs.getValue();

    helper::WriteOnlyAccessor<Data< type::vector<unsigned int> > > indPairs(this->indexPairs);
    indPairs.resize(2*i_pos.size());
    for(size_t i=0;i<i_pos.size();++i) indPairs[2*i]=nb; // assign to remaining sub mesh

    // get parent of each child
    for(int i=nb-1;i>=0;--i) // use reverse order to prioritize the first ROIs
    {
        parseIndices(indPairs.wref(), indices[i]->getValue(), i);
        parseIndices(indPairs.wref(), edgeIndices[i]->getValue(), inputEdges.getValue(), i);
        parseIndices(indPairs.wref(), triangleIndices[i]->getValue(), inputTriangles.getValue(), i);
        parseIndices(indPairs.wref(), quadIndices[i]->getValue(), inputQuads.getValue(), i);
        parseIndices(indPairs.wref(), tetrahedronIndices[i]->getValue(), inputTets.getValue(), i);
        parseIndices(indPairs.wref(), hexahedronIndices[i]->getValue(), inputHexa.getValue(), i);
    }

    // add positions
    std::vector<SeqPositions*> o_pos(nb+1);
    for(size_t i=0;i<nb+1;++i) { o_pos[i]=position[i]->beginWriteOnly(); o_pos[i]->clear(); }

    for(size_t i=0;i<i_pos.size();++i)
    {
        indPairs[2*i+1]=o_pos[indPairs[2*i]]->size();
        o_pos[indPairs[2*i]]->push_back(i_pos[i]);
    }
    for(size_t i=0;i<nb+1;++i) position[i]->endEdit();

    msg_info() <<this->name<<":"<<"updated" ;
}


} //namespace sofa::component::engine::select
