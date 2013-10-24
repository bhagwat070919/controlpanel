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

#include <alljoyn/controlpanel/CPSTime.h>

namespace ajn {
namespace services {

CPSTime::CPSTime(uint16_t hour, uint16_t minute, uint16_t second) :
    m_Hour(hour), m_Minute(minute), m_Second(second)
{
}

CPSTime::~CPSTime()
{
}

uint16_t CPSTime::getHour() const
{
    return m_Hour;
}

void CPSTime::setHour(uint16_t hour)
{
    m_Hour = hour;
}

uint16_t CPSTime::getMinute() const
{
    return m_Minute;
}

void CPSTime::setMinute(uint16_t minute)
{
    m_Minute = minute;
}

uint16_t CPSTime::getSecond() const
{
    return m_Second;
}

void CPSTime::setSecond(uint16_t second)
{
    m_Second = second;
}

} /* namespace services */
} /* namespace ajn */
