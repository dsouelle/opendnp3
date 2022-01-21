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

#include "opendnp3/gen/StaticFrozenAnalogVariation.h"
#include <stdexcept>

namespace opendnp3 {

	uint8_t StaticFrozenAnalogVariationSpec::to_type(StaticFrozenAnalogVariation arg)
	{
		return static_cast<uint8_t>(arg);
	}

	StaticFrozenAnalogVariation StaticFrozenAnalogVariationSpec::from_type(uint8_t arg)
	{
		switch (arg)
		{
		case(0):
			return StaticFrozenAnalogVariation::Group31Var1;
		case(1):
			return StaticFrozenAnalogVariation::Group31Var2;
		case(2):
			return StaticFrozenAnalogVariation::Group31Var3;
		case(3):
			return StaticFrozenAnalogVariation::Group31Var4;
		case(4):
			return StaticFrozenAnalogVariation::Group31Var5;
		case(5):
			return StaticFrozenAnalogVariation::Group31Var6;
		case(6):
			return StaticFrozenAnalogVariation::Group31Var7;
		case(7):
			return StaticFrozenAnalogVariation::Group31Var8;
		default:
			throw new std::invalid_argument("Unknown value");
		}
	}

	char const* StaticFrozenAnalogVariationSpec::to_string(StaticFrozenAnalogVariation arg)
	{
		switch (arg)
		{
		case(StaticFrozenAnalogVariation::Group31Var1):
			return "Group31Var1";
		case(StaticFrozenAnalogVariation::Group31Var2):
			return "Group31Var2";
		case(StaticFrozenAnalogVariation::Group31Var3):
			return "Group31Var3";
		case(StaticFrozenAnalogVariation::Group31Var4):
			return "Group31Var4";
		case(StaticFrozenAnalogVariation::Group31Var5):
			return "Group31Var5";
		case(StaticFrozenAnalogVariation::Group31Var6):
			return "Group31Var6";
		case(StaticFrozenAnalogVariation::Group31Var7):
			return "Group31Var7";
		case(StaticFrozenAnalogVariation::Group31Var8):
			return "Group31Var8";
		default:
			return "UNDEFINED";
		}
	}

	char const* StaticFrozenAnalogVariationSpec::to_human_string(StaticFrozenAnalogVariation arg)
	{
		switch (arg)
		{
		case(StaticFrozenAnalogVariation::Group31Var1):
			return "Group31Var1";
		case(StaticFrozenAnalogVariation::Group31Var2):
			return "Group31Var2";
		case(StaticFrozenAnalogVariation::Group31Var3):
			return "Group31Var3";
		case(StaticFrozenAnalogVariation::Group31Var4):
			return "Group31Var4";
		case(StaticFrozenAnalogVariation::Group31Var5):
			return "Group31Var5";
		case(StaticFrozenAnalogVariation::Group31Var6):
			return "Group31Var6";
		case(StaticFrozenAnalogVariation::Group31Var7):
			return "Group31Var7";
		case(StaticFrozenAnalogVariation::Group31Var8):
			return "Group31Var8";
		default:
			return "UNDEFINED";
		}
	}

	StaticFrozenAnalogVariation StaticFrozenAnalogVariationSpec::from_string(const std::string& arg)
	{
		if (arg == "Group31Var1") return StaticFrozenAnalogVariation::Group31Var1;
		if (arg == "Group31Var2") return StaticFrozenAnalogVariation::Group31Var2;
		if (arg == "Group31Var3") return StaticFrozenAnalogVariation::Group31Var3;
		if (arg == "Group31Var4") return StaticFrozenAnalogVariation::Group31Var4;
		if (arg == "Group31Var5") return StaticFrozenAnalogVariation::Group31Var5;
		if (arg == "Group31Var6") return StaticFrozenAnalogVariation::Group31Var6;
		if (arg == "Group31Var7") return StaticFrozenAnalogVariation::Group31Var7;
		if (arg == "Group31Var8") return StaticFrozenAnalogVariation::Group31Var8;
		else throw std::invalid_argument(std::string("Unknown value: ") + arg);
	}


}
