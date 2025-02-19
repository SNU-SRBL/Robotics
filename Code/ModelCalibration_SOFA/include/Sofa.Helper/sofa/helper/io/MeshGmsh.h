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
#ifndef SOFA_HELPER_IO_MESHGMSH_H
#define SOFA_HELPER_IO_MESHGMSH_H

#include <sofa/helper/io/Mesh.h>
#include <istream>

namespace sofa
{

namespace helper
{

namespace io
{

class SOFA_HELPER_API MeshGmsh : public Mesh
{
public:

    MeshGmsh(const std::string& filename)
    {
        init (filename);
    }

    void init (std::string filename);

protected:

    bool readGmsh(std::ifstream &file, const unsigned int gmshFormat);

    void addInGroup(type::vector< sofa::type::PrimitiveGroup>& group, int tag, std::size_t eid);

    void normalizeGroup(type::vector< sofa::type::PrimitiveGroup>& group);
};

} // namespace io

} // namespace helper

} // namespace sofa

#endif // SOFA_HELPER_IO_MESHGMSH_H
