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

#include <sofa/component/constraint/projective/OscillatorConstraint.h>
#include <sofa/core/visual/VisualParams.h>
#include <cmath>

namespace sofa::component::constraint::projective
{

template <class TDataTypes>
OscillatorConstraint<TDataTypes>::OscillatorConstraint(core::behavior::MechanicalState<TDataTypes>* mstate)
    : core::behavior::ProjectiveConstraintSet<TDataTypes>(mstate)
    , constraints(initData(&constraints,"oscillators","Define a sequence of oscillating particules: \n[index, Mean(x,y,z), amplitude(x,y,z), pulsation, phase]"))
{
}

template <class TDataTypes>
OscillatorConstraint<TDataTypes>::~OscillatorConstraint()
{
}

template <class TDataTypes>
OscillatorConstraint<TDataTypes>*  OscillatorConstraint<TDataTypes>::addConstraint(unsigned index, const Coord& mean, const Deriv& amplitude, Real pulsation, Real phase)
{
    this->constraints.beginEdit()->push_back( Oscillator(index,mean,amplitude,pulsation,phase) );
    return this;
}


template <class TDataTypes> template <class DataDeriv>
void OscillatorConstraint<TDataTypes>::projectResponseT(const core::MechanicalParams* /*mparams*/, DataDeriv& res)
{
    const type::vector<Oscillator> &oscillators = constraints.getValue();
    for (unsigned i = 0; i < oscillators.size(); ++i)
    {
        const unsigned& index = oscillators[i].index;
        res[index] = Deriv();
    }
}

template <class TDataTypes>
void OscillatorConstraint<TDataTypes>::projectResponse(const core::MechanicalParams* mparams, DataVecDeriv& resData)
{
    helper::WriteAccessor<DataVecDeriv> res = resData;
    projectResponseT(mparams, res.wref());
}

template <class TDataTypes>
void OscillatorConstraint<TDataTypes>::projectVelocity(const core::MechanicalParams* /*mparams*/, DataVecDeriv& vData)
{
    helper::WriteAccessor<DataVecDeriv> v = vData;
    const type::vector<Oscillator>& oscillators = constraints.getValue();
    Real t = (Real) this->getContext()->getTime();
    for (unsigned i = 0; i < oscillators.size(); ++i)
    {
        const unsigned& index = oscillators[i].index;
        const Deriv& a = oscillators[i].amplitude;
        const Real& w = oscillators[i].pulsation;
        const Real& p = oscillators[i].phase;

        v[index] = a * w * cos(w * t + p);
    }
}

template <class TDataTypes>
void OscillatorConstraint<TDataTypes>::projectPosition(const core::MechanicalParams* /*mparams*/, DataVecCoord& xData)
{
    helper::WriteAccessor<DataVecCoord> x = xData;
    const type::vector<Oscillator> &oscillators = constraints.getValue();
    Real t = (Real) this->getContext()->getTime();
    for (unsigned i = 0; i < oscillators.size(); ++i)
    {
        const unsigned& index = oscillators[i].index;
        const Coord& m = oscillators[i].mean;
        const Deriv& a = oscillators[i].amplitude;
        const Real& w = oscillators[i].pulsation;
        const Real& p = oscillators[i].phase;

        x[index] = m + a * sin(w * t + p);
    }
}

template <class TDataTypes>
void OscillatorConstraint<TDataTypes>::projectJacobianMatrix(const core::MechanicalParams* mparams, DataMatrixDeriv& cData)
{
    helper::WriteAccessor<DataMatrixDeriv> c = cData;

    MatrixDerivRowIterator rowIt = c->begin();
    MatrixDerivRowIterator rowItEnd = c->end();

    while (rowIt != rowItEnd)
    {
        projectResponseT<MatrixDerivRowType>(mparams, rowIt.row());
        ++rowIt;
    }
}

template <class TDataTypes>
OscillatorConstraint<TDataTypes>::Oscillator::Oscillator(): index(0)
{
}

template <class TDataTypes>
OscillatorConstraint<TDataTypes>::Oscillator::Oscillator(unsigned int i, const Coord& m, const Deriv& a,
        const Real& w, const Real& p) :
    index(i), mean(m), amplitude(a), pulsation(w), phase(p)
{
}

} // namespace sofa::component::constraint::projective
