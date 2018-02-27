/**
* @version    GrPPI v0.3
* @copyright    Copyright (C) 2017 Universidad Carlos III de Madrid. All rights reserved.
* @license    GNU/GPL, see LICENSE.txt
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License in LICENSE.txt
* also available in <http://www.gnu.org/licenses/gpl.html>.
*
* See COPYRIGHT.txt for copyright notices and details.
*/

#ifndef GRPPI_FF_DETAIL_ORDERED_STREAM_REDUCE_H
#define GRPPI_FF_DETAIL_ORDERED_STREAM_REDUCE_H

#include "reduce_nodes.h"

#include <ff/farm.hpp>


namespace grppi {

namespace detail_ff {

/**
 \brief Ordered stream reduce for FastFlow.
 */
template <typename Item, typename Reducer, typename CombineOp>
class ordered_stream_reduce : public ff::ff_ofarm {
public:
  ordered_stream_reduce(Reducer && red_obj, int num_workers);

private:
  std::vector<ff_node*> workers_;

  using emitter_type = reduce_emitter<Item,Reducer>;
  std::unique_ptr<emitter_type> p_emitter_;
};

template <typename Item, typename Reducer, typename Combiner>
ordered_stream_reduce<Item,Reducer,Combiner>::ordered_stream_reduce(
    Reducer && red_obj, 
    int num_workers) 
:
    ff::ff_ofarm{false, DEF_IN_BUFF_ENTRIES, DEF_OUT_BUFF_ENTRIES, true, num_workers},
    workers_{},
    p_emitter_{std::make_unique<emitter_type>(red_obj.window_size(), red_obj.offset())} 
{
  for(int i=0; i<num_workers; ++i) {
    reduce_worker<Item,Combiner> * p_worker =
        new reduce_worker<Item,Combiner>{red_obj.combiner()};
    workers_.push_back(p_worker);
  }

  add_workers(workers_);
  setEmitterF(p_emitter_.get());
}


} // namespace detail_ff

} // namespace grppi

#endif