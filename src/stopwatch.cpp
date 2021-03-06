// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

#include "stopwatch.hpp"

namespace flexiblesusy {

Stopwatch::Stopwatch()
{
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::start()
{
   start_point = std::chrono::high_resolution_clock::now();
}

void Stopwatch::stop()
{
   stop_point = std::chrono::high_resolution_clock::now();
}

double Stopwatch::get_time_in_seconds()
{
   typedef std::chrono::duration<int,std::milli> milliseconds_t;
   milliseconds_t duration(std::chrono::duration_cast<milliseconds_t>(
                              stop_point - start_point));
   return duration.count() * 0.001;
}

} // namespace flexiblesusy
