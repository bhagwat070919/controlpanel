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

namespace ajn {
namespace services {

/**
 * Hints for Containers Widgets
 * determining the layout
 */
enum LAYOUT_HINTS {
    VERTICAL_LINEAR = 1, //!< VERTICAL_LINEAR
    HORIZONTAL_LINEAR = 2 //!< HORIZONTAL_LINEAR
};

/**
 * Hints for Dialog Widgets
 */
enum DIALOG_HINTS {
    ALERTDIALOG = 1 //!< ALERTDIALOG
};

/**
 * Hints for Property Widgets
 */
enum PROPERTY_HINTS {
    SWITCH = 1,      //!< SWITCH
    CHECKBOX = 2,    //!< CHECKBOX
    SPINNER = 3,     //!< SPINNER
    RADIOBUTTON = 4, //!< RADIOBUTTON
    SLIDER = 5,      //!< SLIDER
    TIMEPICKER = 6,  //!< TIMEPICKER
    DATEPICKER = 7,  //!< DATEPICKER
    NUMBERPICKER = 8, //!< NUMBERPICKER
    KEYPAD = 9,      //!< KEYPAD
    ROTARYKNOB = 10, //!< ROTARYKNOB
    TEXTVIEW = 11,   //!< TEXTVIEW
    NUMERICVIEW = 12, //!< NUMERICVIEW
    EDITTEXT = 13    //!< EDITTEXT
};

/**
 * Hints for Label Widgets
 */
enum LABEL_HINTS {
    TEXTLABEL = 1 //!< TEXTLABEL
};

/**
 * Hints for ListProperty Widgets
 */
enum LIST_PROPERTY_HINTS {
    DYNAMICSPINNER = 1 //!< DYNAMICSPINNER
};

/**
 * Hints for Action Widgets
 */
enum ACTION_HINTS {
    ACTIONBUTTON = 1 //!< ACTIONBUTTON
};

} //namespace services
} //namespace ajn

#endif /* CONTROLPANELHINTS_H_ */


