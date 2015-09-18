/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_LILACSAT_PLAN13_CC_H
#define INCLUDED_LILACSAT_PLAN13_CC_H

#include <lilacsat/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace lilacsat {

    /*!
     * \brief <+description of block+>
     * \ingroup lilacsat
     *
     */
    class LILACSAT_API plan13_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<plan13_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lilacsat::plan13_cc.
       *
       * To avoid accidental use of raw pointers, lilacsat::plan13_cc's
       * constructor is in a private implementation
       * class. lilacsat::plan13_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool enable, const std::string& tle1, const std::string& tle2, float lon, float lat, float height, float fc, float samp_rate, bool txrx, bool verbose);
    };

  } // namespace lilacsat
} // namespace gr

#endif /* INCLUDED_LILACSAT_PLAN13_CC_H */

