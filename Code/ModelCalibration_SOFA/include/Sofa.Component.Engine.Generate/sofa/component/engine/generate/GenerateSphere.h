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
#include <sofa/component/engine/generate/config.h>



#include <sofa/core/DataEngine.h>
#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/topology/BaseMeshTopology.h>

#include <sofa/defaulttype/VecTypes.h>

namespace sofa::component::engine::generate
{

/*** This class creates a mesh on the sphere as the tessellation of a regular tetrahedron,
 regular octahedron or regular dodecahedron.
 The mesh can be either a triangulation, a tetrahedal mesh (with the sphere center) or a 
 rational Bezier triangulation or tetrahedral mesh. 
 */
template <class DataTypes>
class GenerateSphere : public core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(GenerateSphere,DataTypes),core::DataEngine);
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::Real Real;
    typedef typename sofa::core::topology::Topology::PointID PointID;
    typedef sofa::core::topology::BaseMeshTopology::SeqTetrahedra SeqTetrahedra;
    typedef typename sofa::core::topology::Topology::Edge Edge;
    typedef sofa::core::topology::BaseMeshTopology::SeqTriangles SeqTriangles;
    typedef typename SeqTetrahedra::value_type Tetrahedron;
    typedef typename SeqTriangles::value_type Triangle;

    typedef enum {
        TETRAHEDRON=1,
        OCTAHEDRON=2,
        ICOSAHEDRON=3
    } PlatonicTriangulation;

public:

    GenerateSphere();

    ~GenerateSphere() override {}

    void init() override;

    void reinit() override;

    void doUpdate() override;

public:
    Data<VecCoord> f_outputTetrahedraPositions; ///< Output tetrahedra positions
    Data<SeqTetrahedra> f_tetrahedra; ///< Output tetrahedra
    Data<VecCoord> f_outputTrianglesPositions; ///< Output triangle positions
    Data<SeqTriangles> f_triangles; ///< Output triangles

    Data<size_t> f_bezierTetrahedronDegree; ///< Degree of Bezier tetrahedra
    Data<sofa::type::vector<Real> > f_bezierTetrahedronWeight; ///<  Output weight for rational Bezier triangles
    Data<sofa::type::vector<bool> > f_isBezierTetrahedronRational; ///<  For each Bezier tetrahedron, indicates if it is rational
    Data<size_t> f_bezierTriangleDegree; ///< Degree of Bezier triangles
    Data<sofa::type::vector<Real> > f_bezierTriangleWeight; ///< Output weight for rational Bezier triangles
    Data<sofa::type::vector<bool> > f_isBezierTriangleRational; ///< For each Bezier triangle indicates, if it is rational or integral

    Data<Real > f_radius; ///< Radius of the sphere
    Data<Coord> f_origin; ///< Origin
    Data<size_t > f_tessellationDegree; ///< Degree of tessellation of each platonic triangle 
    Data<std::string>     f_platonicSolidName; ///< Name of the platonics solid 

    PlatonicTriangulation platonicSolid; ///< the type of platonic solid used for the tessellation
};


#if  !defined(SOFA_COMPONENT_ENGINE_GENERATESPHERE_CPP)
extern template class SOFA_COMPONENT_ENGINE_GENERATE_API GenerateSphere<defaulttype::Vec3Types>;

#endif

} //namespace sofa::component::engine::generate
