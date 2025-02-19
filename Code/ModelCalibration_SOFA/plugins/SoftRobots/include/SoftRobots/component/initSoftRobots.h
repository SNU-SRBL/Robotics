/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture                          *
*                (c) 2006-2018 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                           Plugin SoftRobots    v1.0                         *
*				                                              *
* This plugin is also distributed under the GNU LGPL (Lesser General          *
* Public License) license with the same conditions than SOFA.                 *
*                                                                             *
* Contributors: Defrost team  (INRIA, University of Lille, CNRS,              *
*               Ecole Centrale de Lille)                                      *
*                                                                             *
* Contact information: https://project.inria.fr/softrobot/contact/            *
*                                                                             *
******************************************************************************/
#ifndef INITSOFTROBOTS_H
#define INITSOFTROBOTS_H


#include <sofa/config.h>

#ifdef SOFA_BUILD_SOFTROBOTS
#define SOFA_TARGET SoftRobots
#define SOFA_SOFTROBOTS_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#define SOFA_SOFTROBOTS_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

#ifdef SOFA_BUILD_SOFTROBOTS
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_NAMESPACE_SOFTROBOTS()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_NAMESPACE_SOFTROBOTS() \
    SOFA_ATTRIBUTE_DEPRECATED( \
        "v23.06", "v23.12", \
        "Namespace in the plugin SoftRobots is now 'softrobots'.")
#endif

#define SOFTROBOTS_HAVE_SOFAPYTHON 0
#define SOFTROBOTS_HAVE_SOFAPYTHON3 0
#define SOFTROBOTS_HAVE_SOFA_GL 1

namespace softrobots
{
    constexpr const char* MODULE_NAME = "SoftRobots";
    constexpr const char* MODULE_VERSION = "1.0";
}

#endif // INITSOFTROBOTS_H
