﻿/******************************************************************************
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
#include <sofa/component/linearsolver/direct/config.h>

#include <Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>
#include <Eigen/MetisSupport>

namespace sofa::component::linearsolver::direct
{
    template<class Real>
    struct SimplicialLDLTTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SimplicialLDLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SimplicialLDLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SimplicialLDLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
        using MetisOrderSolver = Eigen::SimplicialLDLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
    };
}
