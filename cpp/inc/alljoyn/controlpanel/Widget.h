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
#include "alljoyn/controlpanel/LanguageSet.h"

namespace ajn {
namespace services {

/*
 * Typedefs for functionPointers used
 */
typedef bool (*GetBoolFptr)();
typedef uint32_t (*GetUint32Fptr)();
typedef const char* (*GetStringFptr)(uint16_t);

/*
 * Forward Declaration
 */
class WidgetBusObject;

/**
 * Base Class for all Widgets
 */
class Widget {
  public:

    /**
     * Constructor for Widget class
     * @param name - name of Widget
     * @param tag - tag for logging
     */
    Widget(qcc::String const&  name, qcc::String const& tag);

    /**
     * Destructor for Widget
     */
    virtual ~Widget() = 0;

    /**
     * Pure virtual function. Needs to be implemented by a function that will
     * create and return the appropriate BusObject for the Widget
     * @param bus - the bus used to create the widget
     * @param objectPath - the objectPath of the widget
     * @param langIndx - the language Indx
     * @param status - the status indicating success or failure
     * @return a newly created WidgetBusObject
     */
    virtual WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                                   uint16_t langIndx, QStatus& status) = 0;

    /**
     * Get the name of the Widget
     * @return widgetName
     */
    qcc::String const& getWidgetName();

    /**
     * Get the Interface Version of the Widget
     * @return interface Version
     */
    const uint16_t getInterfaceVersion() const;

    /**
     * Set the isSecured boolean
     * @param secured
     */
    void setIsSecured(bool secured);

    /**
     * Get the isSecured boolean
     * @return
     */
    bool getIsSecured();

    /**
     * Set the Enabled flag of the Widget
     * @param enabled
     */
    void setEnabled(bool enabled);

    /**
     * Get the GetEnabled function Pointer
     * @return getEnabled function Pointer of the widget
     */
    GetBoolFptr getGetEnabled() const;

    /**
     * Set the GetEnabled function Pointer
     * @param getEnabled - function pointer to get the enabled boolean
     */
    void setGetEnabled(GetBoolFptr getEnabled);

    /**
     * Set the Writable flag of the widget
     * @param writable
     */
    void setWritable(bool writable);

    /**
     * Get the GetWritable function Pointer
     * @return getWritable function Pointer of the widget
     */
    GetBoolFptr getGetWritable() const;

    /**
     * Set the GetWritable function Pointer
     * @param getWritable - function pointer to get the writable boolean
     */
    void setGetWritable(GetBoolFptr getWritable);

    /**
     * Get the States of the Widget
     * @return states
     */
    uint32_t getStates() const;

    /**
     * Set the States of the widget
     * @param enabled - is widget enabled
     * @param writable -  is widget writable
     */
    void setStates(uint8_t enabled, uint8_t writable);

    /**
     * Get the BgColor of the Widget
     * @return bgColor
     */
    uint32_t getBgColor() const;

    /**
     * Set the BgColor of the Widget
     * @param bgColor
     */
    void setBgColor(uint32_t bgColor);

    /**
     * Get the GetBgColor function pointer of the Widget
     * @return GetBgColor function pointer
     */
    GetUint32Fptr getGetBgColor() const;

    /**
     * Set the GetBgColor function pointer of the Widget
     * @param getBgColor
     */
    void setGetBgColor(GetUint32Fptr getBgColor);

    /**
     * Get the Labels vector of the widget
     * @return - label
     */
    virtual const std::vector<qcc::String>& getLabel() const;

    /**
     * Set the labels vector of the widget
     * @param label - vector of labels
     */
    virtual void setLabel(const std::vector<qcc::String>& label);

    /**
     * Get the GetLabel function pointer
     * @return GetLabel function pointer
     */
    virtual GetStringFptr getGetLabel() const;

    /**
     * Set the GetLabel function pointer
     * @param getLabel - getLabel function pointer
     */
    virtual void setGetLabel(GetStringFptr getLabel);

    /**
     * Get the vector of Hints for the Widget
     * @return hints Vector
     */
    const std::vector<uint16_t>& getHints() const;

    /**
     * Set the vector of Hints for the Widget
     * @param hints - hints vector
     */
    void setHints(const std::vector<uint16_t>& hints);

    /**
     * Register the BusObjects for this Widget
     * @param bus - the bus used to register the busObjects
     * @param languageSet -  the languageSet to register the busObjects for
     * @param objectPathPrefix - the objectPathPrefix of the busObject
     * @param objectPathSuffix - the objectPathSuffix of the busObject
     * @param isRoot - is this a rootWidget
     * @return status - success/failure
     */
    virtual QStatus registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                    qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot = false);

    /**
     * Unregister the BusObjects for this widget
     * @param bus
     * @return status - success/failure
     */
    virtual QStatus unregisterObjects(BusAttachment* bus);

    /**
     * Fill MsgArg passed in with the States
     * @param val - msgArg to fill
     * @param languageIndx - language requested
     * @return status - success/failure
     */
    QStatus fillStatesArg(MsgArg& val, uint16_t languageIndx);

    /**
     * Fill MsgArg passed in with the OptParams
     * @param val - msgArg to fill
     * @param languageIndx - language requested
     * @return status - success/failure
     */
    virtual QStatus fillOptParamsArg(MsgArg& val, uint16_t languageIndx);

    /**
     * Set a Property Changed Signal
     * @return status - success/failure
     */
    QStatus SendPropertyChangedSignal();

  protected:

    /**
     * The Name of the Widget
     */
    qcc::String m_Name;

    /**
     * Is the Widget Secured
     */
    bool m_IsSecured;

    /**
     * States of the Widget
     */
    uint32_t m_States;

    /**
     * GetEnabled function Pointer
     */
    GetBoolFptr m_GetEnabled;

    /**
     * Get Writable Function Pointer
     */
    GetBoolFptr m_GetWritable;

    /**
     * BgColor of the Widget
     */
    uint32_t m_BgColor;

    /**
     * GetBgColor function Pointer of the Widget
     */
    GetUint32Fptr m_GetBgColor;

    /**
     * Vector of Labels
     */
    std::vector<qcc::String> m_Label;

    /**
     * GetLabel functionPointer
     */
    GetStringFptr m_GetLabel;

    /**
     * Vector of Hints
     */
    std::vector<uint16_t> m_Hints;

    /**
     * The BusObjects of the Widget
     */
    std::vector<WidgetBusObject*> m_BusObjects;

    /**
     * Tag used for Logging
     */
    qcc::String const& TAG;

    /**
     * Function to fill the OptParams of the Widget Base class
     * @param optParams - msgArg Array to fill
     * @param languageIndx - the language requested
     * @param optParamIndx - the index of the optParams array to start from
     * @return status - success/failure
     */
    QStatus fillOptParamsArg(MsgArg* optParams, uint16_t languageIndx, size_t& optParamIndx);

};
} //namespace services
} //namespace ajn

#endif /* WIDGET_H_ */
