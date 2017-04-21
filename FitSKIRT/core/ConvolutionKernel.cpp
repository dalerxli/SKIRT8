/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "ConvolutionKernel.hpp"

////////////////////////////////////////////////////////////////////

void ConvolutionKernel::setupSelfBefore()
{
    SimulationItem::setupSelfBefore();
}

////////////////////////////////////////////////////////////////////

void ConvolutionKernel::setupSelfAfter()
{
    SimulationItem::setupSelfAfter();

    (*this) /= (*this).sum();
}

////////////////////////////////////////////////////////////////////
