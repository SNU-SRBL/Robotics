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

#include <sofa/config.h>
#include <sofa/config/sharedlibrary_defines.h>

#ifdef SOFA_BUILD_SOFA_COMPONENT_VISUAL
#  define SOFA_TARGET Sofa.Component.Visual
#  define SOFA_COMPONENT_VISUAL_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_COMPONENT_VISUAL_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

namespace sofa::component::visual
{
	constexpr const char* MODULE_NAME = "Sofa.Component.Visual";
	constexpr const char* MODULE_VERSION = "23.06.00";
} // namespace sofa::component::visual

#ifdef SOFA_BUILD__COMPONENT__VISUAL
#define SOFA_ATTRIBUTE_DEPRECATED__VEC3STATE_AS_VISUALSTATE()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__VEC3STATE_AS_VISUALSTATE() \
    SOFA_ATTRIBUTE_DEPRECATED( \
        "v23.06", "v23.12", \
        "Vec3State is now an alias of sofa::core::visual::VisualState<defaulttype::Vec3Types>.")
#endif
