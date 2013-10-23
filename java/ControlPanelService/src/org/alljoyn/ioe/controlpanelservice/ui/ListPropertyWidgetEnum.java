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
 * Optional parameter keys of {@link ListPropertyWidget} 
 */
public enum ListPropertyWidgetEnum {
    LABEL((short)0),
    BG_COLOR((short)1),
    HINTS((short)2),
    ;   
    
    /**
     * The key number
     */
    public final short ID;
    
    /**
     * Constructor
     * @param id
     */ 
    private ListPropertyWidgetEnum(short id) {
        ID = id;
    }

}
