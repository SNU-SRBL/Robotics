/******************************************************************************
*                              SofaPython3 plugin                             *
*                  (c) 2021 CNRS, University of Lille, INRIA                  *
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
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once
#include <SofaPython3/config.h>

#ifdef SOFA_BUILD_SOFAPYTHON3
#  define SOFAPYTHON3_TESTING_API PYBIND11_EXPORT
#else
#  define SOFAPYTHON3_TESTING_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

namespace sofapython3::testing
{
    constexpr const char* MODULE_NAME = "SofaPython3Testing";
    constexpr const char* MODULE_VERSION = "1.0";
} // namespace sofapython3::testing
