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

package org.alljoyn.ioe.controlpanelservice.ui;

/**
 * Possible types of property UI hints
 */
public enum PropertyWidgetHintsType {
	SWITCH((short)1),
	CHECKBOX((short)2),
	SPINNER((short)3),
	RADIO_BUTTON((short)4),
	SLIDER((short)5),
	TIME_PICKER((short)6),
	DATE_PICKER((short)7),
	NUMBER_PICKER((short)8),
	NUMERIC_KEYPAD((short)9),
	ROTARY_KNOB((short)10),
	TEXT_VIEW((short)11),
	NUMERIC_VIEW((short)12),
	EDIT_TEXT((short)13),
	;
	
    /** 
     * The key number
     */  
    public final short ID; 
        
    /** 
     * Constructor
     * @param id
     */
    private PropertyWidgetHintsType(short id) {
        ID = id; 
    }   
        
    /** 
     * Search for the enum by the given id
     * If not found returns NULL
     * @param id  
     * @return Enum type by the given id
     */
    public static PropertyWidgetHintsType getEnumById(short id) {
    	PropertyWidgetHintsType retType = null;
        for (PropertyWidgetHintsType type : PropertyWidgetHintsType.values()) {
            if ( id == type.ID ) { 
                retType = type;
                break;
            }   
        }   
        return retType;
    }//getEnumById
}
