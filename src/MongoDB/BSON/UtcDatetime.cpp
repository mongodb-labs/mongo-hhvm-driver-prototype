/**
 *  Copyright 2014-2015 MongoDB, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "hphp/runtime/ext/extension.h"
#include "hphp/runtime/vm/native-data.h"

#include "hphp/runtime/ext/datetime/ext_datetime.h"

#include "UtcDatetime.h"

namespace HPHP {

const StaticString s_MongoBsonUtcDatetime_className("MongoDB\\BSON\\UtcDatetime");

const StaticString s_MongoBsonUtcDatetime_milliseconds("milliseconds");

const StaticString s_DateTime("DateTime");

Object HHVM_METHOD(MongoDBBsonUtcDatetime, toDateTime)
{
	static HPHP::Class* c_dt;
	int64_t milliseconds = this_->o_get(s_MongoBsonUtcDatetime_milliseconds, false, s_MongoBsonUtcDatetime_className).toInt64();

	/* Prepare result */
	c_dt = HPHP::Unit::lookupClass(HPHP::s_DateTime.get());
	assert(c_dt);
	HPHP::ObjectData* obj = HPHP::ObjectData::newInstance(c_dt);

	DateTimeData* data = Native::data<DateTimeData>(obj);
	data->m_dt = makeSmartPtr<DateTime>(0, false);
	data->m_dt->fromTimeStamp(milliseconds / 1000, true);

	return obj;
}

}
