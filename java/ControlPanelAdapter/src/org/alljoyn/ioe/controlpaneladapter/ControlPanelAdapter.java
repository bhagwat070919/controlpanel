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
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;
import java.util.Map;
import java.util.WeakHashMap;

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ui.ActionWidget;
import org.alljoyn.ioe.controlpanelservice.ui.ActionWidgetHintsType;
import org.alljoyn.ioe.controlpanelservice.ui.AlertDialogWidget;
import org.alljoyn.ioe.controlpanelservice.ui.AlertDialogWidget.DialogButton;
import org.alljoyn.ioe.controlpanelservice.ui.ContainerWidget;
import org.alljoyn.ioe.controlpanelservice.ui.LabelWidget;
import org.alljoyn.ioe.controlpanelservice.ui.LayoutHintsType;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ConstrainToValues;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.RangeConstraint;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ValueType;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidgetHintsType;
import org.alljoyn.ioe.controlpanelservice.ui.UIElement;
import org.alljoyn.ioe.controlpanelservice.ui.UIElementType;

import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.text.InputFilter;
import android.text.InputType;
import android.text.format.DateFormat;
import android.util.Log;
import android.util.SparseArray;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;
import android.widget.TimePicker;

public class ControlPanelAdapter
{
	private final static String TAG = "cpapp" + ControlPanelAdapter.class.getSimpleName();

	private static final Object PROPERTY_VALUE = "property_value";
	private static final Object PROPERTY_EDITOR = "property_editor";

	/* a context for creating Views */
	private final Context uiContext;

	/* mapping of UIElements to Views that were created by this adapter */
	private Map<String,View> uiElementToView = new WeakHashMap<String, View>(10);
	
	/* mapping of AlertDialogWidgets to AlertDialogs that were created by this adapter */
	private Map<String,AlertDialog> alertWidgetToDialog = new WeakHashMap<String, AlertDialog>(3);

	/* App handler for control panel exceptions */
	private ControlPanelExceptionHandler exceptionHandler;

	// =====================================================================================================================

	public ControlPanelAdapter(Context uiContext, ControlPanelExceptionHandler exceptionHandler) {
		super();
		this.uiContext = uiContext;
		this.exceptionHandler = exceptionHandler;
	}

	// =====================================================================================================================

	/**
	 * Creates a Layout that corresponds with the given ContainerWidget
	 * @param container input widget defining a container.
	 * @return a resulting Layout. This method iterates the contained widget and creates the corresponding inner Views. 
	 */
	public View createContainerView(ContainerWidget container) {
		if ( container == null ) {
			Log.e(TAG, "createContainerView(container==null)");
			return null;
		}

		// the returned Layout object
		ViewGroup scrollView;
		ViewGroup containerLayout;

		ViewGroup.LayoutParams layoutParams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		Log.d(TAG, "Received main container, objPath: '" + container.getObjectPath() + "'");

		// initialize the container by type
		List<LayoutHintsType> layoutHints = container.getLayoutHints();
		Log.d(TAG, "Container has LayoutHints: " + layoutHints);

		// set the layout
		if ( layoutHints.size() == 0 ) {
			scrollView 		= new ScrollView(uiContext);
			LinearLayout linearLayout1 = new LinearLayout(uiContext);
			linearLayout1.setOrientation(LinearLayout.VERTICAL);
			linearLayout1.setGravity(Gravity.CENTER_HORIZONTAL);
			containerLayout	= linearLayout1;
			// set the inner label
			if (container.getLabel() != null && container.getLabel().trim().length() > 0)
			{
				Log.d(TAG,"Setting container label to: " + container.getLabel());
				TextView titleTextView = new TextView(uiContext);
				titleTextView.setText(container.getLabel());
				LinearLayout.LayoutParams textLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
				textLayoutParams.setMargins(20, 0, 20, 0);
				containerLayout.addView(titleTextView, textLayoutParams);
			}
		} else {
			LayoutHintsType layoutHintsType = layoutHints.get(0);
			switch(layoutHintsType) {
			case HORIZONTAL_LINEAR:
				scrollView 		= new HorizontalScrollView(uiContext);
				LinearLayout linearLayout = new LinearLayout(uiContext);
				linearLayout.setOrientation(LinearLayout.HORIZONTAL);
				linearLayout.setGravity(Gravity.CENTER_VERTICAL);
				containerLayout	= linearLayout;
				LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
				hLinearLayoutParams.setMargins(10, 10, 10, 10);
				layoutParams = hLinearLayoutParams;
				break;
			case VERTICAL_LINEAR: default:
				scrollView 		= new ScrollView(uiContext);
				LinearLayout linearLayout1 = new LinearLayout(uiContext);
				linearLayout1.setOrientation(LinearLayout.VERTICAL);
				linearLayout1.setGravity(Gravity.CENTER_HORIZONTAL);
				containerLayout	= linearLayout1;
				// set the inner label
				if (container.getLabel() != null && container.getLabel().trim().length() > 0)
				{
					Log.d(TAG,"Setting container label to: " + container.getLabel());
					TextView titleTextView = new TextView(uiContext);
					titleTextView.setText(container.getLabel());
					LinearLayout.LayoutParams textLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					textLayoutParams.setMargins(20, 0, 20, 0);
					containerLayout.addView(titleTextView, textLayoutParams);
				}
				break;
			}
		}
		Log.d(TAG, "Initialized Layout of class: " +containerLayout.getClass().getSimpleName());

		Log.d(TAG,"Container bgColor:  " + container.getBgColor());
		if (container.getBgColor() != null)
			containerLayout.setBackgroundColor(container.getBgColor());

		Log.d(TAG,"Container is enabled: " + container.isEnabled() );
		containerLayout.setEnabled(container.isEnabled());

		// recursively layout the items
		List<UIElement> elements = container.getElements();
		Log.d(TAG, String.format("Laying out %d elements", elements.size()));

		for(UIElement element : elements) {
			View childView = createInnerView(element);
			containerLayout.addView(childView, layoutParams);
		}//for :: elements

		LinearLayout.LayoutParams linearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		scrollView.addView(containerLayout, linearLayoutParams);
		uiElementToView.put(container.getObjectPath(), scrollView);
		return scrollView;
	}

	// =====================================================================================================================

	/**
	 * Creates an Android View that corresponds with the given UIElement
	 * @param element the abstract UIElement
	 * @return an Android View that corresponds with the given abstract UIElement
	 */
	private View createInnerView(UIElement element) {
		UIElementType elementType = element.getElementType();
		Log.d(TAG, "Creating an Android View for element of type: '" + elementType + "'");
		View returnView = new TextView(uiContext);

		switch(elementType) {
		case ACTION_WIDGET: {
			returnView = createActionView((ActionWidget)element);
			break;
		}//ACTION_WIDGET
		case CONTAINER: {
			returnView = createContainerView((ContainerWidget) element);
			break;
		}// CONTAINER
		//			case LIST_PROPERTY_WIDGET: {
		//				break;
		//			}//LIST_PROPERTY_WIDGET
		case PROPERTY_WIDGET: {
			returnView = createPropertyView((PropertyWidget) element);
			break;
		}//PROPERTY_WIDGET
		case LABEL_WIDGET: {
			returnView = createLabelView((LabelWidget) element);
			break;
		}//PROPERTY_WIDGET
		default:
			break;
		}//switch :: elementType

		return returnView;
	}

