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

#include "alljoyn/controlpanel/Widget.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include <iostream>

using namespace ajn;
using namespace services;
using namespace cpsConsts;

#ifndef UINT32_MAX
#define UINT32_MAX      (4294967295U)
#endif
#define STATE_ENABLED 0x01
#define STATE_WRITABLE 0x02

Widget::Widget(qcc::String const& name, qcc::String const& tag) : m_Name(name)
{
	m_IsSecured = false;
	m_InterfaceVersion = 1;
	m_States = 0;
	m_GetEnabled = 0;
	m_GetWritable = 0;
	m_GetLabel = 0;
	m_BgColor = UINT32_MAX;
	m_GetBgColor = 0;
}

QStatus Widget::registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
		qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot)
{
	std::cout << "Prefix, Suffix, name: " << objectPathPrefix.c_str() << " "
		<< objectPathSuffix.c_str() << " " << m_Name.c_str() << std::endl;

	GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
	QStatus status;
	const std::vector<qcc::String>& languages = languageSet.getLanguages();
	qcc::String newObjectPathSuffix = isRoot? objectPathSuffix : objectPathSuffix + "/" + m_Name;
	for (size_t indx = 0; indx < languages.size(); indx++) {
		qcc::String objectPath = objectPathPrefix + languages[indx] + newObjectPathSuffix;
		std::cout << "ObjectPath is: " << objectPath.c_str() << std::endl;
		WidgetBusObject* busObject = createWidgetBusObject(bus, objectPath, indx, status);
		if (status != ER_OK) {
			if (logger)
				logger->warn(TAG, "Could not Create BusObject for Action");
			return status;
		}
		status = bus->RegisterBusObject(*busObject);
		if (status != ER_OK) {
			if (logger)
				logger->warn(TAG, "Could not register BusObject for Action");
			return status;
		}
		m_BusObjects.push_back(busObject);
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

qcc::String const& Widget::getWidgetName()
{
	return m_Name;
}

bool Widget::getIsSecured()
{
	return m_IsSecured;
}

void Widget::setEnabled(uint8_t enabled)
{
	if (enabled)
		m_States = m_States | STATE_ENABLED;
	else
		m_States = m_States & ~STATE_ENABLED;
}

void Widget::setWritable(uint8_t writeable)
{
	if (writeable)
		m_States = m_States | STATE_WRITABLE;
	else
		m_States = m_States & ~STATE_WRITABLE;
}

Widget::~Widget()
{

}

uint32_t Widget::getBgColor() const
{
	return m_BgColor;
}

void Widget::setBgColor(uint32_t bgColor)
{
	this->m_BgColor = bgColor;
}

GetBgColorFptr Widget::getGetBgColor() const
{
	return m_GetBgColor;
}

void Widget::setGetBgColor(GetBgColorFptr getBgColor)
{
	m_GetBgColor = getBgColor;
}

GetEnabledFptr Widget::getGetEnabled() const
{
	return m_GetEnabled;
}

void Widget::setGetEnabled(GetEnabledFptr getEnabled)
{
	m_GetEnabled = getEnabled;
}

GetLabelFptr Widget::getGetLabel() const
{
	return m_GetLabel;
}

void Widget::setGetLabel(GetLabelFptr getLabel)
{
	m_GetLabel = getLabel;
}

GetWritableFptr Widget::getGetWritable() const
{
	return m_GetWritable;
}

void Widget::setGetWritable(GetWritableFptr getWritable)
{
	m_GetWritable = getWritable;
}

const std::vector<uint16_t>& Widget::getHints() const
{
	return m_Hints;
}

void Widget::setHints(const std::vector<uint16_t>& hints)
{
	m_Hints = hints;
}

const uint16_t Widget::getInterfaceVersion() const
{
	return m_InterfaceVersion;
}

void Widget::setInterfaceVersion(uint16_t interfaceVersion)
{
	m_InterfaceVersion = interfaceVersion;
}

const std::vector<qcc::String>& Widget::getLabel() const
{
	return m_Label;
}

void Widget::setLabel(const std::vector<qcc::String>& label)
{
	m_Label = label;
}

void Widget::setIsSecured(bool secured)
{
	m_IsSecured = secured;
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

QStatus Widget::GetVersionForArg(MsgArg& val, int16_t languageIndx)
{
	return val.Set(AJPARAM_UINT16.c_str(), m_InterfaceVersion);
}

QStatus Widget::getStatesForArg(MsgArg& val, int16_t languageIndx)
{
	if (m_GetEnabled)
		setEnabled(m_GetEnabled());
	if (m_GetWritable)
		setWritable(m_GetWritable());
	return val.Set(AJPARAM_UINT32.c_str(), m_States);
}

QStatus Widget::getOptParamsForArg(MsgArg& val, int16_t languageIndx,
		MsgArg* optParams, int32_t& optParamIndx) //TODO Memory leak if set fails?
{
	QStatus status;

	if (m_Label.size() || m_GetLabel) {
		MsgArg* labelArg = new MsgArg(AJPARAM_STR.c_str(), m_GetLabel?
				m_GetLabel(languageIndx) : m_Label[languageIndx].c_str());

		CHECK_AND_RETURN(optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
				OPT_PARAM_KEYS::LABEL_KEY, labelArg));
		optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
	}

	if (m_BgColor != UINT32_MAX || m_GetBgColor) {
		MsgArg* bgColorArg = new MsgArg(AJPARAM_UINT32.c_str(), m_GetBgColor?
				m_GetBgColor() : m_BgColor);

		CHECK_AND_RETURN(optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
				OPT_PARAM_KEYS::BGCOLOR_KEY, bgColorArg));
		optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
	}

	if (m_Hints.size()) {
		MsgArg* hintsArg = new MsgArg(AJPARAM_ARRAY_UINT16.c_str(),
				m_Hints.size(), m_Hints.data());
		CHECK_AND_RETURN(optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
				OPT_PARAM_KEYS::HINT_KEY, hintsArg));
		optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
	}
	return status;
}

QStatus Widget::getOptParamsForArg(MsgArg& val, int16_t languageIndx)
{
	QStatus status;
	MsgArg* optParams = new MsgArg[OPT_PARAM_KEYS::NUM_OPT_PARAMS];

	int32_t optParamIndx = 0;

	CHECK_AND_RETURN(getOptParamsForArg(val, languageIndx, optParams, optParamIndx));

    if (!optParamIndx)
	    return val.Set(AJPARAM_OPTPARAM.c_str(), optParamIndx, NULL);
	return val.Set(AJPARAM_OPTPARAM.c_str(), optParamIndx, optParams);
}

