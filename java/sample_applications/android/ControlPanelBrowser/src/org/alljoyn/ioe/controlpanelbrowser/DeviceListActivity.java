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

import org.alljoyn.ioe.controlpanelbrowser.DeviceList.ControlPanelContext;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;

/**
 * An activity representing a list of Appliances. This activity has different
 * presentations for handset and tablet-size devices. On handsets, the activity
 * presents a list of items, which when touched, lead to a
 * {@link DeviceDetailActivity} representing item details. On tablets, the
 * activity presents the list of items and item details side-by-side using two
 * vertical panes.
 * <p>
 * The activity makes heavy use of fragments. The list of items is a
 * {@link DeviceListFragment} and the item details (if present) is a
 * {@link DeviceDetailFragment}.
 * <p>
 * This activity also implements the required
 * {@link DeviceListFragment.Callbacks} interface to listen for item
 * selections.
 */
public class DeviceListActivity extends FragmentActivity implements
		DeviceListFragment.Callbacks {

	
	/**
	 * For logging
	 */
	private final static String TAG = "cpappApplianceListActivity";
	/**
	 * Whether or not the activity is in two-pane mode, i.e. running on a tablet
	 * device.
	 */
	private boolean isTwoPane;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		Log.d(TAG, "onCreate()");

		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_device_list);

		if (findViewById(R.id.appliance_detail_container) != null) {
			// The detail container view will be present only in the
			// large-screen layouts (res/values-large and
			// res/values-sw600dp). If this view is present, then the
			// activity should be in two-pane mode.
			isTwoPane = true;

			// In two-pane mode, list items should be given the
			// 'activated' state when touched.
			((DeviceListFragment) getSupportFragmentManager()
					.findFragmentById(R.id.appliance_list))
					.setActivateOnItemClick(true);
		}
	}

	@Override
	public void onDestroy() 
	{
		super.onDestroy();

	}

	/**
	 * Callback method from {@link DeviceListFragment.Callbacks} indicating
	 * that the item with the given ID was selected.
	 */
	@Override
	public void onItemSelected(ControlPanelContext context) {
		if (isTwoPane) {
			// In two-pane mode, show the detail view in this activity by
			// adding or replacing the detail fragment using a
			// fragment transaction.
			Bundle arguments = new Bundle();
			arguments.putParcelable(DeviceDetailFragment.ARG_ITEM_ID, context);
			DeviceDetailFragment fragment = new DeviceDetailFragment();
			fragment.setArguments(arguments);
			getSupportFragmentManager().beginTransaction()
					.replace(R.id.appliance_detail_container, fragment)
					.commit();

		} else {
			// In single-pane mode, simply start the detail activity
			// for the selected item ID.
			Intent detailIntent = new Intent(this,
					DeviceDetailActivity.class);
			detailIntent.putExtra(DeviceDetailFragment.ARG_ITEM_ID, context);
			startActivity(detailIntent);
		}
	}
	
}
