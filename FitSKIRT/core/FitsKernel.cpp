/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FitsKernel.hpp"

////////////////////////////////////////////////////////////////////

void FitsKernel::setupSelfBefore()
{
    ConvolutionKernel::setupSelfBefore();

    // Import the kernel
    load(this, _filename);
}

////////////////////////////////////////////////////////////////////
