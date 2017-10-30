/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */

#ifndef OPENDNP3_EVENTRECORD_H
#define OPENDNP3_EVENTRECORD_H

#include "opendnp3/app/EventType.h"
#include "opendnp3/outstation/EventState.h"
#include "opendnp3/app/MeasurementTypeSpecs.h"

#include "openpal/container/LinkedList.h"


namespace opendnp3
{
	template <class T>
	struct TypedEventRecord;

	/**
	* Generic event information with an opaque pointer to 
	* the specific event details
	*/
	class EventRecord
	{

	public:
		EventRecord(
		    uint16_t index,
		    EventClass clazz
		) :
			
			index(index),
			clazz(clazz)
		{}

		EventRecord() = default;

		template <class T>
		void SetStorageNode(openpal::ListNode<TypedEventRecord<T>>* node)
		{
			this->type = typename T::EventTypeEnum;
			this->storage_node = node;
		}

		uint16_t index = 0;
		EventClass clazz = EventClass::EC1;
		EventState state = EventState::unselected;

		template <class T>
		uint32_t Select(T& selector)
		{
			if (!this->storage) return 0;

			switch (type)
			{
				case(EventType::Binary):
					return selector.handle(reinterpret_cast<openpal::ListNode<BinarySpec>*>(this->storage_node));
				case(EventType::DoubleBitBinary):
					return selector.handle(reinterpret_cast<openpal::ListNode<DoubleBitBinarySpec>*>(this->storage_node));
				case(EventType::Counter):
					return selector.handle(reinterpret_cast<openpal::ListNode<CounterSpec>*>(this->storage_node));
				case(EventType::FrozenCounter):
					return selector.handle(reinterpret_cast<openpal::ListNode<FrozenCounterSpec>*>(this->storage_node));
				case(EventType::Analog):
					return selector.handle(reinterpret_cast<openpal::ListNode<AnalogSpec>*>(this->storage_node));
				case(EventType::BinaryOutputStatus):
					return selector.handle(reinterpret_cast<openpal::ListNode<BinaryOutputStatusSpec>*>(this->storage_node));
				case(EventType::AnalogOutputStatus):
					return selector.handle(reinterpret_cast<openpal::ListNode<AnalogOutputStatusSpec>*>(this->storage_node));
				default:
					return 0;
			}
		}
		
	private:
		EventType type = EventType::Binary;
		void* storage_node = nullptr;
	};

}

#endif

