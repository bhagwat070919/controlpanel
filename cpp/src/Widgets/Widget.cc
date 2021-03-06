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

#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/Widget.h>
#include "../ControlPanelConstants.h"
#include "../BusObjects/WidgetBusObject.h"

#ifndef UINT32_MAX
#define UINT32_MAX      (4294967295U)
#endif
#define STATE_ENABLED 0x01
#define STATE_WRITABLE 0x02

namespace ajn {
namespace services {
using namespace cpsConsts;

Widget::Widget(qcc::String const& name, qcc::String const& tag) : m_Name(name), m_IsSecured(false), m_States(0),
    m_GetEnabled(0), m_GetWritable(0), m_BgColor(UINT32_MAX), m_GetBgColor(0), m_GetLabel(0), TAG(tag)
{
}

Widget::~Widget()
{

}

qcc::String const& Widget::getWidgetName()
{
    return m_Name;
}

const uint16_t Widget::getInterfaceVersion() const
{
    if (!m_BusObjects.size())
        return 1;
    return m_BusObjects[0]->getInterfaceVersion();
}

void Widget::setIsSecured(bool secured)
{
    m_IsSecured = secured;
}

bool Widget::getIsSecured()
{
    return m_IsSecured;
}

void Widget::setEnabled(bool enabled)
{
    if (enabled)
        m_States = m_States | STATE_ENABLED;
    else
        m_States = m_States & ~STATE_ENABLED;
}

GetBoolFptr Widget::getGetEnabled() const
{
    return m_GetEnabled;
}

void Widget::setGetEnabled(GetBoolFptr getEnabled)
{
    m_GetEnabled = getEnabled;
}

void Widget::setWritable(bool writable)
{
    if (writable)
        m_States = m_States | STATE_WRITABLE;
    else
        m_States = m_States & ~STATE_WRITABLE;
}

void Widget::setGetWritable(GetBoolFptr getWritable)
{
    m_GetWritable = getWritable;
}

GetBoolFptr Widget::getGetWritable() const
{
    return m_GetWritable;
}

uint32_t Widget::getStates() const
{
    return m_States;
}

void Widget::setStates(uint8_t enabled, uint8_t writable)
{
    setEnabled(enabled);
    setWritable(writable);
}

uint32_t Widget::getBgColor() const
{
    return m_BgColor;
}

void Widget::setBgColor(uint32_t bgColor)
{
    this->m_BgColor = bgColor;
}

GetUint32Fptr Widget::getGetBgColor() const
{
    return m_GetBgColor;
}

void Widget::setGetBgColor(GetUint32Fptr getBgColor)
{
    m_GetBgColor = getBgColor;
}

const std::vector<qcc::String>& Widget::getLabel() const
{
    return m_Label;
}

void Widget::setLabel(const std::vector<qcc::String>& label)
{
    m_Label = label;
}

GetStringFptr Widget::getGetLabel() const
{
    return m_GetLabel;
}

void Widget::setGetLabel(GetStringFptr getLabel)
{
    m_GetLabel = getLabel;
}

const std::vector<uint16_t>& Widget::getHints() const
{
    return m_Hints;
}

void Widget::setHints(const std::vector<uint16_t>& hints)
{
    m_Hints = hints;
}

QStatus Widget::registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (!bus) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is NULL");
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is not started or not connected");
        return ER_BAD_ARG_1;
    }

    QStatus status = ER_OK;
    const std::vector<qcc::String>& languages = languageSet.getLanguages();
    qcc::String newObjectPathSuffix = isRoot ? objectPathSuffix : objectPathSuffix + "/" + m_Name;
    for (size_t indx = 0; indx < languages.size(); indx++) {
        qcc::String objectPath = objectPathPrefix + languages[indx] + newObjectPathSuffix;
        WidgetBusObject* busObject = createWidgetBusObject(bus, objectPath, indx, status);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not Create BusObject");
            delete busObject;
            return status;
        }
        status = bus->RegisterBusObject(*busObject);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not register BusObject");
            delete busObject;
            return status;
        }
        m_BusObjects.push_back(busObject);
    }
    return status;
}

QStatus Widget::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (!bus) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is NULL");
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is not started or not connected");
        return ER_BAD_ARG_1;
    }

    std::vector<WidgetBusObject*>::iterator it;
    for (it = m_BusObjects.begin(); it != m_BusObjects.end();) {
        bus->UnregisterBusObject(*(*it));
        delete *it;
        it = m_BusObjects.erase(it);
    }
    return ER_OK;
}

QStatus Widget::fillStatesArg(MsgArg& val, uint16_t languageIndx)
{
    if (m_GetEnabled)
        setEnabled(m_GetEnabled());
    if (m_GetWritable)
        setWritable(m_GetWritable());
    return val.Set(AJPARAM_UINT32.c_str(), m_States);
}

QStatus Widget::fillOptParamsArg(MsgArg& val, uint16_t languageIndx)
{
    QStatus status;
    MsgArg* optParams = new MsgArg[OPT_PARAM_KEYS::NUM_OPT_PARAMS];
    size_t optParamIndx = 0;

    status = fillOptParamsArg(optParams, languageIndx, optParamIndx);
    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal optParams");
        delete[] optParams;
        return status;
    }

    return val.Set(AJPARAM_ARRAY_DICT_UINT16_VAR.c_str(), optParamIndx, optParams);
}

QStatus Widget::fillOptParamsArg(MsgArg* optParams, uint16_t languageIndx, size_t& optParamIndx)
{
    QStatus status = ER_OK;

    if (m_Label.size() > languageIndx || m_GetLabel) {
        MsgArg* labelArg = new MsgArg(AJPARAM_STR.c_str(), m_GetLabel ?
                                      m_GetLabel(languageIndx) : m_Label[languageIndx].c_str());

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::LABEL_KEY, labelArg)) != ER_OK) {
            delete labelArg;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_BgColor != UINT32_MAX || m_GetBgColor) {
        MsgArg* bgColorArg = new MsgArg(AJPARAM_UINT32.c_str(), m_GetBgColor ?
                                        m_GetBgColor() : m_BgColor);

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::BGCOLOR_KEY, bgColorArg)) != ER_OK) {
            delete bgColorArg;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_Hints.size()) {
        MsgArg* hintsArg = new MsgArg(AJPARAM_ARRAY_UINT16.c_str(),
                                      m_Hints.size(), m_Hints.data());
        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::HINT_KEY, hintsArg)) != ER_OK) {
            delete hintsArg;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }
    return status;
}

QStatus Widget::SendPropertyChangedSignal()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus status;

    for (size_t indx = 0; indx < m_BusObjects.size(); indx++) {
        status = m_BusObjects[indx]->SendPropertyChangedSignal();
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not send Property Changed Signal");
            return status;
        }
    }
    return status;
}

} /* namespace services */
} /* namespace ajn */
