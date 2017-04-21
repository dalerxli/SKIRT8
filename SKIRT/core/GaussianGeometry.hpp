/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef GAUSSIANGEOMETRY_HPP
#define GAUSSIANGEOMETRY_HPP

#include "SepAxGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The GaussianGeometry class is a subclass of the SepAxGeometry class, and
    describes axisymmetric geometries characterized by a gaussian distribution in the
    radial and the vertical direction, \f[ \rho(R,z) = \rho_0\,\exp\left( -\frac{R^2}{2\sigma^2}
    -\frac{z^2}{2q^2\sigma^2}\right) \f] The ratio of the dispersion in the radial and vertical
    direction is characterized by the flattening parameter \f$q\f$. This geometry
    contains two free parameters: the radial dispersion \f$\sigma\f$ and the flattening parameter
    \f$q\f$. */
class GaussianGeometry : public SepAxGeometry
{
    ITEM_CONCRETE(GaussianGeometry, SepAxGeometry, "an axisymmetric Gaussian geometry")

    PROPERTY_DOUBLE(dispersion, "the dispersion parameter σ")
        ATTRIBUTE_QUANTITY(dispersion, "length")
        ATTRIBUTE_MIN_VALUE(dispersion, "]0")

    PROPERTY_DOUBLE(flattening, "the flattening parameter q")
        ATTRIBUTE_MIN_VALUE(flattening, "]0")
        ATTRIBUTE_MAX_VALUE(flattening, "1]")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function calulates some frequently used values. The central density \f$\rho_0\f$ is
        set by the normalization condition that the total mass equals one, which is straightforward
        for a gaussian distribution, \f[ \rho_0 = \frac{1}{(2\pi)^{3/2}\,q\,\sigma^3} \f] */
    void setupSelfBefore() override;

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho(R,z)\f$ at the cylindrical radius \f$R\f$ and
        height \f$z\f$. It just implements the analytical formula. */
    double density(double R, double z) const override;

    /** This function returns the cylindrical radius \f$R\f$ of a random position drawn from a
        gaussian density distribution. For any axisymmetric geometry in which the density is
        separable in \f$R\f$ and \f$z\f$, such as for the current geometry, such a value can be
        generated by picking a uniform deviate \f${\cal{X}}\f$ and solving the equation \f[
        {\cal{X}} = 2\pi \int_0^R \rho_R(R')\, R'\, {\text{d}}R' \f] for \f$R\f$, where
        \f$\rho_z(z)\f$ is the radial part of the density.  Substituting
        the gaussian radial profile into this equation, we obtain \f[ {\cal{X}} = 1 - \exp
        \left(-\frac{R^2}{2\sigma^2} \right) \f] Solving for \f$R\f$ we obtain \f[ R =
        \sigma\,\sqrt{-2\ln(1-{\cal{X}})} \f] We can simplify this expression even more by noting
        that, if \f${\cal{X}}\f$ is a uniform deviate, \f$1-{\cal{X}}\f$ also is a uniform deviate,
        so we can also take the expression \f[ R = \sigma \sqrt{-2\ln{\cal{X}}} \f] */
    double randomCylRadius() const override;

    /** This function returns the height \f$z\f$ of a random position drawn from a gaussian density
        distribution. For any axisymmetric geometry in which the density is separable in \f$R\f$ and
        \f$z\f$, such as for the current geometry, such a value can be generated by picking a
        uniform deviate \f${\cal{X}}\f$ and solving the equation \f[ {\cal{X}} = \int_{-\infty}^z
        \rho_z(z')\, {\text{d}}z' \f] for \f$z\f$, where \f$\rho_z(z)\f$ is the vertical part of
        the density. As the resulting vertical distribution \f$\rho_z(z)\f$ is
        just a one-dimensional gaussian distribution with dispersion \f$q\,\sigma\f$, we just
        determine a random gaussian deviate \f${\cal{X}}\f$ through the RandomNumber::gauss()
        function and multiply this value with \f$q\,\sigma\f$ to obtain our random \f$z\f$. */
    double randomZ() const override;

    /** This function returns the surface mass density along a line in the equatorial plane
        starting at the centre of the coordinate system, i.e. \f[ \Sigma_R =
        \int_0\infty \rho(R,0)\,{\text{d}}R. \f] For a gaussian geometry we easily find \f[
        \Sigma_R = \frac{1}{4\pi\,q\,\sigma^2}. \f] */
    double SigmaR() const override;

    /** This function returns the surface mass density along the Z-axis, i.e.
        the integration of the mass density along the entire Z-axis, \f[
        \Sigma_Z = \int_{-\infty}^\infty \rho(0,0,z)\, {\text{d}}z.\f] For a gaussian geometry
        we easily find \f[ \Sigma_Z = \frac{1}{2\pi\,\sigma^2}. \f] */
    double SigmaZ() const override;

    //======================== Data Members ========================

private:
    // aliases to discoverable data members for ease of notation and backwards compatibility
    const double& _sigma{_dispersion};
    const double& _q{_flattening};

    // data members initialized during setup
    double _rho0{0.};
};

////////////////////////////////////////////////////////////////////

#endif
