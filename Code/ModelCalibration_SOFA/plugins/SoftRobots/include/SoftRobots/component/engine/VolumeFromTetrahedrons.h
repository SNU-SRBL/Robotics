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
*                           Plugin SoftRobots                                 *
*                                                                             *
* This plugin is also distributed under the GNU LGPL (Lesser General          *
* Public License) license with the same conditions than SOFA.                 *
*                                                                             *
* Contributors: Defrost team  (INRIA, University of Lille, CNRS,              *
*               Ecole Centrale de Lille)                                      *
*                                                                             *
* Contact information: https://project.inria.fr/softrobot/contact/            *
******************************************************************************/
#pragma once

#include <sofa/core/DataEngine.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/behavior/MechanicalState.h>

#include <SoftRobots/component/initSoftRobots.h>

namespace softrobots::engine
{

/**
 * This class returns the volumes of a given volumic mesh.
 * Description can be found at:
 * https://softrobotscomponents.readthedocs.io
 */
template <class DataTypes>
class SOFA_SOFTROBOTS_API VolumeFromTetrahedrons : public sofa::core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(VolumeFromTetrahedrons,DataTypes), sofa::core::DataEngine);

    typedef typename DataTypes::VecCoord VecCoord;

    typedef typename DataTypes::Coord  Coord;
    typedef typename Coord::value_type Real;

    typedef typename sofa::core::behavior::MechanicalState<DataTypes> MechanicalState;
    typedef typename sofa::core::topology::BaseMeshTopology           BaseMeshTopology;

    typedef sofa::core::topology::BaseMeshTopology::Tetra         Tetra;
    typedef sofa::core::topology::BaseMeshTopology::Hexa          Hexa;

    typedef sofa::core::topology::BaseMeshTopology::SeqTetrahedra     VecTetras;
    typedef sofa::core::topology::BaseMeshTopology::SeqHexahedra      VecHexas;

public:

    VolumeFromTetrahedrons();
    ~VolumeFromTetrahedrons() override;

    ////////////////////////// Inherited from BaseObject ///////////////////
    void init() override;
    void reinit() override;
    ////////////////////////////////////////////////////////////////////////

    ////////////////////////// Inherited from DataEngine////////////////////
    void doUpdate() override;
    ///////////////////////////////////////////////////////////////////////

    SReal getVolume() {return d_volume.getValue();}

protected:

    MechanicalState*   m_state;
    BaseMeshTopology*  m_topology;

    sofa::Data<VecCoord>     d_positions;
    sofa::Data<VecTetras>    d_tetras;
    sofa::Data<VecHexas>     d_hexas;

    sofa::Data<Real>         d_volume;
    sofa::Data<bool>         d_doUpdate;

    void updateVolume();

private:

    void initTopology();
    void checkTopology();

    SReal getElementVolume(const Tetra& tetra);
    SReal getElementVolume(const Hexa& hexa);
};

extern template class VolumeFromTetrahedrons<sofa::defaulttype::Vec3Types>;

} // namespace

namespace sofa::component::engine
{
    template <class DataTypes>
    using VolumeFromTetrahedrons SOFA_ATTRIBUTE_DEPRECATED__RENAME_NAMESPACE_SOFTROBOTS()
        = softrobots::engine::VolumeFromTetrahedrons<DataTypes>;
}

