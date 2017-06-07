/**
* @version		GrPPI v0.1
* @copyright		Copyright (C) 2017 Universidad Carlos III de Madrid. All rights reserved.
* @license		GNU/GPL, see LICENSE.txt
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

#ifndef GRPPI_SEQ_POLICY_H
#define GRPPI_SEQ_POLICY_H

namespace grppi{

/** @brief Set the execution mode to sequencial */
struct sequential_execution {
  private:
    bool ordering = true;
    int num_threads=1;
    bool lockfree = false;
  public:
    /** @brief set num_threads to 1 in order to sequential execution */
    sequential_execution(){};

    //Empty functions. Only for potability among framewoks 
    inline bool is_lockfree(){ return false;}
    inline bool is_ordered(){ return true;}
    inline void set_lockfree(bool value){ }
    inline void set_ordered(bool value){ }
    inline void set_num_threads(int _nthreads){ }
    inline int get_num_threads() const{ return 1;}

};

} // end namespace grppi

#endif