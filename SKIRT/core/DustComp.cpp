/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "DustComp.hpp"

////////////////////////////////////////////////////////////////////

void DustComp::setupSelfAfter()
{
    SimulationItem::setupSelfAfter();

    // calculate the normalization factor
    _nf = _normalization->normalizationFactor(_geometry, _mix);
}

////////////////////////////////////////////////////////////////////

int DustComp::dimension()
{
    return _geometry->dimension();
}

////////////////////////////////////////////////////////////////////

double DustComp::density(Position bfr) const
{
    return _nf * _geometry->density(bfr);
}

////////////////////////////////////////////////////////////////////

double DustComp::mass() const
{
    return _nf;  // geometry always has mass of one
}

////////////////////////////////////////////////////////////////////

double DustComp::SigmaX() const
{
    return _nf * _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double DustComp::SigmaY() const
{
    return _nf * _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double DustComp::SigmaZ() const
{
    return _nf * _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////