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

#include "alljoyn/controlpanel/Widgets/ListPropertyWidget.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"
#include "alljoyn/controlpanel/Common/DateTimeUtil.h"

#define NOT_LOCKED "Not Locked"
#define LOCK_TIMEOUT 60000

void initializeListPropertyWidget(ListPropertyWidget* widget)
{
    initializeBaseWidget(&widget->base);

    widget->addRecord = 0;
    widget->cancelRecord = 0;
    widget->confirmRecord = 0;
    widget->deleteRecord = 0;
    widget->updateRecord = 0;
    widget->viewRecord = 0;

    widget->getNumRecords = 0;
    widget->getRecordId = 0;
    widget->getRecordName = 0;

    widget->base.marshalAllProp = &marshalAllListPropertyProperties;

    strncpy(widget->currentViewer, NOT_LOCKED, SENDER_ID_LENGTH);
}

AJ_Status marshalListPropertyValue(ListPropertyWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg arrayArg;
    uint16_t indx;

    if (!widget->getNumRecords || !widget->getRecordId || !widget->getRecordName)
        return AJ_ERR_FAILURE;

    CPS_CHECK(AJ_MarshalContainer(reply, &arrayArg, AJ_ARG_ARRAY));

    for (indx = 0; indx < widget->getNumRecords(); indx++) {
        AJ_Arg structArg;
        CPS_CHECK(AJ_MarshalContainer(reply, &structArg, AJ_ARG_STRUCT));

        uint16_t recordId = widget->getRecordId(indx);
        char* recordName = widget->getRecordName(indx);
        if (recordName == 0)
            return AJ_ERR_FAILURE;

        CPS_CHECK(AJ_MarshalArgs(reply, "qs", recordId, recordName));
        CPS_CHECK(AJ_MarshalCloseContainer(reply, &structArg));
    }
    return AJ_MarshalCloseContainer(reply, &arrayArg);
}

AJ_Status marshalAllListPropertyProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg listPropertyGetAllArray;

    CPS_CHECK(AJ_MarshalContainer(reply, &listPropertyGetAllArray, AJ_ARG_ARRAY));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_VERSION_NAME, PROPERTY_TYPE_VERSION_SIG,
                                   widget, language, &marshalBaseVersion));

    CPS_CHECK(marshalAllBaseProperties(widget, reply, language));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG,
                                   widget, language, &marshalOnlyBaseOptParam));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_VALUE_NAME, LISTPROPERTY_VALUE_SIG,
                                   widget, language, &marshalListPropertyValue));

    return AJ_MarshalCloseContainer(reply, &listPropertyGetAllArray);
}

AJ_Status checkLock(ListPropertyWidget* widget, const char* lockerId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK((lockerId == 0));

    if (strcmp(widget->currentViewer, NOT_LOCKED) == 0) {   // not locked at all
        strncpy(widget->currentViewer, lockerId, SENDER_ID_LENGTH);
        AJ_InitTimer(&widget->lockTimer);
        return AJ_OK;
    }

    if (strcmp(widget->currentViewer, lockerId) == 0) {   // locked by current user
        AJ_InitTimer(&widget->lockTimer);
        return AJ_OK;
    }

    if (AJ_GetElapsedTime(&widget->lockTimer, TRUE) > LOCK_TIMEOUT) {   // locked by someone else
                                                                        // but there's a timeout
        strncpy(widget->currentViewer, lockerId, SENDER_ID_LENGTH);
        AJ_InitTimer(&widget->lockTimer);
        return AJ_OK;
    }

    return status;
}

static void unLock(ListPropertyWidget* widget)
{
    strncpy(widget->currentViewer, NOT_LOCKED, SENDER_ID_LENGTH);
}

AJ_Status addRecord(ListPropertyWidget* widget, const char* lockerId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->addRecord == 0));

    return widget->addRecord() ? AJ_OK : AJ_ERR_FAILURE;
}

AJ_Status viewRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->viewRecord == 0));

    return widget->viewRecord(recordId) ? AJ_OK : AJ_ERR_FAILURE;
}

AJ_Status updateRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->updateRecord == 0));


    return widget->updateRecord(recordId) ? AJ_OK : AJ_ERR_FAILURE;
}

AJ_Status deleteRecord(ListPropertyWidget* widget, const char* lockerId, uint16_t recordId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->deleteRecord == 0));

    return widget->deleteRecord(recordId) ? AJ_OK : AJ_ERR_FAILURE;

}

AJ_Status confirmRecord(ListPropertyWidget* widget, const char* lockerId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->confirmRecord == 0));

    uint8_t success = widget->confirmRecord();
    unLock(widget);

    return success ? AJ_OK : AJ_ERR_FAILURE;
}

AJ_Status cancelRecord(ListPropertyWidget* widget, const char* lockerId)
{
    AJ_Status status = AJ_ERR_FAILURE;

    CPS_CHECK(checkLock(widget, lockerId));
    CPS_CHECK((widget->cancelRecord == 0));

    uint8_t success = widget->cancelRecord();
    unLock(widget);

    return success ? AJ_OK : AJ_ERR_FAILURE;
}
