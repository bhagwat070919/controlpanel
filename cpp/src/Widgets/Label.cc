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

#include "alljoyn/controlpanel/Label.h"
#include "../ControlPanelConstants.h"
#include "../BusObjects/LabelBusObject.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Label::Label(qcc::String const& name) : Widget(name, TAG_LABEL_WIDGET), m_LabelWidgetGetLabel(0)
{
}

Label::~Label()
{
}

WidgetBusObject* Label::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                              uint16_t langIndx, QStatus& status)
{
    return new LabelBusObject(bus, objectPath, langIndx, status, this);
}

const std::vector<qcc::String>& Label::getLabel() const
{
    return m_LabelWidgetLabel;
}

void Label::setLabel(const std::vector<qcc::String>& label)
{
    m_LabelWidgetLabel = label;
}

GetStringFptr Label::getGetLabel() const
{
    return m_LabelWidgetGetLabel;
}

void Label::setGetLabel(GetStringFptr getLabel)
{
    m_LabelWidgetGetLabel = getLabel;
}

QStatus Label::fillLabelArg(MsgArg& val, uint16_t languageIndx)
{
    if (!m_LabelWidgetLabel.size() > languageIndx && !m_LabelWidgetGetLabel)
        return ER_BUS_PROPERTY_VALUE_NOT_SET;

    return val.Set(AJPARAM_STR.c_str(), m_LabelWidgetGetLabel ? m_LabelWidgetGetLabel(languageIndx) :
                   m_LabelWidgetLabel[languageIndx].c_str());
}

} /* namespace services */
} /* namespace ajn */
