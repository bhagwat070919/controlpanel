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

#include "alljoyn/controlpanel/Widget.h"
#include <map>

namespace ajn {
namespace services {

class Label : public Widget {
  public:
    Label(qcc::String name);
    virtual ~Label();

    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    virtual GetStringFptr getGetLabel() const;

    virtual void setGetLabel(GetStringFptr getLabel);

    virtual const std::vector<qcc::String>& getLabel() const;

    virtual void setLabel(const std::vector<qcc::String>& label);

    QStatus getLabelForArg(MsgArg& val, int16_t languageIndx);

  private:

    std::vector<qcc::String> m_LabelForLabel;
    GetStringFptr m_GetLabelForLabel;
};
} //namespace services
} //namespace ajn

#endif /* LABEL_H_ */
