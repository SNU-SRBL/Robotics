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
#ifndef SOFAGENERAL_CONFIG_H
#define SOFAGENERAL_CONFIG_H

#include <sofa/config.h>

#define SOFAGENERAL_HAVE_SOFADENSESOLVER 0

#ifdef SOFA_BUILD_SOFAGENERAL
#  define SOFA_TARGET SofaGeneral
#  define SOFA_SOFAGENERAL_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_SOFAGENERAL_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

#endif
