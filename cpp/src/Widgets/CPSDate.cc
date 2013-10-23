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

#include "alljoyn/controlpanel/CPSDate.h"

namespace ajn {
namespace services {

CPSDate::CPSDate(uint16_t day, uint16_t month, uint16_t year) :
    m_Day(day), m_Month(month), m_Year(year)
{
}

CPSDate::~CPSDate()
{
}

uint16_t CPSDate::getDay() const
{
    return m_Day;
}

void CPSDate::setDay(uint16_t day)
{
    m_Day = day;
}

uint16_t CPSDate::getMonth() const
{
    return m_Month;
}

void CPSDate::setMonth(uint16_t month)
{
    m_Month = month;
}

uint16_t CPSDate::getYear() const
{
    return m_Year;
}

void CPSDate::setYear(uint16_t year)
{
    m_Year = year;
}

} /* namespace services */
} /* namespace ajn */
