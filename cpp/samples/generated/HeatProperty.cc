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

#include "HeatProperty.h"
#include "ControlPanelProvided.h"

namespace ajn {
namespace services {

HeatProperty::HeatProperty(qcc::String name, PropertyType propertyType) :
    Property(name, propertyType)
{

}

HeatProperty::~HeatProperty()
{

}

QStatus HeatProperty::setValue(uint16_t value)
{
    setuint16Var(value);
    return ER_OK;
}

} /* namespace services */
} /* namespace ajn */
