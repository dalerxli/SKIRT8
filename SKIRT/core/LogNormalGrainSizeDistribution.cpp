/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "LogNormalGrainSizeDistribution.hpp"
#include "FatalError.hpp"

////////////////////////////////////////////////////////////////////

double LogNormalGrainSizeDistribution::dnda(double a) const
{
    double x = log(a/_centroid) / _width;
    return proportionalityFactor() / a * exp( -0.5*x*x );
}

////////////////////////////////////////////////////////////////////
