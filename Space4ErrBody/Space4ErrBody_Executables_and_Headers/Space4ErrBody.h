/*    Copyright (c) 2010-2017, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */


#ifndef SPACE4ERRBODY_OPTIMIZATION_HPP
#define SPACE4ERRBODY_OPTIMIZATION_HPP

#include <utility>
#include <vector>
#include <limits>


#include "pagmo/island.hpp"
#include "pagmo/io.hpp"
#include "pagmo/serialization.hpp"
#include "pagmo/problem.hpp"
#include "pagmo/types.hpp"

using namespace pagmo;
//using namespace pagmo::problem;

// Define the problem PaGMO-style
struct Space4ErrBody_Ballistic {

    // Empty constructor
    Space4ErrBody_Ballistic( ) { }

    //! Constructor that sets boundaries of independent variables.
    Space4ErrBody_Ballistic( std::vector< std::vector< double > >  &bounds,std::vector< double > &input_data,std::string &play );

    //! Calculate the fitness as a function of the parameter vector input_data
    std::vector<double>  fitness(const std::vector< double >  &x) const;

    //! Retrieve the allowable limits of the parameters to vary: pair
    //! containing minima and maxima of parameter values
    std::pair< std::vector< double >, std::vector< double > > get_bounds() const;

    //! Retrieve the name of the problem
    std::string get_name( ) const;



    //! Retrieve the number of objectives in problem, e.g. the size of the
    //! vector returned by the fitness function.
    //! The ballistic case:
    //!        4 objectives
    //!
    //!         dif_norm = sqrt(dif_lat^2 + dif_lon^2)
    //!         dif_lat  = lat_f_rad - lat_f_rad_calc
    //!         dif_lon  = lon_f_rad - lon_f_rad_calc
    //!         tof      = simulationEndEpoch_calc - simulationStartEpoch
    //!
    //! The size of the vector returned by the fitness function is then
    //!        4 rows by 1 column.
    std::vector< double >::size_type get_nobj() const
    {
        return 4u;
    }
    //std::vector< double >::size_type get_nec() const
   //{
    //    return 2u;
    //}
    //! Serialization function for Pagmo compatibility
    template <typename Archive>
    void serialize(Archive &ar)
    {
        ar(problemBounds_);
    }
private:

    const std::vector< std::vector< double > > problemBounds_;
    std::vector< double > input_data_;
    std::string play_;


};


//PAGMO_REGISTER_PROBLEM(pagmo::Space4ErrBody_Ballistic)

#endif // TUDAT_EXAMPLE_PAGMO_PROBLEM_PROPAGATION_TARGETING_HPP
