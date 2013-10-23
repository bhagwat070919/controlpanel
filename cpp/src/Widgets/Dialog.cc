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

#include "alljoyn/controlpanel/Dialog.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/DialogBusObject.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Dialog::Dialog(qcc::String const& name) : RootWidget(name, TAG_DIALOG_WIDGET),
    m_NumActions(0), m_GetMessage(0), m_GetLabelAction1(0),
    m_GetLabelAction2(0), m_GetLabelAction3(0)
{
}

Dialog::~Dialog()
{
}

WidgetBusObject* Dialog::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                               uint16_t langIndx, QStatus& status)
{
    return new DialogBusObject(bus, objectPath, langIndx, status, this);
}

const uint16_t Dialog::getNumActions() const
{
    return m_NumActions;
}

void Dialog::setNumActions(const uint16_t numActions)
{
    m_NumActions = numActions;
}

const std::vector<qcc::String>& Dialog::getMessage() const
{
    return m_Message;
}

void Dialog::setMessage(const std::vector<qcc::String>& message)
{
    m_Message = message;
}

GetStringFptr Dialog::getGetMessage() const
{
    return m_GetMessage;
}

void Dialog::setGetMessage(GetStringFptr getMessage)
{
    m_GetMessage = getMessage;
}

const std::vector<qcc::String>& Dialog::getLabelAction1() const
{
    return m_LabelAction1;
}

void Dialog::setLabelAction1(const std::vector<qcc::String>& labelAction1)
{
    m_LabelAction1 = labelAction1;
}

GetStringFptr Dialog::getGetLabelAction1() const
{
    return m_GetLabelAction1;
}

void Dialog::setGetLabelAction1(GetStringFptr getLabelAction1)
{
    m_GetLabelAction1 = getLabelAction1;
}

const std::vector<qcc::String>& Dialog::getLabelAction2() const
{
    return m_LabelAction2;
}

void Dialog::setLabelAction2(const std::vector<qcc::String>& labelAction2)
{
    m_LabelAction2 = labelAction2;
}

GetStringFptr Dialog::getGetLabelAction2() const
{
    return m_GetLabelAction2;
}

void Dialog::setGetLabelAction2(GetStringFptr getLabelAction2)
{
    m_GetLabelAction2 = getLabelAction2;
}

const std::vector<qcc::String>& Dialog::getLabelAction3() const
{
    return m_LabelAction3;
}

void Dialog::setLabelAction3(const std::vector<qcc::String>& labelAction3)
{
    m_LabelAction3 = labelAction3;
}

QStatus Dialog::fillMessageArg(MsgArg& val, uint16_t languageIndx)
{
    if (!m_Message.size() > languageIndx && !m_GetMessage)
        return ER_BUS_PROPERTY_VALUE_NOT_SET;

    return val.Set(AJPARAM_STR.c_str(), m_GetMessage ? m_GetMessage(languageIndx) :
                   m_Message[languageIndx].c_str());
}

QStatus Dialog::fillNumActionArg(MsgArg& val, uint16_t languageIndx)
{
    if (!m_NumActions)
        return ER_BUS_PROPERTY_VALUE_NOT_SET;

    return val.Set(AJPARAM_UINT16.c_str(), m_NumActions);
}

GetStringFptr Dialog::getGetLabelAction3() const
{
    return m_GetLabelAction3;
}

void Dialog::setGetLabelAction3(GetStringFptr getLabelAction3)
{
    m_GetLabelAction3 = getLabelAction3;
}

QStatus Dialog::fillOptParamsArg(MsgArg& val, uint16_t languageIndx)
{
    QStatus status;
    MsgArg* optParams = new MsgArg[OPT_PARAM_KEYS::NUM_OPT_PARAMS];

    size_t optParamIndx = 0;

    status = Widget::fillOptParamsArg(optParams, languageIndx, optParamIndx);
    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal optParams");
        delete[] optParams;
        return status;
    }

    if (m_LabelAction1.size() > languageIndx || m_GetLabelAction1) {
        MsgArg* labelArg = new MsgArg(AJPARAM_STR.c_str(), m_GetLabelAction1 ?
                                      m_GetLabelAction1(languageIndx) : m_LabelAction1[languageIndx].c_str());

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::LABEL_ACTION1, labelArg)) != ER_OK) {
            delete labelArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_LabelAction2.size() > languageIndx || m_GetLabelAction2) {
        MsgArg* labelArg = new MsgArg(AJPARAM_STR.c_str(), m_GetLabelAction2 ?
                                      m_GetLabelAction2(languageIndx) : m_LabelAction2[languageIndx].c_str());

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::LABEL_ACTION2, labelArg)) != ER_OK) {
            delete labelArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_LabelAction3.size() > languageIndx || m_GetLabelAction3) {
        MsgArg* labelArg = new MsgArg(AJPARAM_STR.c_str(), m_GetLabelAction3 ?
                                      m_GetLabelAction3(languageIndx) : m_LabelAction3[languageIndx].c_str());

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::LABEL_ACTION3, labelArg)) != ER_OK) {
            delete labelArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    return val.Set(AJPARAM_ARRAY_DICT_UINT16_VAR.c_str(), optParamIndx, optParams);
}

bool Dialog::executeActionNotDefined()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->warn(TAG, "Could not execute this Action. It is not defined");
    return false;
}

} /* namespace services */
} /* namespace ajn */
