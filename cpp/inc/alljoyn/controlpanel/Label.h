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

#ifndef LABEL_H_
#define LABEL_H_

#include <alljoyn/controlpanel/Widget.h>
#include <map>

namespace ajn {
namespace services {

/**
 * Label class used to display a Label
 */
class Label : public Widget {
  public:

    /**
     * Constructor for Label class
     * @param name - name of Widget
     */
    Label(qcc::String const& name);

    /**
     * Destructor for Label class
     */
    virtual ~Label();

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
     * Get the Labels vector of the widget
     * @return - label
     */
    const std::vector<qcc::String>& getLabel() const;

    /**
     * Set the labels vector of the widget
     * @param label - vector of labels
     */
    void setLabel(const std::vector<qcc::String>& label);

    /**
     * Get the GetLabel function pointer
     * @return GetLabel function pointer
     */
    GetStringFptr getGetLabel() const;

    /**
     * Set the GetLabel function pointer
     * @param getLabel - getLabel function pointer
     */
    void setGetLabel(GetStringFptr getLabel);

    /**
     * Fill MsgArg passed in with the Label
     * @param val - msgArg to fill
     * @param languageIndx - language of the label
     * @return status - success/failure
     */
    QStatus fillLabelArg(MsgArg& val, uint16_t languageIndx);

  private:

    /**
     * Vector of Labels of Label Widget
     */
    std::vector<qcc::String> m_LabelWidgetLabel;

    /**
     * GetLabel functionPointer of Label Widget
     */
    GetStringFptr m_LabelWidgetGetLabel;
};
} //namespace services
} //namespace ajn

#endif /* LABEL_H_ */
