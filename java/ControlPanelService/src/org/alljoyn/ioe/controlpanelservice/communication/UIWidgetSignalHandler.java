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

import java.lang.reflect.Method;

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;

import android.util.Log;

/**
 * The class includes all the required data to register/unregister signals
 */
public class UIWidgetSignalHandler {
	private static final String TAG = "cpan" + UIWidgetSignalHandler.class.getSimpleName();
	
	/**
	 * The object path that is used as a signal source.
	 */
	 private String objPath;
	    
	 /**
	  * The signal handler object
	  */
	 private Object signalReceiver;
	    
	 /**
	  * The reflection of the signal method 
	  */
	 private Method method;
	    
	 /**
	  * The interface of the signal
	  */
	 private String ifName;
	
	/**
	 * Constructor
	 * @param objPath The object path that is used as a signal source.
	 * @param signalReceiver The signal receiver object
	 * @param method The reflection of the signal method 
	 * @param ifName The interface of the signal
	 */
	public UIWidgetSignalHandler(String objPath, Object signalReceiver, Method method, String ifName) {
		this.objPath        = objPath;
		this.signalReceiver = signalReceiver;
		this.method         = method;
		this.ifName         = ifName;
	}

	/**
	 * Registers signal handler
	 * @throws ControlPanelException
	 */
	public void register() throws ControlPanelException {
        ConnectionManager.getInstance().registerObjectAndSetSignalHandler(
                ifName,
                method.getName(),
                method,
                signalReceiver,
                objPath,
                objPath
       );
	}//register
	
	/**
	 * Unregisters signal handler
	 * @throws ControlPanelException
	 */
	public void unregister() throws ControlPanelException {
		Log.v(TAG, "Unregistering signal handler: '" + method.getName() + "', objPath: '" + objPath + "'");
		ConnectionManager.getInstance().unregisterSignalHandler(signalReceiver, method);
	}//unregister
}
