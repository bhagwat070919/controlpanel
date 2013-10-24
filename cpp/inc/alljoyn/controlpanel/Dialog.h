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

#ifndef DIALOG_H_
#define DIALOG_H_

#include <alljoyn/controlpanel/RootWidget.h>

namespace ajn {
namespace services {

/**
 * Action Class. Used to display a Dialog.
 * This is an abstract class. The executeActionCallBack functions need to be overridden.
 */
class Dialog : public RootWidget {
  public:

    /**
     * Constructor for Dialog Widget
     * @param name - name of Widget
     */
    Dialog(qcc::String const& name);

    /**
     * Destructor for Dialog Widget
     */
    virtual ~Dialog();

    /**
     * creates and returns the appropriate BusObject for this Widget
     * @param bus - the bus used to create the widget
     * @param objectPath - the objectPath of the widget
     * @param langIndx - the language Indx
     * @param status - the status indicating success or failure
     * @return a newly created WidgetBusObject
     */
    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    /**
     * Get the Number of Actions in the Dialog
     * @return Number of Actions
     */
    const uint16_t getNumActions() const;

    /**
     * Set the number of Actions in the Dialog
     * @param numActions - number of Actions
     */
    void setNumActions(const uint16_t numActions);

    /**
     * Get the Message Vector of the Dialog
     * @return the Messages
     */
    const std::vector<qcc::String>& getMessage() const;

    /**
     * Set the Message vector of the Dialog
     * @param message - the messages
     */
    void setMessage(const std::vector<qcc::String>& message);

    /**
     * Get the GetMessage Function Pointer for the Dialog
     * @return GetMessage function pointer
     */
    GetStringFptr getGetMessage() const;

    /**
     * Set the GetMessage Function Pointer for the Dialog
     * @param getMessage - the GetMessage function pointer
     */
    void setGetMessage(GetStringFptr getMessage);

    /**
     * Get the Vector of Labels for Action 1
     * @return label for Action 1
     */
    const std::vector<qcc::String>& getLabelAction1() const;

    /**
     * Set the Vector of Labels for Action 1
     * @param labelAction1
     */
    void setLabelAction1(const std::vector<qcc::String>& labelAction1);

    /**
     * Get the GetLabel Function Pointer for Action 1
     * @return GetLabel Function Pointer for Action 1
     */
    GetStringFptr getGetLabelAction1() const;

    /**
     * Set the GetLabel function Pointer for Action 1
     * @param getLabelAction1
     */
    void setGetLabelAction1(GetStringFptr getLabelAction1);

    /**
     * Get the Vector of Labels for Action 2
     * @return label for Action 3
     */
    const std::vector<qcc::String>& getLabelAction2() const;

    /**
     * Set the Vector of Labels for Action 2
     * @param labelAction2
     */
    void setLabelAction2(const std::vector<qcc::String>& labelAction2);

    /**
     * Set the GetLabel function Pointer for Action 2
     * @return getLabelAction2
     */
    GetStringFptr getGetLabelAction2() const;

    /**
     * Set the GetLabel function Pointer for Action 2
     * @param getLabelAction2
     */
    void setGetLabelAction2(GetStringFptr getLabelAction2);

    /**
     * Get the Vector of Labels for Action 3
     * @return label for Action 3
     */
    const std::vector<qcc::String>& getLabelAction3() const;

    /**
     * Set the Vector of Labels for Action 3
     * @param labelAction3
     */
    void setLabelAction3(const std::vector<qcc::String>& labelAction3);

    /**
     * Set the GetLabel function Pointer for Action 3
     * @return getLabelAction3
     */
    GetStringFptr getGetLabelAction3() const;

    /**
     * Set the GetLabel function Pointer for Action 3
     * @param getLabelAction3
     */
    void setGetLabelAction3(GetStringFptr getLabelAction3);

    /**
     * Fill the MsgArg passed in with the OptionalParams
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx used for the Labels
     * @return status - success/failure
     */
    QStatus fillOptParamsArg(MsgArg& val, uint16_t languageIndx);

    /**
     * Fill the MsgArg passed in with the Message Param
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx used for the Message
     * @return status - success/failure
     */
    QStatus fillMessageArg(MsgArg& val, uint16_t languageIndx);

    /**
     * Fill the MsgArg passed in with the NumActions
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx
     * @return status - success/failure
     */
    QStatus fillNumActionArg(MsgArg& val, uint16_t languageIndx);

    /**
     * Pure Virtual Method to be overridden
     * Callback for execute of Action1
     * @return success/failure
     */
    virtual bool executeAction1CallBack() = 0;

    /**
     * Pure Virtual Method to be overridden
     * Callback for execute of Action2
     * @return success/failure
     */
    virtual bool executeAction2CallBack() = 0;

    /**
     * Pure Virtual Method to be overridden
     * Callback for execute of Action3
     * @return success/failure
     */
    virtual bool executeAction3CallBack() = 0;

  protected:

    /**
     * Number of Actions in Dialog
     */
    uint16_t m_NumActions;

    /**
     * The message vector of the dialog
     */
    std::vector<qcc::String> m_Message;

    /**
     * The GetMessage Function Pointer of the Dialog
     */
    GetStringFptr m_GetMessage;

    /**
     * The Label vector for Action1
     */
    std::vector<qcc::String> m_LabelAction1;

    /**
     * The GetLabel function pointer for Action 1
     */
    GetStringFptr m_GetLabelAction1;

    /**
     * The Label vector for Action2
     */
    std::vector<qcc::String> m_LabelAction2;

    /**
     * The GetLabel function pointer for Action 2
     */
    GetStringFptr m_GetLabelAction2;

    /**
     * The Label vector for Action3
     */
    std::vector<qcc::String> m_LabelAction3;

    /**
     * The GetLabel function pointer for Action 3
     */
    GetStringFptr m_GetLabelAction3;

    /**
     * Private method used to log a call to an Action that is Not Defined
     * @return false - for failure
     */
    bool executeActionNotDefined();
};
} //namespace services
} //namespace ajn

#endif /* DIALOG_H_ */
