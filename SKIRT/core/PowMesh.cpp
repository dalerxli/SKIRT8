/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "PowMesh.hpp"
#include "NR.hpp"

////////////////////////////////////////////////////////////////////

Array PowMesh::mesh() const
{
    Array tv;
    if (numBins()>1) NR::buildPowerLawGrid(tv, 0.0, 1.0, numBins(), _ratio);
    else NR::buildLinearGrid(tv, 0.0, 1.0, 1);
    return tv;
}

//////////////////////////////////////////////////////////////////////
