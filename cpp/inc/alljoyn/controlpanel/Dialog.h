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

#include "alljoyn/controlpanel/RootWidget.h"
#include <map>

namespace ajn {
namespace services {

class Dialog : public RootWidget {
  public:
    Dialog(qcc::String name);
    virtual ~Dialog();

    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    virtual QStatus unregisterObjects(BusAttachment* bus);

    virtual void executeAction1CallBack();
    virtual void executeAction2CallBack();
    virtual void executeAction3CallBack();

    virtual GetStringFptr getGetMessage() const;
    virtual void setGetMessage(GetStringFptr getMessage);

    virtual const std::vector<qcc::String>& getMessage() const;
    virtual void setMessage(const std::vector<qcc::String>& message);

    virtual const uint16_t getNumActions() const;
    virtual void setNumActions(const uint16_t numActions);

    QStatus getOptParamsForArg(MsgArg& val, int16_t languageIndx);

    QStatus getMessageForArg(MsgArg& val, int16_t languageIndx);

    QStatus getNumActionForArg(MsgArg& val, int16_t languageIndx);

    GetStringFptr getGetLabelAction1() const;
    void setGetLabelAction1(GetStringFptr getLabelAction1);

    GetStringFptr getGetLabelAction2() const;
    void setGetLabelAction2(GetStringFptr getLabelAction2);

    GetStringFptr getGetLabelAction3() const;
    void setGetLabelAction3(GetStringFptr getLabelAction3);

    const std::vector<qcc::String>& getLabelAction1() const;
    void setLabelAction1(const std::vector<qcc::String>& labelAction1);

    const std::vector<qcc::String>& getLabelAction2() const;
    void setLabelAction2(const std::vector<qcc::String>& labelAction2);

    const std::vector<qcc::String>& getLabelAction3() const;
    void setLabelAction3(const std::vector<qcc::String>& labelAction3);

  protected:

    void executeActionNotDefined();

    std::vector<qcc::String> m_Message;
    GetStringFptr m_GetMessage;

    uint16_t m_NumActions;

    std::vector<qcc::String> m_LabelAction1;
    GetStringFptr m_GetLabelAction1;

    std::vector<qcc::String> m_LabelAction2;
    GetStringFptr m_GetLabelAction2;

    std::vector<qcc::String> m_LabelAction3;
    GetStringFptr m_GetLabelAction3;
};
} //namespace services
} //namespace ajn

#endif /* DIALOG_H_ */
