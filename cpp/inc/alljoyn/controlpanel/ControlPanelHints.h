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

#ifndef CONTROLPANELHINTS_H_
#define CONTROLPANELHINTS_H_

#include <qcc/String.h>

namespace ajn {
namespace services {

enum LAYOUT_HINTS {
    VERTICAL_LINEAR = 1,
    HORIZONTAL_LINEAR = 2
};

enum DIALOG_HINTS {
    ALERTDIALOG = 1
};

enum PROPERTY_HINTS {
    SWITCH = 1,
    CHECKBOX = 2,
    SPINNER = 3,
    RADIOBUTTON = 4,
    SLIDER = 5,
    TIMEPICKER = 6,
    DATEPICKER = 7,
    NUMBERPICKER = 8,
    KEYPAD = 9,
    ROTARYKNOB = 10,
    TEXTVIEW = 11,
    NUMERICVIEW = 12,
    EDITTEXT = 13
};

enum LABEL_HINTS {
    TEXTLABEL = 1
};

enum LIST_PROPERTY_HINTS {
    DYNAMICSPINNER = 1
};

enum ACTION_HINTS {
    ACTIONBUTTON = 1
};

} //namespace services
} //namespace ajn

#endif /* CONTROLPANELHINTS_H_ */


