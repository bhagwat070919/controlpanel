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

#ifndef WIDGET_H_
#define WIDGET_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/BusObject.h"
#include "alljoyn/InterfaceDescription.h"
#include "alljoyn/controlpanel/WidgetBusObject.h"
#include "alljoyn/controlpanel/LanguageSet.h"
#include <vector>

namespace ajn {
namespace services {

typedef uint8_t (*GetEnabledFptr)();
typedef uint8_t (*GetWritableFptr)();
typedef uint32_t (*GetBgColorFptr)();
typedef const char* (*GetLabelFptr)(uint16_t);
typedef const char* (*GetMessageFptr)(uint16_t);


class Widget {
public:
	Widget(qcc::String const&  name, qcc::String const& tag);
    /**
     * Destructor for Widget
     */
    virtual ~Widget() = 0;

    /**
     * setEnabled
     * @param enabled
     */
    void setEnabled(uint8_t enabled);

    /**
     * setWritable
     * @param writeable
     */
    void setWritable(uint8_t writeable);

    QStatus GetVersionForArg(MsgArg& val, int16_t languageIndx);

    QStatus getStatesForArg(MsgArg& val, int16_t languageIndx);

    QStatus getOptParamsForArg(MsgArg& val, int16_t languageIndx,
    		MsgArg* optParams, int32_t& optParamIndx);

    QStatus getOptParamsForArg(MsgArg& val, int16_t languageIndx);

	uint32_t getBgColor() const;
	void setBgColor(uint32_t bgColor);

	GetBgColorFptr getGetBgColor() const;
	void setGetBgColor(GetBgColorFptr getBgColor);

	GetEnabledFptr getGetEnabled() const;
	void setGetEnabled(GetEnabledFptr getEnabled);

	virtual GetLabelFptr getGetLabel() const;
	virtual void setGetLabel(GetLabelFptr getGetLabel);

	GetWritableFptr getGetWritable() const;
	void setGetWritable(GetWritableFptr getWritable);

	const std::vector<uint16_t>& getHints() const;
	void setHints(const std::vector<uint16_t>& hints);

	const uint16_t getInterfaceVersion() const;
	void setInterfaceVersion(uint16_t interfaceVersion);

	virtual const std::vector<qcc::String>& getLabel() const;
	virtual void setLabel(const std::vector<qcc::String>& label);

	void setIsSecured(bool secured);
    bool getIsSecured();

	uint32_t getStates() const;
	void setStates(uint8_t enabled, uint8_t writable);

	qcc::String const& getWidgetName();

	virtual QStatus registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
			qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot = false);

	virtual WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
			uint16_t langIndx, QStatus status) = 0;

	QStatus SendPropertyChangedSignal();

protected:

    qcc::String m_Name;

    bool m_IsSecured;
	uint16_t m_InterfaceVersion;

	uint32_t m_States;
    GetEnabledFptr m_GetEnabled;
    GetWritableFptr m_GetWritable;

    uint32_t m_BgColor;
    GetBgColorFptr m_GetBgColor;

    std::vector<qcc::String> m_Label;
    GetLabelFptr m_GetLabel;

    std::vector<uint16_t> m_Hints;

    /**
     * Tag used for Logging
     */
    qcc::String TAG;

    std::vector<WidgetBusObject*> m_BusObjects;

};
} //namespace services
} //namespace ajn

#endif /* WIDGET_H_ */
