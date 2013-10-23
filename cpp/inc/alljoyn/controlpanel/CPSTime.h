/******************************************************************************
 * Copyright 2013, Qualcomm Innovation Center, Inc.
 *
 *    All rights reserved.
 *    This file is licensed under the 3-clause BSD license in the NOTICE.txt
 *    file for this project. A copy of the 3-clause BSD license is found at:
 *
 *        http://opensource.org/licenses/BSD-3-Clause.
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the license is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the license for the specific language governing permissions and
 *    limitations under the license.
 ******************************************************************************/

#ifndef CPSTIME_H_
#define CPSTIME_H_

namespace ajn {
namespace services {

#include "qcc/platform.h"

/**
 * A class to allow sending of a Time as a Property
 */
class CPSTime {
  public:

    /**
     * Constructor of a CPSTime.
     * @param hour - hour of date
     * @param minute - minute of date
     * @param second - second of date
     */
    CPSTime(uint16_t hour, uint16_t minute, uint16_t second);

    /**
     * Destructor of CPSTime
     */
    virtual ~CPSTime();

    /**
     * Get the hour value of the date
     * @return hour value
     */
    uint16_t getHour() const;

    /**
     * Set the hour Value of the date
     * @param hour value
     */
    void setHour(uint16_t hour);

    /**
     * Get the Minute value of the date
     * @return minute value
     */
    uint16_t getMinute() const;

    /**
     * Set the Minute value of the date
     * @param minute value
     */
    void setMinute(uint16_t minute);

    /**
     * Get the Second value of the date
     * @return second value
     */
    uint16_t getSecond() const;

    /**
     * Set the Second value of the date
     * @param second value
     */
    void setSecond(uint16_t second);

  private:

    /**
     * Hour value of the Time
     */
    uint16_t m_Hour;

    /**
     * Minute value of the Time
     */
    uint16_t m_Minute;

    /**
     * Second value of the Time
     */
    uint16_t m_Second;
};

} /* namespace services */
} /* namespace ajn */

#endif /* CPSTIME_H_ */
