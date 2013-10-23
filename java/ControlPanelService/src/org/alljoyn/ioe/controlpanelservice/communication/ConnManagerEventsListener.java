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

package org.alljoyn.ioe.controlpanelservice.communication;

import java.util.Map;

/**
 * Used to notify observers about the connection manager events
 */
public interface ConnManagerEventsListener {
	
	/**
	 * The method is launched when the event happened in ConnectionManager
	 * @param eventType The type of the event
	 * @param args
	 */
	public void connMgrEventOccured(ConnManagerEventType eventType, Map<String, Object> args);
}	
