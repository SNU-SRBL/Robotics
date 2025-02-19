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
#include <CollisionOBBCapsule/config.h>

#include <sofa/core/collision/DetectionOutput.h>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/component/collision/geometry/SphereModel.h>
#include <CollisionOBBCapsule/geometry/OBBModel.h>
#include <CollisionOBBCapsule/detection/intersection/IntrCapsuleOBB.h>

namespace collisionobbcapsule::detection::intersection
{

using namespace sofa;

using collisionobbcapsule::geometry::OBB;
using collisionobbcapsule::geometry::TCapsule;
using collisionobbcapsule::geometry::Capsule;
using sofa::component::collision::geometry::TSphere;

class COLLISIONOBBCAPSULE_API CapsuleIntTool
{
public:
    typedef sofa::type::vector<sofa::core::collision::DetectionOutput> OutputVector;

    template <class DataTypes1,class DataTypes2>
    static int computeIntersection(TCapsule<DataTypes1>&, TCapsule<DataTypes2>&,SReal alarmDist,SReal contactDist,OutputVector* contacts);

    template <class DataTypes1,class DataTypes2>
    static int computeIntersection(TCapsule<DataTypes1>&, TSphere<DataTypes2>&,SReal alarmDist,SReal contactDist,OutputVector* contacts);

    template <class DataTypes>
    static int computeIntersection(TCapsule<DataTypes>&, OBB&,SReal alarmDist,SReal contactDist,OutputVector* contacts);

    template <class DataTypes1,class DataTypes2>
    static bool shareSameVertex(const TCapsule<DataTypes1>& c1, const TCapsule<DataTypes2>& c2);

    static bool shareSameVertex(const Capsule & c1, const Capsule & c2);

};

template <class DataTypes1,class DataTypes2>
bool CapsuleIntTool::shareSameVertex(const TCapsule<DataTypes1>&, const TCapsule<DataTypes2>&){
    return false;
}

template <class DataTypes1,class DataTypes2>
int CapsuleIntTool::computeIntersection(TCapsule<DataTypes1> & cap, TSphere<DataTypes2> & sph,SReal alarmDist,SReal contactDist,OutputVector* contacts){
    using namespace sofa::type;
    using namespace sofa::defaulttype;
    type::Vec3 sph_center = sph.center();
    type::Vec3 cap_p1 = cap.point1();
    type::Vec3 cap_p2 = cap.point2();
    SReal cap_rad = cap.radius();
    SReal sph_rad = sph.r();

    type::Vec3 AB = cap_p2 - cap_p1;
    type::Vec3 AC = sph_center - cap_p1;

    SReal theory_contactDist = (SReal) cap_rad + sph_rad + contactDist;
    SReal contact_exists = (SReal) cap_rad + sph_rad + alarmDist;
    SReal alpha = (SReal) (AB * AC)/AB.norm2();//projection of the sphere center on the capsule segment
                                        //alpha is the coefficient such as the projected point P = cap_p1 + alpha * AB
    if(alpha < 0.000001){//S is the sphere center, here is the case :
                         //        S
                         //           A--------------B
        type::Vec3 PQ = sph_center - cap_p1;

        if(PQ.norm2() > contact_exists * contact_exists)
            return 0;

        contacts->resize(contacts->size()+1);
        sofa::core::collision::DetectionOutput *detection = &*(contacts->end()-1);

        detection->elem = std::pair<core::CollisionElementIterator, core::CollisionElementIterator>(cap, sph);
        //detection->id = (cap.getCollisionModel()->getSize() > sph.getCollisionModel()->getSize()) ? cap.getIndex() : sph.getIndex();
        detection->id = cap.getIndex();

        detection->normal = PQ;
        detection->value = detection->normal.norm();
        detection->normal /= detection->value;
        detection->point[0] = cap_p1 + cap_rad * detection->normal;
        detection->point[1] = sph.getContactPointByNormal( detection->normal );
        detection->value -= theory_contactDist;

        return 1;
    }
    else if(alpha > 0.999999){//the case :
                              //                         S
                              //      A-------------B
        type::Vec3 PQ = sph_center - cap_p2;

        if(PQ.norm2() > contact_exists * contact_exists)
            return 0;

        contacts->resize(contacts->size()+1);
        sofa::core::collision::DetectionOutput *detection = &*(contacts->end()-1);

        detection->elem = std::pair<core::CollisionElementIterator, core::CollisionElementIterator>(cap, sph);
        //detection->id = (cap.getCollisionModel()->getSize() > sph.getCollisionModel()->getSize()) ? cap.getIndex() : sph.getIndex();
        detection->id = cap.getIndex();

        detection->normal = PQ;
        detection->value = detection->normal.norm();
        detection->normal /= detection->value;
        detection->point[0] = cap_p2 + cap_rad * detection->normal;
        detection->point[1] = sph.getContactPointByNormal( detection->normal );
        detection->value -= theory_contactDist;

        return 1;
    }
    else{//the case :
         //              S
         //      A-------------B
        type::Vec3 P = cap_p1 + alpha * AB;
        type::Vec3 PQ = sph_center - P;

        if(PQ.norm2() > contact_exists * contact_exists)
            return 0;

        contacts->resize(contacts->size()+1);
        sofa::core::collision::DetectionOutput *detection = &*(contacts->end()-1);

        detection->elem = std::pair<core::CollisionElementIterator, core::CollisionElementIterator>(cap, sph);
        //detection->id = (cap.getCollisionModel()->getSize() > sph.getCollisionModel()->getSize()) ? cap.getIndex() : sph.getIndex();
        detection->id = cap.getIndex();

        detection->normal = PQ;
        detection->value = detection->normal.norm();
        detection->normal /= detection->value;
        detection->point[0] = P + cap_rad * detection->normal;
        detection->point[1] = sph.getContactPointByNormal( detection->normal );
        detection->value -= theory_contactDist;

        return 1;
    }
}


#if  !defined(SOFA_COMPONENT_COLLISION_CAPSULEINTTOOL_CPP)
extern template COLLISIONOBBCAPSULE_API int CapsuleIntTool::computeIntersection(TCapsule<sofa::defaulttype::Vec3Types>&, TCapsule<sofa::defaulttype::Vec3Types>&,SReal alarmDist,SReal contactDist,OutputVector* contacts);
extern template COLLISIONOBBCAPSULE_API int CapsuleIntTool::computeIntersection(TCapsule<sofa::defaulttype::Vec3Types>&, TCapsule<sofa::defaulttype::RigidTypes>&,SReal alarmDist,SReal contactDist,OutputVector* contacts);
extern template COLLISIONOBBCAPSULE_API int CapsuleIntTool::computeIntersection(TCapsule<sofa::defaulttype::RigidTypes>&, TCapsule<sofa::defaulttype::RigidTypes>&,SReal alarmDist,SReal contactDist,OutputVector* contacts);
extern template COLLISIONOBBCAPSULE_API int CapsuleIntTool::computeIntersection(TCapsule<sofa::defaulttype::RigidTypes> & cap, OBB& obb,SReal alarmDist,SReal contactDist,OutputVector* contacts);
extern template COLLISIONOBBCAPSULE_API int CapsuleIntTool::computeIntersection(TCapsule<sofa::defaulttype::Vec3Types> & cap, OBB& obb,SReal alarmDist,SReal contactDist,OutputVector* contacts);
#endif

} // namespace collisionobbcapsule::detection::intersection
