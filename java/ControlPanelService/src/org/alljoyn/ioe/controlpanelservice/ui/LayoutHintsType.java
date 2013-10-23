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
 * Possible types of layout hints
 */
public enum LayoutHintsType {
	VERTICAL_LINEAR((short)1),
	HORIZONTAL_LINEAR((short)2),
	;
	
	/**
	 * The key number
	 */
	public final short ID;
	
	/**
	 * Constructor
	 * @param id
	 */
	private LayoutHintsType(short id) {
		ID = id;
	}
	
    /**
	 * Search for the enum by the given id
	 * If not found returns NULL
	 * @param id 
	 * @return Enum type by the given id
	 */
	public static LayoutHintsType getEnumById(short id) {
		LayoutHintsType retType = null;
		for (LayoutHintsType type : LayoutHintsType.values()) {
			if ( id == type.ID ) {
				retType = type;
				break;
			}
		}
		return retType;
	}//getEnumById
}
