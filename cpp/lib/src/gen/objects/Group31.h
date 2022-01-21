//
//  _   _         ______    _ _ _   _             _ _ _
// | \ | |       |  ____|  | (_) | (_)           | | | |
// |  \| | ___   | |__   __| |_| |_ _ _ __   __ _| | | |
// | . ` |/ _ \  |  __| / _` | | __| | '_ \ / _` | | | |
// | |\  | (_) | | |___| (_| | | |_| | | | | (_| |_|_|_|
// |_| \_|\___/  |______\__,_|_|\__|_|_| |_|\__, (_|_|_)
//                                           __/ |
//                                          |___/
// 
// This file is auto-generated. Do not edit manually
// 
// Copyright 2013-2020 Automatak, LLC
// 
// Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
// LLC (www.automatak.com) under one or more contributor license agreements.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership. Green Energy Corp and Automatak LLC license
// this file to you under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may obtain
// a copy of the License at:
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef OPENDNP3_Group31_H
#define OPENDNP3_Group31_H

#include "opendnp3/app/GroupVariationID.h"
#include <ser4cpp/container/SequenceTypes.h>
#include "opendnp3/app/DNPTime.h"
#include "app/DNP3Serializer.h"
#include "app/MeasurementTypeSpecs.h"

namespace opendnp3 {

// FrozenAnalog Input - Any Variation
struct Group31Var0
{
  static GroupVariationID ID() { return GroupVariationID(31,0); }
};

// Frozen Analog Input - 32-bit With Flag
struct Group31Var1
{
  static GroupVariationID ID() { return GroupVariationID(31,1); }

  Group31Var1();

  static size_t Size() { return 5; }
  static bool Read(ser4cpp::rseq_t&, Group31Var1&);
  static bool Write(const Group31Var1&, ser4cpp::wseq_t&);

  typedef int32_t ValueType;
  uint8_t flags;
  int32_t value;

  typedef FrozenAnalog Target;
  typedef FrozenAnalogSpec Spec;
  static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
  static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
  static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
  static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var1;
};

// Frozen Analog Input - 16-bit With Flag
struct Group31Var2
{
  static GroupVariationID ID() { return GroupVariationID(31,2); }

  Group31Var2();

  static size_t Size() { return 3; }
  static bool Read(ser4cpp::rseq_t&, Group31Var2&);
  static bool Write(const Group31Var2&, ser4cpp::wseq_t&);

  typedef int16_t ValueType;
  uint8_t flags;
  int16_t value;

  typedef FrozenAnalog Target;
  typedef FrozenAnalogSpec Spec;
  static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
  static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
  static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
  static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var2;
};

// Frozen Analog Input - 32-bit With Flag and Time
struct Group31Var3
{
	static GroupVariationID ID() { return GroupVariationID(31, 3); }

	Group31Var3();

	static size_t Size() { return 11; }
	static bool Read(ser4cpp::rseq_t&, Group31Var3&);
	static bool Write(const Group31Var3&, ser4cpp::wseq_t&);

	typedef uint32_t ValueType;
	uint8_t flags;
	uint32_t value;
	DNPTime time;

	typedef FrozenAnalog Target;
	typedef FrozenAnalogSpec Spec;
	static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
	static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
	static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
	static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var3;
};

// Frozen Analog Input - 16-bit With Time
// Frozen Analog Input - 16-bit With Flag and Time
struct Group31Var4
{
	static GroupVariationID ID() { return GroupVariationID(31, 4); }

	Group31Var4();

	static size_t Size() { return 9; }
	static bool Read(ser4cpp::rseq_t&, Group31Var4&);
	static bool Write(const Group31Var4&, ser4cpp::wseq_t&);

	typedef uint16_t ValueType;
	uint8_t flags;
	uint16_t value;
	DNPTime time;

	typedef FrozenAnalog Target;
	typedef FrozenAnalogSpec Spec;
	static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
	static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
	static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
	static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var4;
};

// Frozen Analog Input - 32-bit Without Flag
struct Group31Var5
{
	static GroupVariationID ID() { return GroupVariationID(31, 5); }

	Group31Var5();

	static size_t Size() { return 4; }
	static bool Read(ser4cpp::rseq_t&, Group31Var5&);
	static bool Write(const Group31Var5&, ser4cpp::wseq_t&);

	typedef int32_t ValueType;
	int32_t value;

	typedef FrozenAnalog Target;
	typedef FrozenAnalogSpec Spec;
	static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
	static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
	static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
	static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var5;
};

// Frozen Analog Input - 16-bit Without Flag
struct Group31Var6
{
	static GroupVariationID ID() { return GroupVariationID(31, 6); }

	Group31Var6();

	static size_t Size() { return 2; }
	static bool Read(ser4cpp::rseq_t&, Group31Var6&);
	static bool Write(const Group31Var6&, ser4cpp::wseq_t&);

	typedef int16_t ValueType;
	int16_t value;

	typedef FrozenAnalog Target;
	typedef FrozenAnalogSpec Spec;
	static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
	static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
	static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
	static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var6;
};

// Frozen Analog Input - Single-precision With Flag
struct Group31Var7
{
  static GroupVariationID ID() { return GroupVariationID(31,7); }

  Group31Var7();

  static size_t Size() { return 5; }
  static bool Read(ser4cpp::rseq_t&, Group31Var7&);
  static bool Write(const Group31Var7&, ser4cpp::wseq_t&);

  typedef float ValueType;
  uint8_t flags;
  float value;

  typedef FrozenAnalog Target;
  typedef FrozenAnalogSpec Spec;
  static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
  static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
  static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
  static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var7;
};

// Frozen Analog Input - Double-precision With Flag
struct Group31Var8
{
  static GroupVariationID ID() { return GroupVariationID(31,8); }

  Group31Var8();

  static size_t Size() { return 9; }
  static bool Read(ser4cpp::rseq_t&, Group31Var8&);
  static bool Write(const Group31Var8&, ser4cpp::wseq_t&);

  typedef double ValueType;
  uint8_t flags;
  double value;

  typedef FrozenAnalog Target;
  typedef FrozenAnalogSpec Spec;
  static bool ReadTarget(ser4cpp::rseq_t&, FrozenAnalog&);
  static bool WriteTarget(const FrozenAnalog&, ser4cpp::wseq_t&);
  static DNP3Serializer<FrozenAnalog> Inst() { return DNP3Serializer<FrozenAnalog>(ID(), Size(), &ReadTarget, &WriteTarget); }
  static const StaticFrozenAnalogVariation svariation = StaticFrozenAnalogVariation::Group31Var8;
};

}

#endif
