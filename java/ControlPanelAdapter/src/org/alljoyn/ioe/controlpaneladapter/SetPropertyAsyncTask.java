package org.alljoyn.ioe.controlpaneladapter;
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

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget;

import android.os.AsyncTask;
import android.util.Log;

/**
 * A Utility class that has 2 functions:
 * 1. Executing an action on the remote device, in a background process, to free the UI thread.
 * 2. Notifying the caller about the result. 
 */
abstract class SetPropertyAsyncTask extends AsyncTask<Object, Void, ControlPanelException> {

	private final static String TAG = "cpapp" + SetPropertyAsyncTask.class.getSimpleName();

	@Override
	/**
	 * This background processor assumes params[0] to be a PropertyWidget and params[1] to be the value Object.
	 */
	public ControlPanelException doInBackground(Object... params) {
		PropertyWidget propertyWidget 	= (PropertyWidget) params[0];
		Object value					= params[1];
		Log.d(TAG, String.format("Setting property %s to value %s", propertyWidget.getLabel(), value.toString()));
		try {
			propertyWidget.setCurrentValue(value);
			Log.d(TAG, "Property successfully set");
		} catch (ControlPanelException e) {
			Log.e(TAG, "Failed setting property, error in calling remote object: '" + e.getMessage() + "'");
			return e;
		}
		return null; // No exception...ok!
	}
	
	@Override
	/**
	 * Exception means failure. Otherwise - success.  
	 */
    protected void onPostExecute(ControlPanelException e) {
		if (e != null) {
			onFailure(e);
		} else {
			onSuccess();
		}
	}
	
	/**
	 * Notify the caller about an exception.  
	 */
    abstract protected void onFailure(ControlPanelException e);
	/**
	 * Notify the caller about success.  
	 */
    abstract protected void onSuccess();

}
