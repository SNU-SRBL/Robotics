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
#ifndef SOFA_IMAGE_MARCHINGCUBESENGINE_H
#define SOFA_IMAGE_MARCHINGCUBESENGINE_H

#include <image/config.h>
#include "ImageTypes.h"
#include <sofa/core/DataEngine.h>
#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/visual/VisualParams.h>

#include <sofa/core/objectmodel/Event.h>
#include <sofa/simulation/AnimateEndEvent.h>

#include <sofa/type/Vec.h>

namespace sofa
{

namespace component
{

namespace engine
{

/**
 * This class computes an isosurface from an image using marching cubes algorithm
 */


template <class _ImageTypes>
class MarchingCubesEngine : public core::DataEngine
{
public:
    typedef core::DataEngine Inherited;
    SOFA_CLASS(SOFA_TEMPLATE(MarchingCubesEngine,_ImageTypes),Inherited);

    typedef SReal Real;

    Data< Real > isoValue; ///< pixel value to extract isosurface
    Data< type::Vec<3,unsigned int> > subdiv; ///< number of subdividions in x,y,z directions (use image dimension if =0)
    Data< bool > invertNormals; ///< invert triangle vertex order
    Data< bool > showMesh; ///< show reconstructed mesh

    typedef _ImageTypes ImageTypes;
    typedef typename ImageTypes::T T;
    typedef typename ImageTypes::imCoord imCoord;
    typedef helper::ReadAccessor<Data< ImageTypes > > raImage;
    Data< ImageTypes > image;

    typedef defaulttype::ImageLPTransform<Real> TransformType;
    typedef typename TransformType::Coord Coord;
    typedef helper::ReadAccessor<Data< TransformType > > raTransform;
    Data< TransformType > transform;

    typedef type::vector<type::Vec<3,Real> > SeqPositions;
    typedef helper::ReadAccessor<Data< SeqPositions > > raPositions;
    typedef helper::WriteOnlyAccessor<Data< SeqPositions > > waPositions;
    Data< SeqPositions > position; ///< output positions

    typedef typename core::topology::BaseMeshTopology::Triangle Triangle;
    typedef typename core::topology::BaseMeshTopology::SeqTriangles SeqTriangles;
    typedef helper::ReadAccessor<Data< SeqTriangles > > raTriangles;
    typedef helper::WriteOnlyAccessor<Data< SeqTriangles > > waTriangles;
    Data< SeqTriangles > triangles; ///< output triangles

    MarchingCubesEngine()    :   Inherited()
        , isoValue(initData(&isoValue,(Real)(1.0),"isoValue","pixel value to extract isosurface"))
        , subdiv(initData(&subdiv,type::Vec<3,unsigned int>(0,0,0),"subdiv","number of subdividions in x,y,z directions (use image dimension if =0)"))
        , invertNormals(initData(&invertNormals,true,"invertNormals","invert triangle vertex order"))
        , showMesh(initData(&showMesh,false,"showMesh","show reconstructed mesh"))
        , image(initData(&image,ImageTypes(),"image",""))
        , transform(initData(&transform,TransformType(),"transform",""))
        , position(initData(&position,SeqPositions(),"position","output positions"))
        , triangles(initData(&triangles,SeqTriangles(),"triangles","output triangles"))
        , time((unsigned int)0)
    {
        image.setReadOnly(true);
        transform.setReadOnly(true);
        f_listening.setValue(true);
    }

    void init() override
    {
        addInput(&image);
        addInput(&transform);
        addOutput(&position);
        addOutput(&triangles);
        setDirtyValue();
    }

    void reinit() override { update(); }

protected:

    unsigned int time;

    void doUpdate() override
    {
        raImage in(this->image);
		raTransform inT(this->transform);

        // get image at time t
        const cimg_library::CImg<T>& img = in->getCImg(this->time);

        // get subdivision
        type::Vec<3,int> r((int)this->subdiv.getValue()[0],(int)this->subdiv.getValue()[1],(int)this->subdiv.getValue()[2]);
        for(unsigned int i=0; i<3; i++) if(!r[i]) r[i]=-100;

        // get isovalue
        const float val=(float)this->isoValue.getValue();

        // marching cubes using cimg
        cimg_library::CImgList<unsigned int> faces;
        cimg_library::CImg<float> points = img.get_shared_channel(0).get_isosurface3d (faces, val,r[0],r[1],r[2]);

        // update points and faces
        waPositions pos(this->position);
        pos.resize(points.width());
        cimg_forX(points,i)  pos[i]=inT->fromImage(Coord((Real)points(i,0),(Real)points(i,1),(Real)points(i,2)));

        waTriangles tri(this->triangles);
        tri.resize(faces.size());
        if( invertNormals.getValue() )
            cimglist_for(faces,l) tri[l]=Triangle(faces(l,2),faces(l,1),faces(l,0));
        else
            cimglist_for(faces,l) tri[l]=Triangle(faces(l,0),faces(l,1),faces(l,2));

    }

    void handleEvent(sofa::core::objectmodel::Event *event) override
    {
        if (simulation::AnimateEndEvent::checkEventType(event))
        {
            raImage in(this->image);
            raTransform inT(this->transform);

            // get current time modulo dimt
            const unsigned int dimt=in->getDimensions()[4];
            if(!dimt) return;
            Real t=inT->toImage(this->getContext()->getTime()) ;
            t-=(Real)((int)((int)t/dimt)*dimt);
            t=(t-floor(t)>0.5)?ceil(t):floor(t); // nearest
            if(t<0) t=0.0; else if(t>=(Real)dimt) t=(Real)dimt-1.0; // clamp

            if(this->time!=(unsigned int)t) { this->time=(unsigned int)t; update(); }
        }
    }

    void draw(const core::visual::VisualParams* vparams) override
    {
        if (!vparams->displayFlags().getShowVisualModels()) return;
        if (!this->showMesh.getValue()) return;

        vparams->drawTool()->saveLastState();

        bool wireframe=vparams->displayFlags().getShowWireFrame();

        raPositions pos(this->position);
        raTriangles tri(this->triangles);

        const sofa::type::RGBAColor color(0.5,0.5,0.5,0.5);
        vparams->drawTool()->setMaterial(color);
        vparams->drawTool()->enableLighting();

        std::size_t size = tri.size();
        std::vector<type::Vec3> points;
        std::vector<type::Vec3> normals;
        std::vector<sofa::type::RGBAColor> colors;
        points.resize(3*size);
        normals.resize(size);
        colors.resize(size);

        for (std::size_t i=0; i<size; ++i)
        {
            points[3*i] = pos[ tri[i][0] ];
            points[3*i+1] = pos[ tri[i][1] ];
            points[3*i+2] = pos[ tri[i][2] ];
            normals[i] = cross((points[3*i]-points[3*i+1]),(points[3*i]-points[3*i+2]));
            normals[i].normalize();
            colors[i] = color;
        }
        // Draw triangles
        if(!wireframe)
            vparams->drawTool()->drawTriangles(points,normals,colors);
        // Wireframe mode: draw line loop
        else
            vparams->drawTool()->drawLineLoop(points,1.0,color);

        vparams->drawTool()->restoreLastState();
    }
};


} // namespace engine

} // namespace component

} // namespace sofa

#endif // SOFA_IMAGE_MarchingCubesENGINE_H