	// =====================================================================================================================

	/**
	 * Creates an AlertDialog that corresponds with the given AlertDialogWidget
	 * @param alertDialogWidget input abstract widget defining a dialog.
	 * @return an AlertDialog with up to 3 actions. Each action executes a different DialogButton UIElement.
	 */
	public AlertDialog createAlertDialog(final AlertDialogWidget alertDialogWidget) {
		final SparseArray<DialogButton> buttonToAction = new SparseArray<AlertDialogWidget.DialogButton>(3);

		List<DialogButton> execButtons = alertDialogWidget.getExecButtons();
		int numOfButtons = alertDialogWidget.getNumActions();
		if (numOfButtons > 0) {
			buttonToAction.put(DialogInterface.BUTTON_POSITIVE, execButtons.get(0));
			if (numOfButtons > 1) {
				buttonToAction.put(DialogInterface.BUTTON_NEGATIVE, execButtons.get(1));
				if (numOfButtons > 2) {
					buttonToAction.put(DialogInterface.BUTTON_NEUTRAL, execButtons.get(2));
				}
			}
		}

		// create a confirmation dialog
		DialogInterface.OnClickListener confirmationListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, final int which) {
				// handle user choice 
				final DialogButton actionButton = buttonToAction.get(which);
				Log.d(TAG, "User selected: " + actionButton.getLabel());

				// execute the action in a background task
				ExecuteActionAsyncTask asyncTask = new ExecuteActionAsyncTask() {

					@Override
					protected void onFailure(ControlPanelException e) {
						if (exceptionHandler != null) {
							exceptionHandler.handleControlPanelException(e);
						}
					}

					@Override
					protected void onSuccess() {
					}

				};
				asyncTask.execute(actionButton);
			}
		};

		// show the confirmation dialog
		Builder builder = new AlertDialog.Builder(uiContext)
		.setMessage(alertDialogWidget.getMessage())
		.setTitle(alertDialogWidget.getLabel());


		if (numOfButtons > 0) {
			builder.setPositiveButton(buttonToAction.get(DialogInterface.BUTTON_POSITIVE).getLabel(), confirmationListener);
			if (numOfButtons > 1) {
				builder.setNegativeButton(buttonToAction.get(DialogInterface.BUTTON_NEGATIVE).getLabel(), confirmationListener);
				if (numOfButtons > 2) {
					builder.setNeutralButton(buttonToAction.get(DialogInterface.BUTTON_NEUTRAL).getLabel(), confirmationListener);
				}
			}
		}

		AlertDialog alertDialog = builder.create();
		alertWidgetToDialog.put(alertDialogWidget.getObjectPath(), alertDialog);
		return alertDialog;

	}

	// =====================================================================================================================

	/**
	 * Creates a Button for an ActionWidget
	 * @param action the UIElement to be represented by this button. 
	 * @return a Button with 2 optional flows corresponding with the ActionWidget definition:
	 * 			A button that executes an action.
	 * 			Or a button that popsup an "Are You Sure?" dialog.
	 */
	public View createActionView(final ActionWidget action) {

		List<ActionWidgetHintsType> hints = action.getHints();
		String label = action.getLabel();
		Integer bgColor = action.getBgColor();
		Log.d(TAG, "Create Action: " + label + " BGColor: " + bgColor + " actionMeta: " + hints);

		Button actionButton = new Button(uiContext);
		actionButton.setText(label);
		if (bgColor != null)
			actionButton.setBackgroundColor(bgColor);

		// register a click listener
		OnClickListener actionButtonListener = new OnClickListener() {

			@Override
			public void onClick(View v)	{
				// Check that action is still enabled
				try {
					action.refreshProperties();
					if (action.isEnabled()) {
						Log.d(TAG, "ActionWidget is enabled");
					} else {
						Log.i(TAG, "ActionWidget is disabled");
						// ====
						return;
					}

				} catch (ControlPanelException e) {
					Log.e(TAG, "ActionWidget.refreshMetadata failed", e);
					// ====
					return;
				}

				// check if action requires an extra confirmation
				AlertDialogWidget alertDialogWidget = action.getAlertDialog();
				if (alertDialogWidget != null) {
					Log.d(TAG, "Showing confirmation: " + alertDialogWidget.getMessage() + "?");
					// create a confirmation dialog
					AlertDialog confirmationDialog = createAlertDialog(alertDialogWidget);
					confirmationDialog.show();
				} // Confirmation needed
				else { // No confirmation needed

					// execute the action in a background task
					ExecuteActionAsyncTask asyncTask = new ExecuteActionAsyncTask() {

						@Override
						protected void onFailure(ControlPanelException e) {
							if (exceptionHandler != null) {
								exceptionHandler.handleControlPanelException(e);
							}
						}

						@Override
						protected void onSuccess() {
						}

					};
					asyncTask.execute(action);
				} // No confirmation needed

			}
		};// new OnClickListener()
		actionButton.setOnClickListener(actionButtonListener);

		uiElementToView.put(action.getObjectPath(), actionButton);
		return actionButton;
	}//createActionView

	// =====================================================================================================================

	/**
	 * Creates a TextView for a LabelWidget
	 * @param labelWidget the UIElement to be represented by this View 
	 * @return a TextView displaying the contents of the LabelWidget
	 */
	public View createLabelView(final LabelWidget labelWidget) {
		String label = labelWidget.getLabel();
		Integer bgColor = labelWidget.getBgColor();
		Log.d(TAG, "Creating Label: \"" + label + "\" BGColor: " + bgColor);

		TextView labelView =  new TextView(uiContext);
		labelView.setText(label);
		if (bgColor != null)
			labelView.setBackgroundColor(bgColor);

		uiElementToView.put(labelWidget.getObjectPath(), labelView);
		return labelView;
	}//createLabelView


	// =====================================================================================================================
	// ============================================= PropertyWidget ========================================================
	// =====================================================================================================================


	/**
	 * A factory method for creating a View for a given PropertyWidget.
	 * @param propertyWidget the UIElement to be represented by this View
	 * @return a View that represents the property. The type of View corresponds with the propertys hint.
	 */
	public View createPropertyView(PropertyWidget propertyWidget) {
		ValueType valueType = propertyWidget.getValueType();
		View returnView = new TextView(uiContext);

		Log.d(TAG, "Creating a View for property '" + propertyWidget.getLabel() + "' , using UI hint: " + propertyWidget.getHints() + ", value type: '" + valueType + "', objPath: '" + propertyWidget.getObjectPath() + "'");

		if (propertyWidget.getHints() == null || propertyWidget.getHints().size() == 0) {
			Log.d(TAG, "No hint provided for property '" + propertyWidget.getLabel() + "' , returning an empty view");
			return returnView;
		}

		PropertyWidgetHintsType hint = propertyWidget.getHints().get(0);
		switch(hint) {
		case SPINNER:
			returnView = createSpinnerView(propertyWidget);
			break;
		case CHECKBOX:
			returnView = createCheckBoxView(propertyWidget);
			break;
		case NUMERIC_VIEW: 
			returnView = createNumericView(propertyWidget);
			break;
		case TEXT_VIEW:
			returnView = createTextView(propertyWidget);
			break;
		case NUMBER_PICKER:
			returnView = createNumberPickerView(propertyWidget);
			break;
		case SLIDER:
			returnView = createSliderView(propertyWidget);
			break;
		case EDIT_TEXT:
			returnView = createEditTextView(propertyWidget);
			break;
		case NUMERIC_KEYPAD:
			returnView = createNumericKeypadView(propertyWidget);
			break;
		case RADIO_BUTTON:
			returnView = createRadioButtonView(propertyWidget);
			break;
		case TIME_PICKER:
			returnView = createTimePickerView(propertyWidget);
			break;
		case DATE_PICKER:
			returnView = createDatePickerView(propertyWidget);
			break;
		default:
			break;
		}

		uiElementToView.put(propertyWidget.getObjectPath(), returnView);

		return returnView;
	}

	// =====================================================================================================================

	private Spinner createSpinnerView(final PropertyWidget propertyWidget)
	{
		Log.d(TAG, "Creating a spinner for propertyWidget " + propertyWidget.getLabel());

		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "propertyWidget.getCurrentValue() failed, initializing property without current value", e);
		}

		final Spinner spinner = new Spinner(uiContext);
		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());
		spinner.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the data model
		final ArrayAdapter<LabelValuePair> adapter = new ArrayAdapter<LabelValuePair>(uiContext, android.R.layout.simple_spinner_item);
		int selection = 0;
		if ( propertyWidget.getListOfConstraint() != null ) {
			// create a spinner model made of the given ConstrainToValues entries
			int position = 0;
			for (ConstrainToValues<?> valueCons : propertyWidget.getListOfConstraint()) {
				boolean isDefault = valueCons.getValue().equals(currentValue);
				Log.d(TAG, "Adding spinner item, Label: " + valueCons.getLabel() + " Value: " + valueCons.getValue() + (isDefault?" (default)":""));
				adapter.add(new LabelValuePair(valueCons.getLabel(), valueCons.getValue()));
				if (isDefault) {
					selection = position; 
				}
				position++;
			}
		} else if (propertyWidget.getPropertyRangeConstraint() != null){
			// dynamically create a spinner model made of integers from min to max
			RangeConstraint<?> propertyRangeConstraint = propertyWidget.getPropertyRangeConstraint();

			ValueType valueType = propertyWidget.getValueType();
			Object minT = propertyRangeConstraint.getMin();
			int min = 
					ValueType.SHORT.equals(valueType) ? ((Short)minT) :
						ValueType.INT.equals(valueType) ? ((Integer)minT) : 0;	
			Object maxT = propertyRangeConstraint.getMax();
			int max = 
					ValueType.SHORT.equals(valueType) ? ((Short)maxT) :
						ValueType.INT.equals(valueType) ? ((Integer)maxT) : 0;	
			Object incrementT = propertyRangeConstraint.getIncrement();
			int increment = 
					ValueType.SHORT.equals(valueType) ? ((Short)incrementT) :
						ValueType.INT.equals(valueType) ? ((Integer)incrementT) : 0;	
			for (int i=min; i<=max; i+=increment) {
				switch (valueType) {
				case SHORT:
					adapter.add(new LabelValuePair(String.valueOf(i), (short)i));
					break;
				case INT: default: {
					adapter.add(new LabelValuePair(String.valueOf(i), i));
				}
				}
			}
		}

		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spinner.setAdapter(adapter);
		spinner.setSelection(selection);
		final int initialSelection = selection;

		// Unfortunately spinner loses some of its UI components when background is set.
		//spinner.setBackgroundColor(property.getBgColor());

		// register a selection listener
		OnItemSelectedListener listener = new OnItemSelectedListener() {
			int currentSelection = initialSelection;
			public void onItemSelected(AdapterView<?> parent, View view, final int pos, long id) {
				if (pos == currentSelection) {
					Log.d(TAG, String.format("Selected position %d already selected. No action required", pos));
				} else {
					LabelValuePair item = adapter.getItem(pos);

					// set the property in a background task
					SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

						@Override
						protected void onFailure(ControlPanelException e) {
							spinner.setSelection(currentSelection);
							if (exceptionHandler != null) {
								// An exception was thrown. Restore old value.
								exceptionHandler.handleControlPanelException(e);
							}
						}

						@Override
						protected void onSuccess() {
							// All went well. Store the new value.
							currentSelection = pos;
						}

					};
					asyncTask.execute(propertyWidget, item.value);
				}
			}

			public void onNothingSelected(AdapterView<?> parent) {
				// Another interface callback
			}
		};
		spinner.setOnItemSelectedListener(listener);

		return spinner;
	}

	// =====================================================================================================================

	private RadioGroup createRadioButtonView(final PropertyWidget propertyWidget)
	{
		Log.d(TAG, "Creating a radio button group for property " + propertyWidget.getLabel());

		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
			Log.d(TAG, "CurrentValue is: " + currentValue);
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}

		RadioGroup radioGroup = new RadioGroup(uiContext);
		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());
		radioGroup.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		final List<ConstrainToValues<?>> listOfConstraint = propertyWidget.getListOfConstraint();
		if ( listOfConstraint != null ) {
			for (ConstrainToValues<?> valueCons : listOfConstraint) {

				boolean isDefault = valueCons.getValue().equals(currentValue);
				Log.d(TAG, "Adding radio button, Label: " + valueCons.getLabel() + " Value: " + valueCons.getValue() + (isDefault?" (default)":""));

				RadioButton radioButton = new RadioButton(uiContext);
				radioButton.setText(valueCons.getLabel());
				LinearLayout.LayoutParams layoutParams = new RadioGroup.LayoutParams(
						RadioGroup.LayoutParams.WRAP_CONTENT,
						RadioGroup.LayoutParams.WRAP_CONTENT);
				radioGroup.addView(radioButton, layoutParams);

				// check the default value
				if (isDefault && !radioButton.isChecked()) {
					radioButton.toggle(); 
				}
			}
		}//LOV constraints

		radioGroup.setBackgroundColor(propertyWidget.getBgColor());

		final int initialCheckedId = radioGroup.getCheckedRadioButtonId();

		// register selection listener
		radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
			int currentCheckedId = initialCheckedId;
			@Override
			public void onCheckedChanged(final RadioGroup group, final int checkedId) {
				int index = group.indexOfChild(group.findViewById(checkedId));
				if (index > -1)
				{
					ConstrainToValues<?> item  = listOfConstraint.get(index);

					// set the property in a background task
					SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

						@Override
						protected void onFailure(ControlPanelException e) {
							group.check(currentCheckedId);
							if (exceptionHandler != null) {
								// An exception was thrown. Restore old value.
								exceptionHandler.handleControlPanelException(e);
							}
						}

						@Override
						protected void onSuccess() {
							// All went well. Store the new value.
							currentCheckedId = checkedId;
						}

					};
					asyncTask.execute(propertyWidget, item.getValue());
				}
			}
		});

		return radioGroup;
	}

	// =====================================================================================================================

	private CheckBox createCheckBoxView(final PropertyWidget propertyWidget)
	{
		Log.d(TAG, "Creating a checkbox for property " + propertyWidget.getLabel());

		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}

		CheckBox checkbox = new CheckBox(uiContext);
		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		checkbox.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());
		if (propertyWidget.getBgColor() != null)
			checkbox.setBackgroundColor(propertyWidget.getBgColor());

		// initialize data
		if (currentValue instanceof Boolean) {
			checkbox.setSelected((Boolean) currentValue);
		}
		checkbox.setText(propertyWidget.getLabel());

		// register selection listener
		OnCheckedChangeListener listener = new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(final CompoundButton buttonView, final boolean isChecked) {

				// set the property in a background task
				SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

					@Override
					protected void onFailure(ControlPanelException e) {
						buttonView.setChecked(!isChecked);
						if (exceptionHandler != null) {
							// An exception was thrown. Restore old value.
							exceptionHandler.handleControlPanelException(e);
						}
					}

					@Override
					protected void onSuccess() {
						// All went well. 
					}

				};
				asyncTask.execute(propertyWidget, isChecked);
			}
		};
		checkbox.setOnCheckedChangeListener(listener );

		return checkbox;
	}

	// =====================================================================================================================

	private View createTextView(final PropertyWidget propertyWidget) {
		String label = propertyWidget.getLabel();
		Integer bgColor = propertyWidget.getBgColor();
		Log.d(TAG, "Creating Label: \"" + label + "\" BGColor: " + bgColor);

		TextView labelView = new TextView(uiContext);
		labelView.setText(label);
		if (bgColor != null)
			labelView.setBackgroundColor(bgColor);

		return labelView;
	}//createTextView

	// =====================================================================================================================

	private View createEditTextView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a text editor for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final EditText valueEditText = new EditText(uiContext);
		valueEditText.setImeOptions(EditorInfo.IME_ACTION_DONE);
		valueEditText.setTag(PROPERTY_EDITOR);
		
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueEditText, hLinearLayoutParams);

		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueEditText.setBackgroundColor(propertyWidget.getBgColor());
		valueEditText.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the current value
		String currentValue = null;
		try {
			Object tempCurrentValue = propertyWidget.getCurrentValue();
			currentValue = (tempCurrentValue == null? "" : tempCurrentValue.toString());
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}

		final String initialValue = currentValue;
		Log.d(TAG, "Setting current value to " + currentValue);
		valueEditText.setText(initialValue);


		// register edit listener
		valueEditText.setInputType(InputType.TYPE_CLASS_TEXT);
		// limit the number of characters
		// editText.setFilters( new InputFilter[] {new InputFilter.LengthFilter(10)});
		valueEditText.setOnEditorActionListener(new OnEditorActionListener() {
			String currentText = initialValue;
			@Override
			public boolean onEditorAction(final TextView v, int actionId, KeyEvent event) {
				if (actionId == EditorInfo.IME_ACTION_DONE) {

					// set the property in a background task
					SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

						@Override
						protected void onFailure(ControlPanelException e) {
							v.setText(currentText);
							if (exceptionHandler != null) {
								// An exception was thrown. Restore old value.
								exceptionHandler.handleControlPanelException(e);
							}
						}

						@Override
						protected void onSuccess() {
							// All went well. Store the new value.
							currentText = v.getText().toString();
						}

					};
					asyncTask.execute(propertyWidget, v.getText().toString());
				}
				// otherwise keyboard remains up
				return false;
			}
		});        	

		return layout;
	}//createEditTextView

	// =====================================================================================================================

	private View createNumericKeypadView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a number text editor for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final EditText valueEditText = new EditText(uiContext);
		valueEditText.setImeOptions(EditorInfo.IME_ACTION_DONE);
		valueEditText.setTag(PROPERTY_EDITOR);
		
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueEditText, hLinearLayoutParams);

		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueEditText.setBackgroundColor(propertyWidget.getBgColor());
		valueEditText.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}

		final ValueType valueType = propertyWidget.getValueType();
		final Number initialValue = (currentValue == null? 0 :
			ValueType.SHORT.equals(valueType) ? ((Short)currentValue) :
				ValueType.INT.equals(valueType) ? ((Integer)currentValue) : 0);
		Log.d(TAG, "Setting current value to " + currentValue);
		valueEditText.setText(String.valueOf(currentValue));

		// register edit listener
		valueEditText.setInputType(InputType.TYPE_CLASS_NUMBER);
		// limit the number of characters
		int maxChars = String.valueOf(Integer.MAX_VALUE).length();
		Log.d(TAG, "Setting maximum input characters to: " +maxChars);

		valueEditText.setFilters( new InputFilter[] {new InputFilter.LengthFilter(maxChars)});
		valueEditText.setOnEditorActionListener(new OnEditorActionListener() {
			Number currentValue = initialValue;
			@Override
			public boolean onEditorAction(final TextView v, int actionId, KeyEvent event) {
				if (actionId == EditorInfo.IME_ACTION_DONE) {

					Number readEnteredValue = null;
					try {
						if (ValueType.SHORT==valueType) {
							readEnteredValue = Short.valueOf(v.getText().toString());
						} else if (ValueType.INT==valueType) {
							readEnteredValue = Integer.valueOf(v.getText().toString());
						}
					} catch (NumberFormatException nfe) {
						Log.e(TAG, "Failed parsing Integer: '" + nfe.getMessage() + "'");
						v.setText(String.valueOf(currentValue));
						return true;
					}

					final Number enteredValue = readEnteredValue;

					// set the property in a background task
					SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

						@Override
						protected void onFailure(ControlPanelException e) {
							v.setText(String.valueOf(currentValue));
							if (exceptionHandler != null) {
								// An exception was thrown. Restore old value.
								exceptionHandler.handleControlPanelException(e);
							}
						}

						@Override
						protected void onSuccess() {
							// All went well. Store the new value.
							currentValue = enteredValue;
						}

					};
					asyncTask.execute(propertyWidget, enteredValue);
				}
				// otherwise keyboard remains up
				return false;
			}
		});        	

		return layout;
	}//createEditTextView

	// =====================================================================================================================

	private View createTimePickerView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a time picker for property " + propertyWidget.getLabel());

		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final Button valueButton = new Button(uiContext);
		valueButton.setTag(PROPERTY_VALUE);
		
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueButton, hLinearLayoutParams);
		
		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueButton.setBackgroundColor(propertyWidget.getBgColor());
		valueButton.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}
		if (currentValue != null && (ValueType.TIME.equals(propertyWidget.getValueType()))) {
			PropertyWidget.Time time = (PropertyWidget.Time) currentValue;
			valueButton.setText(formatTime(time.getHour(), time.getMinute()));
		} else {
			Log.e(TAG, "property.getValueType() is not TIME, initializing property without current value");
		}

		// register time picker dialog listener
		final TimePickerDialog.OnTimeSetListener onTimeSetListener = new TimePickerDialog.OnTimeSetListener() {

			@Override
			public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
				PropertyWidget.Time time = new PropertyWidget.Time();
				time.setHour((short) hourOfDay);
				time.setMinute((short) minute);
				time.setSecond((short) 0);

				// set the property in a background task
				SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

					@Override
					protected void onFailure(ControlPanelException e) {
						if (exceptionHandler != null) {
							// no need to restore value, it hasn't changed.
							exceptionHandler.handleControlPanelException(e);
						}
					}

					@Override
					protected void onSuccess() {
						// don't worry about the result, it will be broadcasted with ValueChanged
						// All went well.
					}

				};
				asyncTask.execute(propertyWidget, time);
			}
		};

		// register click listener
		OnClickListener onClickListener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				// set the current value
				Object currentValue = null;
				PropertyWidget.Time time;
				try {
					currentValue = propertyWidget.getCurrentValue();
				} catch (ControlPanelException e) {
					Log.e(TAG, "property.getCurrentValue() failed, initializing picker without current value", e);
					time = new PropertyWidget.Time();				}
				if (currentValue != null && (ValueType.TIME.equals(propertyWidget.getValueType()))) {
					time = (PropertyWidget.Time) currentValue;
				} else {
					Log.e(TAG, "property.getValueType() is not TIME, initializing picker without current value");
					time = new PropertyWidget.Time();
				}

				// Use the current time as the default values for the picker
				final Calendar c = Calendar.getInstance();
				int hour = currentValue == null? c.get(Calendar.HOUR_OF_DAY) : time.getHour();
				int minute = currentValue == null? c.get(Calendar.MINUTE) : time.getMinute();

				// Pop a TimePickerDialog
				new TimePickerDialog(uiContext, onTimeSetListener, hour, minute,
						DateFormat.is24HourFormat(uiContext)).show();
			}
		};
		valueButton.setOnClickListener(onClickListener);

		return layout;
	}//createTimePickerView

	// =====================================================================================================================

	private View createDatePickerView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a date picker for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final Button valueButton = new Button(uiContext);
		valueButton.setTag(PROPERTY_VALUE);
		
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueButton, hLinearLayoutParams);

		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueButton.setBackgroundColor(propertyWidget.getBgColor());
		valueButton.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}
		if (currentValue != null && (ValueType.DATE.equals(propertyWidget.getValueType()))) {
			PropertyWidget.Date date = (PropertyWidget.Date) currentValue;
			valueButton.setText(formatDate(date.getDay(), date.getMonth(), date.getYear()));
		} else {
			Log.e(TAG, "property.getValueType() is not DATE, initializing property without current value");
		}

		// register time picker dialog listener
		final DatePickerDialog.OnDateSetListener onDateSetListener = new DatePickerDialog.OnDateSetListener() {

			@Override
			public void onDateSet(DatePicker view, int year, int month, int day) {
				PropertyWidget.Date date = new PropertyWidget.Date();

				// DatePicker enums months from 0..11 :(
				month++;

				date.setDay((short) day);
				date.setMonth((short) month);
				date.setYear((short) year);

				// set the property in a background task
				SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

					@Override
					protected void onFailure(ControlPanelException e) {
						if (exceptionHandler != null) {
							// no need to restore value, it hasn't changed.
							exceptionHandler.handleControlPanelException(e);
						}
					}

					@Override
					protected void onSuccess() {
						// don't worry about the result, it will be broadcasted with ValueChanged
						// All went well.
					}

				};
				asyncTask.execute(propertyWidget, date);
			}
		};

		// register click listener
		OnClickListener onClickListener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				// set the current value
				Object currentValue = null;
				PropertyWidget.Date date;
				try {
					currentValue = propertyWidget.getCurrentValue();
				} catch (ControlPanelException e) {
					Log.e(TAG, "property.getCurrentValue() failed, initializing picker without current value", e);
					date = new PropertyWidget.Date();				}
				if (currentValue != null && (ValueType.DATE.equals(propertyWidget.getValueType()))) {
					date = (PropertyWidget.Date) currentValue;
				} else {
					Log.e(TAG, "property.getValueType() is not DATE, initializing picker without current value");
					date = new PropertyWidget.Date();
				}

				// Use the current date as the default values for the picker
				final Calendar c = Calendar.getInstance();
				int day = currentValue == null? c.get(Calendar.DAY_OF_MONTH) : date.getDay();
				int month = currentValue == null? c.get(Calendar.MONTH) : date.getMonth();
				int year = currentValue == null? c.get(Calendar.YEAR) : date.getYear();

				// DatePicker enums months from 0..11 :(
				month--;
				// Pop a DatePickerDialog
				new DatePickerDialog(uiContext, onDateSetListener, year, month, day).show();
			}
		};
		valueButton.setOnClickListener(onClickListener);

		return layout;
	}//createTimePickerView

	// =====================================================================================================================

	private View createNumberPickerView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a number picker for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final TextView valueTextView = new TextView(uiContext);
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueTextView, hLinearLayoutParams);

		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueTextView.setBackgroundColor(propertyWidget.getBgColor());
		valueTextView.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		RangeConstraint<?> propertyRangeConstraint = propertyWidget.getPropertyRangeConstraint();
		if (propertyRangeConstraint == null) {
			Log.e(TAG, "Found null property-range. Disabling Number Picker. Returning a plain label.");
			valueTextView.setEnabled(false);
			return layout;
		}

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}
		if (currentValue != null) {
			valueTextView.setText(currentValue.toString());
		}

		// register touch listener
		/*	Only in honeycomb 3.0 	
		final int min = (Integer) propertyRangeConstraint.getMin();
		final int max = (Integer) propertyRangeConstraint.getMax();
		//final int increment = (Integer) propertyRangeConstraint.getIncrement();
   numericTextView.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch (View v, MotionEvent event) {
				if (event.getAction() == MotionEvent.ACTION_DOWN) {

					final NumberPicker picker = new NumberPicker(uiContext);
					picker.setMaxValue(max);
					picker.setMinValue(min);
					picker.setValue(Integer.valueOf(numericTextView.getText().toString()));
					AlertDialog alertDialog = new AlertDialog.Builder(uiContext)
					.setView(picker)
					.setTitle(propertyWidget.getLabel())
					.setPositiveButton(R.string.dialog_set, new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int whichButton) {
			            	setPropertyValue(propertyWidget, picker.getValue());
							numericTextView.setText(String.valueOf(picker.getValue()));
						}})
						.setNegativeButton(R.string.dialog_cancel, null).create();
					alertDialog.show();
					return true;
				}
				return false;
			}
		});

		 */
		return layout;
	}

	// =====================================================================================================================

	private View createNumericView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a numberic view for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final TextView valueTextView = new TextView(uiContext);
		valueTextView.setTag(PROPERTY_VALUE);
		
		layout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		layout.addView(valueTextView, hLinearLayoutParams);

		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		if (propertyWidget.getBgColor() != null)
			valueTextView.setBackgroundColor(propertyWidget.getBgColor());
		valueTextView.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}
		if (currentValue != null) {
			Log.d(TAG, "Setting property value to: " + currentValue.toString());
			valueTextView.setText(currentValue.toString());
		}

		return layout;
	}

	// =====================================================================================================================

	private View createSliderView(final PropertyWidget propertyWidget) {
		Log.d(TAG, "Creating a slider for property " + propertyWidget.getLabel());

		// create the label
		final LinearLayout layout = new LinearLayout(uiContext);
		layout.setOrientation(LinearLayout.VERTICAL);
		final LinearLayout innerLayout = new LinearLayout(uiContext);
		innerLayout.setOrientation(LinearLayout.HORIZONTAL);
		final TextView nameTextView = new TextView(uiContext);
		nameTextView.setText(propertyWidget.getLabel());
		final TextView valueTextView = new TextView(uiContext);
		valueTextView.setTag(PROPERTY_VALUE);
		final TextView unitsOfMeasureTextView =  new TextView(uiContext);
		final SeekBar slider = new SeekBar(uiContext);
		slider.setTag(PROPERTY_EDITOR);

		innerLayout.addView(nameTextView);
		LinearLayout.LayoutParams hLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		hLinearLayoutParams.setMargins(10, 0, 0, 0);
		innerLayout.addView(valueTextView, hLinearLayoutParams);
		innerLayout.addView(unitsOfMeasureTextView, hLinearLayoutParams);

		LinearLayout.LayoutParams vLinearLayoutParams = new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		layout.addView(innerLayout, vLinearLayoutParams);
		layout.addView(slider, vLinearLayoutParams);
		
		Log.d(TAG, "Property isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());

		// initialize meta data
		valueTextView.setBackgroundColor(propertyWidget.getBgColor());
		valueTextView.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());

		String unitOfMeasure = propertyWidget.getUnitOfMeasure();
		Log.d(TAG, "Setting property units of measure to: " + unitOfMeasure);
		unitsOfMeasureTextView.setText(unitOfMeasure);

		// set the current value
		Object currentValue = null;
		try {
			currentValue = propertyWidget.getCurrentValue();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.getCurrentValue() failed, initializing property without current value", e);
		}

		RangeConstraint<?> propertyRangeConstraint = propertyWidget.getPropertyRangeConstraint();
		if (propertyRangeConstraint == null) {
			Log.e(TAG, "Found null property-range. Disabling Number Picker. Returning a plain label.");
			return new TextView(uiContext);
		}

		// set the current value
		ValueType valueType = propertyWidget.getValueType();
		final int initialValue = (currentValue == null? 0 :
			ValueType.SHORT.equals(valueType) ? ((Short)currentValue) :
				ValueType.INT.equals(valueType) ? ((Integer)currentValue) : 0);

		// unused. Android sliders always start from 0
		//final int min = (Integer) propertyRangeConstraint.getMin();
		Object maxT = propertyRangeConstraint.getMax();
		final int max = 
				ValueType.SHORT.equals(valueType) ? ((Short)maxT) :
					ValueType.INT.equals(valueType) ? ((Integer)maxT) : 0;	
		Object incrementT = propertyRangeConstraint.getIncrement();
		final int increment = 
				ValueType.SHORT.equals(valueType) ? ((Short)incrementT) :
					ValueType.INT.equals(valueType) ? ((Integer)incrementT) : 0;	

		slider.setMax(max);
		slider.setKeyProgressIncrement(increment);
		Log.d(TAG, "Setting property value to: " + String.valueOf(currentValue));
		slider.setProgress(initialValue);
		valueTextView.setText(String.valueOf(initialValue));

		slider.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

			int currentProgress = initialValue;
			@Override
			public void onStopTrackingTouch(final SeekBar seekBar) {

				// set the property in a background task
				SetPropertyAsyncTask asyncTask = new SetPropertyAsyncTask() {

					@Override
					protected void onFailure(ControlPanelException e) {
						seekBar.setProgress(currentProgress);
						if (exceptionHandler != null) {
							// An exception was thrown. Restore old value.
							exceptionHandler.handleControlPanelException(e);
						}
					}

					@Override
					protected void onSuccess() {
						// All went well. Store the new value.
						currentProgress = seekBar.getProgress();
					}
					
				};
				asyncTask.execute(propertyWidget, seekBar.getProgress());
			}

			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {}

			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				valueTextView.setText(String.valueOf(progress));									}
		});

		return layout;
	}

	// =====================================================================================================================

	/**
	 * A callback that is invoked when the meta data of a UIElement has changed. 
	 * Refreshes the UIElement and the corresponding View.  
	 * @param element the abstract UIElement
	 */
	public void onMetaDataChange(UIElement element) {
		UIElementType elementType = element.getElementType();
		Log.d(TAG, "Refreshing the Android View for element : '" + element.getObjectPath() + "'");

		switch(elementType) {
		case ACTION_WIDGET: {
			onActionMetaDataChange((ActionWidget)element);
			break;
		}//ACTION_WIDGET
		case CONTAINER: {
			onContainerMetaDataChange((ContainerWidget) element);
			break;
		}// CONTAINER
		//			case LIST_PROPERTY_WIDGET: {
		//				break;
		//			}//LIST_PROPERTY_WIDGET
		case PROPERTY_WIDGET: {
			onPropertyMetaDataChange((PropertyWidget) element);
			break;
		}//PROPERTY_WIDGET
		case ALERT_DIALOG: {
			onAlertDialogMetaDataChange((AlertDialogWidget) element);
			break;
		}//PROPERTY_WIDGET
		default:
			break;
		}//switch :: elementType
	}

	// =====================================================================================================================

	private void onContainerMetaDataChange(ContainerWidget container) {
		if ( container == null ) {
			Log.e(TAG, "onContainerMetaDataChange");
			return;
		}
		// refresh the container properties
		try {
			container.refreshProperties();
		} catch (ControlPanelException e) {
			Log.e(TAG, "container.refreshProperties() failed", e);
			// ====
			return;
		}

		// get a handle to the corresponding view
		ViewGroup containerLayout = (ViewGroup) uiElementToView.get(container.getObjectPath());
		if (containerLayout == null) 
		{
			Log.d(TAG, "ViewGroup not found for widget " + container.getObjectPath());
			return;
		}

		boolean enabled = container.isEnabled();
		Log.d(TAG,"Refreshing ContainerWidget bgColor:  " + container.getBgColor() + " enabled: "+ enabled);
		if (container.getBgColor() != null)
			containerLayout.setBackgroundColor(container.getBgColor());

		containerLayout.setEnabled(enabled);
	}

	// =====================================================================================================================

	private void onActionMetaDataChange(final ActionWidget actionWidget) {

		// refresh the action properties
		try {
			actionWidget.refreshProperties();
		} catch (ControlPanelException e) {
			Log.e(TAG, "action.refreshProperties() failed", e);
			// ====
			return;
		}

		// get a handle to the corresponding view
		Button actionButton = (Button) uiElementToView.get(actionWidget.getObjectPath());
		if (actionButton == null) 
		{
			Log.d(TAG, "Button not found for widget " + actionWidget.getObjectPath());
			return;
		}

		String label = actionWidget.getLabel();
		Integer bgColor = actionWidget.getBgColor();
		boolean enabled = actionWidget.isEnabled();

		Log.d(TAG, "Refreshing ActionWidget: Label: " + label + " BGColor: " + bgColor + " Enabled: " + enabled);

		actionButton.setText(label);
		actionButton.setEnabled(enabled);
		if (bgColor != null)
			actionButton.setBackgroundColor(bgColor);

	}//onActionMetaDataChange

	// =====================================================================================================================

	private void onAlertDialogMetaDataChange(final AlertDialogWidget alertDialogWidget) {

		// refresh the widget properties
		try {
			alertDialogWidget.refreshProperties();
		} catch (ControlPanelException e) {
			Log.e(TAG, "alertDialogWidget.refreshProperties() failed", e);
			// ====
			return;
		}

		// get a handle to the corresponding AlertDialog
		AlertDialog alertDialog = (AlertDialog) alertWidgetToDialog.get(alertDialogWidget.getObjectPath());
		if (alertDialog == null) 
		{
			Log.d(TAG, "AlertDialog not found for widget " + alertDialogWidget.getObjectPath());
			return;
		}

		if (!alertDialogWidget.isEnabled() && alertDialog.isShowing()) {
			Log.d(TAG, "Dismissing AlertDialog");
			alertDialog.dismiss();
		}
	}//onAlertDialogMetaDataChange

	// =====================================================================================================================

	private void onPropertyMetaDataChange(PropertyWidget propertyWidget) {

		// refresh the property
		try {
			propertyWidget.refreshProperties();
		} catch (ControlPanelException e) {
			Log.e(TAG, "property.refreshProperties() failed", e);
			// ====
			return;
		}

		// get a handle to the corresponding view
		View propertyView = (View) uiElementToView.get(propertyWidget.getObjectPath());
		if (propertyView == null) 
		{
			Log.d(TAG, "Property View not found for widget " + propertyWidget.getObjectPath());
			return;
		}

		Log.d(TAG, "Refreshing the view of property '" + propertyWidget.getLabel() + "' isWritable? " + propertyWidget.isWritable() + ", isEnabled? " + propertyWidget.isEnabled());
		propertyView.setEnabled(propertyWidget.isEnabled() && propertyWidget.isWritable());
		if (!(propertyView instanceof Spinner)) {
			if (propertyWidget.getBgColor() != null)
				propertyView.setBackgroundColor(propertyWidget.getBgColor());
		}
	}

	// =====================================================================================================================

	/**
	 * A callback that is invoked when a value of a UIElement has changed. 
	 * Refreshes the UIElement and the corresponding View.  
	 * @param element the abstract UIElement
	 * @param newValue the new value
	 */
	public void onValueChange(UIElement element, Object newValue) {
		UIElementType elementType = element.getElementType();
		Log.d(TAG, "Value changed for the Android View for element : '" + element.getObjectPath() + "'");

		switch(elementType) {
		case PROPERTY_WIDGET: {
			onPropertyValueChange((PropertyWidget) element, newValue);
			break;
		}//PROPERTY_WIDGET
		case ACTION_WIDGET: {
			Log.d(TAG, "Ignoring change of value for action : '" + element.getObjectPath() + "'");
			break;
		}//ACTION_WIDGET
		case CONTAINER: {
			Log.d(TAG, "Ignoring change of value for container : '" + element.getObjectPath() + "'");
			break;
		}// CONTAINER
		//			case LIST_PROPERTY_WIDGET: {
		//				break;
		//			}//LIST_PROPERTY_WIDGET
		default:
			break;
		}//switch :: elementType
	}

	// =====================================================================================================================

	/**
	 * A callback that is invoked when a value of a property has changed. Refreshes the property and the corresponding View.  
	 * @param propertyWidget the property whose value has changed.
	 * @param newValue new value for the property
	 */
	private void onPropertyValueChange(PropertyWidget propertyWidget, Object newValue) {

		// get a handle to the corresponding view
		View propertyView = (View) uiElementToView.get(propertyWidget.getObjectPath());
		if (propertyView == null) 
		{
			Log.d(TAG, "Property View not found for widget " + propertyWidget.getObjectPath());
			return;
		}
		if (newValue == null) {
			Log.e(TAG, "onPropertyValueChange() failed, new value is null");
			// ====
			return;
		}

		for (PropertyWidgetHintsType hint: propertyWidget.getHints()) {
			switch(hint) {
			case SPINNER:
				onSpinnerValueChange(propertyView, propertyWidget, newValue);
				break;
			case CHECKBOX:
				onCheckBoxValueChange(propertyView, propertyWidget, newValue);
				break;
			case SLIDER:
				onSliderValueChange(propertyView, propertyWidget, newValue);
				break;
			case NUMERIC_VIEW: 
				onNumericViewValueChange(propertyView, propertyWidget, newValue);
				break;
			case TEXT_VIEW:
				onTextViewValueChange(propertyView, propertyWidget, newValue);
				break;
				//			case NUMBER_PICKER: HoneyComb 3.0
				//				returnView = createNumberPickerView(property, uiContext);
				//				break;
			case EDIT_TEXT:
				onEditTextValueChange(propertyView, propertyWidget, newValue);
				break;
			case NUMERIC_KEYPAD:
				onNumericKeypadValueChange(propertyView, propertyWidget, newValue);
				break;
			case RADIO_BUTTON:
				onRadioButtonValueChange(propertyView, propertyWidget, newValue);
				break;
			case TIME_PICKER:
				onTimeValueChange(propertyView, propertyWidget, newValue);
				break;
			case DATE_PICKER:
				onDateValueChange(propertyView, propertyWidget, newValue);
				break;
			default:
				break;
			}
		}
	}

	// =====================================================================================================================

	private void onSliderValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue2) {
		ViewGroup layout = (ViewGroup) propertyView;
		final TextView valueTextView = (TextView) layout.findViewWithTag(PROPERTY_VALUE);
		final SeekBar slider = (SeekBar) layout.findViewWithTag(PROPERTY_EDITOR);
		Log.d(TAG, "Refreshing the value of property " + propertyWidget.getLabel());

		// set the current value
		ValueType valueType = propertyWidget.getValueType();
		int newValue = -1;
		switch (valueType) {
		case SHORT: 
			newValue = (Short)newValue2;
			break;
		case INT: 
			newValue = (Integer)newValue2;
			break;
		default:
			Log.e(TAG, "property.getValueType() has unexpected value type: " + valueType);
			// ====
			return;
		}			

		// set value
		valueTextView.setText(String.valueOf(newValue));
		slider.setProgress(newValue);
	}

	// =====================================================================================================================

	private void onCheckBoxValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {
		Log.d(TAG, "Refreshing the CheckBox of property " + propertyWidget.getLabel());

		CheckBox checkbox = (CheckBox) propertyView;
		ValueType valueType = propertyWidget.getValueType();

		// set checked
		if (ValueType.BOOLEAN.equals(valueType)) {
			checkbox.setChecked((Boolean)newValue);
		} else {
			Log.e(TAG, "property.getCurrentValue() failed, cannot update property with value: " + newValue);
		}
	}

	// =====================================================================================================================

	private void onTextViewValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		String label = newValue.toString();
		Log.d(TAG, "Refreshing the TextView of property " + label);

		// set the text of the label
		TextView labelView = (TextView) propertyView;
		labelView.setText(label);
	}

	// =====================================================================================================================

	private void onNumericViewValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		Log.d(TAG, "Refreshing the NumericView of property " + propertyWidget.getLabel());

		// extract the text view
		final ViewGroup layout = (ViewGroup) propertyView;
		final TextView valueTextView = (TextView) layout.findViewWithTag(PROPERTY_VALUE);

		// set the current value
		Log.d(TAG, "Setting property value to: " + newValue.toString());
		valueTextView.setText(newValue.toString());

	}

	// =====================================================================================================================

	private void onNumericKeypadValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		Log.d(TAG, "Refreshing the NumericKeypad View of property " + propertyWidget.getLabel());

		// extract the text view
		final ViewGroup layout = (ViewGroup) propertyView;
		final EditText valueEditText = (EditText) layout.findViewWithTag(PROPERTY_EDITOR);

		// set the current value
		Log.d(TAG, "Setting property value to: " + newValue.toString());
		valueEditText.setText(newValue.toString());
	}

	// =====================================================================================================================

	private void onTimeValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		Log.d(TAG, "Refreshing the Time View of property " + propertyWidget.getLabel());

		// extract the text view
		final ViewGroup layout = (ViewGroup) propertyView;
		final Button valueButton = (Button) layout.findViewWithTag(PROPERTY_VALUE);

		// set the current value
		if (ValueType.TIME.equals(propertyWidget.getValueType())) {
			PropertyWidget.Time time = (PropertyWidget.Time) newValue;
			String formattedTime = formatTime(time.getHour(), time.getMinute());
			Log.d(TAG, "Setting property value to: " + formattedTime);
			valueButton.setText(formattedTime);
		} else {
			Log.e(TAG, "property.getValueType() is not TIME, cannot update property with new value: " + newValue);
		}
	}

	// =====================================================================================================================

	private void onDateValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		Log.d(TAG, "Refreshing the Date View of property " + propertyWidget.getLabel());

		// extract the text view
		final ViewGroup layout = (ViewGroup) propertyView;
		final Button valueButton = (Button) layout.findViewWithTag(PROPERTY_VALUE);

		// set the current value
		if (ValueType.DATE.equals(propertyWidget.getValueType())) {
			PropertyWidget.Date date = (PropertyWidget.Date) newValue;
			String formattedDate = formatDate(date.getDay(), date.getMonth(), date.getYear());
			Log.d(TAG, "Setting property value to: " + formattedDate);
			valueButton.setText(formattedDate);
		} else {
			Log.e(TAG, "property.getValueType() is not DATE,  cannot update property with current value: " + newValue);
		} 
	}

	// =====================================================================================================================

	private void onEditTextValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {	
		Log.d(TAG, "Refreshing the EditText View of property " + propertyWidget.getLabel());

		// extract the text view
		final ViewGroup layout = (ViewGroup) propertyView;
		final EditText valueEditText = (EditText) layout.findViewWithTag(PROPERTY_EDITOR);

		// set the current value
		Log.d(TAG, "Setting property value to: " + newValue.toString());
		valueEditText.setText(newValue.toString());
	}

	// =====================================================================================================================

	private void onSpinnerValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {
		Spinner spinner = (Spinner) propertyView;
		Log.d(TAG, "Refreshing the spinner of property " + propertyWidget.getLabel());

		// set the selected item
		int selection = 0;
		@SuppressWarnings("unchecked")
		final ArrayAdapter<LabelValuePair> adapter = (ArrayAdapter<LabelValuePair>) spinner.getAdapter();
		for (int i=0; i< adapter.getCount(); i++)
		{
			LabelValuePair item = adapter.getItem(i);
			if (item != null && item.value.equals(newValue)) {
				selection = i;
				break;
			}
		}
		spinner.setSelection(selection);
		adapter.notifyDataSetChanged();
	}

	// =====================================================================================================================

	private void onRadioButtonValueChange(View propertyView, PropertyWidget propertyWidget, Object newValue) {
		Log.d(TAG, "Refreshing the RadioButton of property " + propertyWidget.getLabel());

		RadioGroup radioGroup = (RadioGroup) propertyView;

		// set the selected item
		int selection = 0;
		final List<ConstrainToValues<?>> listOfConstraint = propertyWidget.getListOfConstraint();
		if ( listOfConstraint != null ) {
			for (ConstrainToValues<?> valueCons : listOfConstraint) {
				boolean isDefault = valueCons.getValue().equals(newValue);
				Log.d(TAG, "Adding radio button, Label: " + valueCons.getLabel() + " Value: " + valueCons.getValue() + (isDefault?" (default)":""));

				// check the default value
				if (isDefault) {
					RadioButton radioButton = (RadioButton) radioGroup.getChildAt(selection);
					if (!radioButton.isChecked()) {
						radioButton.toggle();
					}
				} else {
					selection++;
				}

			}
		}//LOV constraints
	}

	// =====================================================================================================================

	/**
	 * A wrapper class for hosting a {label,value} pair inside an ArrayAdapter.
	 * So that the label is displayed, while practically the real value is used.
	 */
	class LabelValuePair {

		final String label;
		final Object value;

		public LabelValuePair(String label, Object value) {
			super();
			this.value = value;
			this.label = label;
		}

		@Override
		// This does the trick of displaying the label and not the value in the Adapter
		public String toString() {
			return label;
		}
	}

	/**
	 * A utility method that formats time for display, following the user's locale as given by context 
	 * @param hour
	 * @param minute
	 * @return
	 */
	private String formatTime(short hour, short minute) {
		Calendar calendar = new GregorianCalendar();
		calendar.setTimeInMillis(System.currentTimeMillis());
		calendar.set(Calendar.HOUR_OF_DAY, hour);
		calendar.set(Calendar.MINUTE, minute);
		return DateFormat.getTimeFormat(uiContext.getApplicationContext()).format(calendar.getTime());
		//return String.format("%02d", hour) + ":" +  String.format("%02d", minute);
	}

	/**
	 *  A utility method that formats dates for display, following the user's locale as given by context
	 * @param day
	 * @param month
	 * @param year
	 * @return
	 */
	private String formatDate(short day, short month, short year) {
		Calendar calendar = new GregorianCalendar(year, month, day);
		return DateFormat.getDateFormat(uiContext.getApplicationContext()).format(calendar.getTime());
	}

}