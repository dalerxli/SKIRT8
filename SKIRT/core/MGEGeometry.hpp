/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef MGEGEOMETRY_HPP
#define MGEGEOMETRY_HPP

#include "AxGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The MGEGeometry class is a subclass of the AxGeometry class, and describes
    axisymmetric geometries characterized by a combination of gaussian distributions in the
    radial and the vertical direction, \f[ \rho(R,z) = \sum_j\rho_{j,0}\,\exp\left(
    -\frac{R^2}{2\sigma_j^2} -\frac{z^2}{2q_j^2\sigma_j^2}\right) \f] Using a MGE, one can
    reconstruct a large variety of stellar geometries; see for example Emsellem, Monnet & Bacon
    (1994, A&A, 285, 723), Emsellem et al. (1994, A&A, 285, 739) and Cappellari (2002, MNRAS, 333,
    400). */
class MGEGeometry : public AxGeometry
{
    ITEM_CONCRETE(MGEGeometry, AxGeometry, "a multi-gaussian expansion (MGE) geometry")

    PROPERTY_STRING(filename, "the name of the file with the MGE expansion parameters")

    PROPERTY_DOUBLE(pixelscale, "the scale of the MGE-expanded image (length per pixel)")
        ATTRIBUTE_QUANTITY(pixelscale, "length")
        ATTRIBUTE_MIN_VALUE(pixelscale, "]0")

    PROPERTY_DOUBLE(inclination, "the inclination of the system")
        ATTRIBUTE_QUANTITY(inclination, "posangle")
        ATTRIBUTE_MIN_VALUE(inclination, "[0")
        ATTRIBUTE_MAX_VALUE(inclination, "90 deg]")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function reads in a file with the result of a multi-Gaussian expansion of an image on
        the sky. The file should contain three columns, with the first column the total count
        \f$N_j\f$ of the \f$j\f$'th component, the second column the scalelength \f$\sigma_j\f$ in
        pixel units and the third column the apparent flattening \f$q'_j\f$ on the plane of the
        sky. Apart from this file, the function needs the physical pixel scale (e.g. in pc/pix)
        of the images that have been used for the MGE decomposition and the inclination of the
        system. From these data, the function calculates for each of the components the
        normalized mass contribution \f[ M_j = \frac{N_j}{\sum_{j'} N_{j'}}, \f] the scalelength
        \f$\sigma_j\f$ in physical units and the actual flattening \f$q_j\f$ of each of the
        components. In particular, the actual flattening is calculated from the apparent flattening
        and inclination of the system using the relation \f[ q_j =
        \frac{\sqrt{{q'}_j^2-\cos^2i}}{\sin i} \f] */
    void setupSelfBefore() override;

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho(R,z)\f$ at the cylindrical radius \f$R\f$ and
        height \f$z\f$. It just sums the contribution of the different MGE components. */
    double density(double R, double z) const override;

    /** This pure virtual function generates a random position from the geometry, by
        drawing a random point from the three-dimensional probability density \f$p({\bf{r}})\,
        {\text{d}}{\bf{r}} = \rho({\bf{r}})\, {\text{d}}{\bf{r}}\f$. In the case of an MGE
        component, first a random component is chosen according to the finite probability \f$p_j =
        M_j\f$. Once this component is chosen, a random position \f${\bf{r}} = (x,y,z)\f$ is chosen
        by choosing three random numbers \f$(X_1,X_2,X_3)\f$ from a gaussian distribution and
        setting \f[ \begin{split} x &= \sigma_j\, X_1 \\ y &= \sigma_j \, X_2 \\ z &= q_j\,
        \sigma_j\, X_3 \end{split} \f] */
    Position generatePosition() const override;

    /** This function returns the radial surface density, i.e. the integration of the density
        along a line in the equatorial plane starting at the centre of the coordinate system,
        \f[ \Sigma_R = \int_0\infty \rho(R,0)\,{\text{d}}R. \f]
        For the MGE geometry we find \f[ \Sigma_R = \sum_j \rho_{0,j} \int_0^\infty
        \exp\left(-\frac{R^2}{2\sigma_j^2}\right) {\text{d}}R = \frac{1}{4\pi} \sum_j
        \frac{M_j}{q_j\,\sigma_j^2}. \f] */
    double SigmaR() const override;

    /** This function returns the Z-axis surface density, i.e. the integration of the density
        along the entire Z-axis, \f[ \Sigma_Z = \int_{-\infty}^\infty \rho(0,0,z)\,{\text{d}}z. \f]
        For the MGE geometry we find \f[ \Sigma_Z = \sum_j \rho_{0,j} \int_{-\infty}^\infty
        \exp\left(-\frac{z^2}{2 q_j^2 \sigma_j^2}\right) {\text{d}}z = \frac{1}{2\pi} \sum_j
        \frac{M_j}{\sigma_j^2}. \f] */
    double SigmaZ() const override;

    //======================== Data Members ========================

private:
    // data members initialized during setup
    int _Ncomp{0};
    std::vector<double> _Mv;
    std::vector<double> _Mcumv;
    std::vector<double> _sigmav;
    std::vector<double> _qv;
};

////////////////////////////////////////////////////////////////////

#endif
