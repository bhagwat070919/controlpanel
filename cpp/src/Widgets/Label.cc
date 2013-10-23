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

using namespace ajn;
using namespace services;
using namespace cpsConsts;

Label::Label(qcc::String name) : Widget(name, TAG_LABEL_WIDGET), m_GetLabelForLabel(0)
{
}

Label::~Label()
{
}

GetStringFptr Label::getGetLabel() const
{
    return m_GetLabelForLabel;
}

void Label::setGetLabel(GetStringFptr getLabel)
{
    m_GetLabelForLabel = getLabel;
}

const std::vector<qcc::String>& Label::getLabel() const
{
    return m_LabelForLabel;
}

void Label::setLabel(const std::vector<qcc::String>& label)
{
    m_LabelForLabel = label;
}

QStatus Label::getLabelForArg(MsgArg& val, int16_t languageIndx)
{
    if (!m_LabelForLabel.size() & !m_GetLabelForLabel)
        return ER_BUS_PROPERTY_VALUE_NOT_SET;

    return val.Set(AJPARAM_STR.c_str(), m_GetLabelForLabel ? m_GetLabelForLabel(languageIndx) :
                   m_LabelForLabel[languageIndx].c_str());
}

WidgetBusObject* Label::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                              uint16_t langIndx, QStatus status)
{
    return new LabelBusObject(bus, objectPath, langIndx, status, this);
}
