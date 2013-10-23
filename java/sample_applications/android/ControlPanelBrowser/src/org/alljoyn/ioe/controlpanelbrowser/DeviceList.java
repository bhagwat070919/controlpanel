package org.alljoyn.ioe.controlpanelbrowser;
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
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import android.os.Parcel;
import android.os.Parcelable;

/**
 * Helper class for providing sample content for user interfaces created by
 * Android template wizards.
 * <p>
 * TODO: Replace all uses of this class before publishing your app.
 */
public class DeviceList {

	/**
	 * An array of ControlPanelContexts.
	 */
	private List<ControlPanelContext> contexts = new ArrayList<ControlPanelContext>();

	public void addItem(ControlPanelContext item) {
		contexts.add(item);
	}
	
	public List<ControlPanelContext> getContexts() {
		return contexts;
	}

	/**
	 * An item representing a device.
	 */
	public static class ControlPanelContext implements Parcelable {
		final public String deviceId;
		final public String objPath;
		final public String busName;
		final private String label;
		final public String[] interfaces;

		public ControlPanelContext(String deviceId, String objPath, String[] interfaces, String busName, String deviceName) {
			this.deviceId = deviceId;
			this.objPath = objPath;
			this.busName = busName;
			this.interfaces = interfaces;
			label = deviceName + '(' + busName + ')';
		}

		@Override
		public String toString() {
			return label;
		}

		@Override
	     public int describeContents() {
	         return 0;
	     }

	     public void writeToParcel(Parcel out, int flags) {
	         out.writeStringArray(new String[]{deviceId, objPath, busName, label});
	         out.writeInt(interfaces.length);
	         out.writeStringArray(this.interfaces);
	     }

	     public static final Parcelable.Creator<ControlPanelContext> CREATOR
	             = new Parcelable.Creator<ControlPanelContext>() {
	         public ControlPanelContext createFromParcel(Parcel in) {
	             return new ControlPanelContext(in);
	         }

	         public ControlPanelContext[] newArray(int size) {
	             return new ControlPanelContext[size];
	         }
	     };
	     
	     private ControlPanelContext(Parcel in) {
	    	 String[] fields = new String[4];
	    	 in.readStringArray(fields);
	    	 this.deviceId 	= fields[0];
	    	 this.objPath 	= fields[1];
	    	 this.busName 	= fields[2];
	    	 this.label 	= fields[3];
	    	 int numOfIfs = in.readInt();
	    	 this.interfaces = new String[numOfIfs];
	    	 in.readStringArray(this.interfaces);
			
	     }
	}

	public void onDeviceOffline(String busName) {
		Collection<ControlPanelContext> toRemove = new ArrayList<ControlPanelContext>();
		for (ControlPanelContext context: contexts) {
			if (context.busName.equals(busName)) {
				toRemove.add(context);
			}
		}
		contexts.removeAll(toRemove);
	}
}
