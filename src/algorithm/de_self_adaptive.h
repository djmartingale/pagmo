/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef PAGMO_ALGORITHM_DE_SELF_ADAPTIVE_H
#define PAGMO_ALGORITHM_DE_SELF_ADAPTIVE_H

#include <string>

#include "../config.h"
#include "../population.h"
#include "../serialization.h"
#include "base.h"

namespace pagmo { namespace algorithm {

/// Differential Evolution Algorithm - Self-Adaptive (2011)
/**
 *
 * \image html de.jpg "Differential Evolution block diagram."
 * \image latex de.jpg "Differential Evolution block diagram." width=5cm
 *
 * Since its creation, the original Differential Evolution (pagmo::algorithm::de) algorithm
 * has been modified several times and many improvements have been suggested. We thus provide in PaGMO, together with the
 * original version of the algorithm, a modern version of the algorithm, with self-adaptation of its 
 * parameters pagmo::algorithm::de::m_cr and pagmo::algorithm::de::m_f and some of the most used recombination variants.
 *
 * NOTE: when called on mixed-integer problems DE treats the integer part as fixed and optimizes
 * the continuous part.
 *
 * NOTE2: when called on stochastic optimization problems, DE changes the seed
 * at the end of each generation.
 *
 * NOTE3: the pagmo::population::individual_type::cur_v is also updated along DE as soon as a new chromosome is accepted.
 *
 *
 * @see http://sci2s.ugr.es/EAMHCO/pdfs/contributionsCEC11/05949732.pdf for the paper where some of the variants implemented in this
 * 'modern' de version are used.
 *
 * @author Dario Izzo (dario.izzo@googlemail.com)
 */

class __PAGMO_VISIBLE de_self_adaptive: public base
{
public:
	de_self_adaptive(int = 100, int = 2, int = 1, double = 1e-6, double = 1e-6, bool = true);
	base_ptr clone() const;
	void evolve(population &) const;
	std::string get_name() const;

protected:
	std::string human_readable_extra() const;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & const_cast<int &>(m_gen);
		ar & const_cast<int &>(m_variant);
		ar & const_cast<int &>(m_variant_adptv);
		ar & m_f;
		ar & m_cr;
		ar & const_cast<bool &>(m_restart);
	}
	
	// Number of generations.
	const int m_gen;
	
	// Weighting factor
	mutable std::vector<double> m_f;
	
	// Crossover probability
	mutable std::vector<double> m_cr;
	
	// Startegy
	const int m_variant;
	const int m_variant_adptv;
	const double m_ftol;
	const double m_xtol;

	// Resart option
	const bool m_restart;
};

}}

BOOST_CLASS_EXPORT_KEY(pagmo::algorithm::de_self_adaptive);

#endif // DE_SELF_ADAPTIVE_H