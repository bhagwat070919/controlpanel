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

#ifndef CPSDATE_H_
#define CPSDATE_H_

#include "qcc/platform.h"

namespace ajn {
namespace services {

/**
 * A class to allow sending of a Date as a Property
 */
class CPSDate {
  public:

    /**
     * Constructor of a CPSDate.
     * @param day - day of date
     * @param month - month of date
     * @param year - year of date
     */
    CPSDate(uint16_t day, uint16_t month, uint16_t year);

    /**
     * Destructor of CPSDate
     */
    virtual ~CPSDate();

    /**
     * Get the day value of the date
     * @return day value
     */
    uint16_t getDay() const;

    /**
     * Set the day Value of the date
     * @param day value
     */
    void setDay(uint16_t day);

    /**
     * Get the Month value of the date
     * @return month value
     */
    uint16_t getMonth() const;

    /**
     * Set the Month value of the date
     * @param month value
     */
    void setMonth(uint16_t month);

    /**
     * Get the Year value of the date
     * @return year value
     */
    uint16_t getYear() const;

    /**
     * Set the Year value of the date
     * @param year value
     */
    void setYear(uint16_t year);

  private:

    /**
     * Day value of the Date
     */
    uint16_t m_Day;

    /**
     * Month value of the Date
     */
    uint16_t m_Month;

    /**
     * Year value of the Date
     */
    uint16_t m_Year;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CPSDATE_H_ */
