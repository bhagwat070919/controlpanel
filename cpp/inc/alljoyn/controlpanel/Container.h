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

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "alljoyn/controlpanel/RootWidget.h"

namespace ajn {
namespace services {

class Container : public RootWidget {
  public:
    Container(qcc::String name);
    virtual ~Container();

    QStatus addChildElement(Widget* childElement);

    QStatus registerObjects(BusAttachment* bus, LanguageSet const& m_LanguageSet,
                            qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot = false);

    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    bool getIsDismissable() const;
    void setIsDismissable(bool isDismissable);

  private:
    std::vector<Widget*> m_ChildElements;

    bool m_IsDismissable;

};
} //namespace services
} //namespace ajn

#endif /* CONTAINER_H_ */
