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

package org.alljoyn.ioe.controlpanelservice.ui.ajstruct;

import org.alljoyn.bus.annotation.Position;

public class PropertyWidgetThreeShortAJ {
	
	/**
	 * The type of the received structure, either Date or Time
	 */
	@Position(0)
	public short dataType;
	
	/**
	 * Either Hour or Day
	 */
	@Position(1)
	public ThreeShortAJ data;
	
		
	public static class ThreeShortAJ {
		@Position(0)
		public short var1;
		
		@Position(1)
		public short var2;
		
		@Position(2)
		public short var3;

	}
}
