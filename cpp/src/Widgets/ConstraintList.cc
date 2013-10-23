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

#include "alljoyn/controlpanel/ConstraintList.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../ControlPanelConstants.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

#define TAG TAG_CONSTRAINTLIST

ConstraintList::ConstraintList() : m_PropertyType(UNDEFINED), m_GetDisplay(0)
{
}

ConstraintList::~ConstraintList()
{
}

void ConstraintList::setConstraintValue(uint16_t value)
{
    m_ConstraintValue.uint16Value = value;
    m_PropertyType = UINT16_PROPERTY;
}

void ConstraintList::setConstraintValue(int16_t value)
{
    m_ConstraintValue.int16Value = value;
    m_PropertyType = INT16_PROPERTY;
}

void ConstraintList::setConstraintValue(uint32_t value)
{
    m_ConstraintValue.uint32Value = value;
    m_PropertyType = UINT32_PROPERTY;
}

void ConstraintList::setConstraintValue(int32_t value)
{
    m_ConstraintValue.int32Value = value;
    m_PropertyType = INT32_PROPERTY;
}

void ConstraintList::setConstraintValue(uint64_t value)
{
    m_ConstraintValue.uint64Value = value;
    m_PropertyType = UINT64_PROPERTY;
}

void ConstraintList::setConstraintValue(int64_t value)
{
    m_ConstraintValue.int64Value = value;
    m_PropertyType = INT64_PROPERTY;
}

void ConstraintList::setConstraintValue(double value)
{
    m_ConstraintValue.doubleValue = value;
    m_PropertyType = DOUBLE_PROPERTY;
}

void ConstraintList::setConstraintValue(qcc::String const& value)
{
    m_ConstraintValueString = value;
    m_ConstraintValue.charValue = m_ConstraintValueString.c_str();
    m_PropertyType = STRING_PROPERTY;
}

ConstraintValue ConstraintList::getConstraintValue() const
{
    return m_ConstraintValue;
}

PropertyType ConstraintList::getPropertyType() const
{
    return m_PropertyType;
}

const std::vector<qcc::String>& ConstraintList::getDisplay() const
{
    return m_Display;
}

void ConstraintList::setDisplay(const std::vector<qcc::String>& display)
{
    m_Display = display;
}

GetStringFptr ConstraintList::getGetDisplay() const
{
    return m_GetDisplay;
}

void ConstraintList::setGetDisplay(GetStringFptr getDisplay)
{
    m_GetDisplay = getDisplay;
}

QStatus ConstraintList::fillConstraintArg(MsgArg& val, uint16_t languageIndx, PropertyType propertyType)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (m_PropertyType != propertyType) {
        if (logger)
            logger->warn(TAG, "Could not fill the Constraint Arg. PropertyTypes do not match");
        return ER_FAIL;
    }

    if (!m_Display.size() > languageIndx && !m_GetDisplay) {
        if (logger)
            logger->warn(TAG, "Could not fill the Constraint Arg. Display is not set");
        return ER_FAIL;
    }

    QStatus status;
    MsgArg* valueArg = new MsgArg();

    switch (propertyType) {
    case UINT16_PROPERTY:
        status = valueArg->Set(AJPARAM_UINT16.c_str(), m_ConstraintValue.uint16Value);
        break;

    case INT16_PROPERTY:
        status = valueArg->Set(AJPARAM_INT16.c_str(), m_ConstraintValue.int16Value);
        break;

    case UINT32_PROPERTY:
        status = valueArg->Set(AJPARAM_UINT32.c_str(), m_ConstraintValue.uint32Value);
        break;

    case INT32_PROPERTY:
        status = valueArg->Set(AJPARAM_INT32.c_str(), m_ConstraintValue.int32Value);
        break;

    case UINT64_PROPERTY:
        status = valueArg->Set(AJPARAM_UINT64.c_str(), m_ConstraintValue.uint64Value);
        break;

    case INT64_PROPERTY:
        status = valueArg->Set(AJPARAM_INT64.c_str(), m_ConstraintValue.int64Value);
        break;

    case DOUBLE_PROPERTY:
        status = valueArg->Set(AJPARAM_DOUBLE.c_str(), m_ConstraintValue.doubleValue);
        break;

    case STRING_PROPERTY:
        status = valueArg->Set(AJPARAM_STR.c_str(), m_ConstraintValue.charValue);
        break;

    default:
        status = ER_BUS_BAD_SIGNATURE;
        break;
    }

    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal Constraint Value");
        delete valueArg;
        return status;
    }

    const char* display = m_GetDisplay ? m_GetDisplay(languageIndx) : m_Display[languageIndx].c_str();
    status = val.Set(AJPARAM_STRUCT_VAR_STR.c_str(), valueArg, display);

    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal Constraint Value");
        delete valueArg;
        return status;
    }
    return status;
}

} /* namespace services */
} /* namespace ajn */
