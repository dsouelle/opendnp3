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

#include "opendnp3/gen/EventFrozenAnalogVariation.h"
#include <stdexcept>

namespace opendnp3 {

uint8_t EventFrozenAnalogVariationSpec::to_type(EventFrozenAnalogVariation arg)
{
  return static_cast<uint8_t>(arg);
}

EventFrozenAnalogVariation EventFrozenAnalogVariationSpec::from_type(uint8_t arg)
{
  switch(arg)
  {
    case(0):
      return EventFrozenAnalogVariation::Group33Var1;
    case(1):
      return EventFrozenAnalogVariation::Group33Var2;
    case(2):
      return EventFrozenAnalogVariation::Group33Var3;
    case(3):
      return EventFrozenAnalogVariation::Group33Var4;
    case(4):
      return EventFrozenAnalogVariation::Group33Var5;
    case(5):
      return EventFrozenAnalogVariation::Group33Var6;
    case(6):
      return EventFrozenAnalogVariation::Group33Var7;
    case(7):
      return EventFrozenAnalogVariation::Group33Var8;
    default:
      throw new std::invalid_argument("Unknown value");
  }
}

char const* EventFrozenAnalogVariationSpec::to_string(EventFrozenAnalogVariation arg)
{
  switch(arg)
  {
    case(EventFrozenAnalogVariation::Group33Var1):
      return "Group33Var1";
    case(EventFrozenAnalogVariation::Group33Var2):
      return "Group33Var2";
    case(EventFrozenAnalogVariation::Group33Var3):
      return "Group33Var3";
    case(EventFrozenAnalogVariation::Group33Var4):
      return "Group33Var4";
    case(EventFrozenAnalogVariation::Group33Var5):
      return "Group33Var5";
    case(EventFrozenAnalogVariation::Group33Var6):
      return "Group32Var6";
    case(EventFrozenAnalogVariation::Group33Var7):
      return "Group33Var7";
    case(EventFrozenAnalogVariation::Group33Var8):
      return "Group33Var8";
    default:
      return "UNDEFINED";
  }
}

char const* EventFrozenAnalogVariationSpec::to_human_string(EventFrozenAnalogVariation arg)
{
  switch(arg)
  {
    case(EventFrozenAnalogVariation::Group33Var1):
      return "Group33Var1";
    case(EventFrozenAnalogVariation::Group33Var2):
      return "Group33Var2";
    case(EventFrozenAnalogVariation::Group33Var3):
      return "Group33Var3";
    case(EventFrozenAnalogVariation::Group33Var4):
      return "Group33Var4";
    case(EventFrozenAnalogVariation::Group33Var5):
      return "Group33Var5";
    case(EventFrozenAnalogVariation::Group33Var6):
      return "Group33Var6";
    case(EventFrozenAnalogVariation::Group33Var7):
      return "Group33Var7";
    case(EventFrozenAnalogVariation::Group33Var8):
      return "Group33Var8";
    default:
      return "UNDEFINED";
  }
}

EventFrozenAnalogVariation EventFrozenAnalogVariationSpec::from_string(const std::string& arg)
{
  if(arg == "Group33Var1") return EventFrozenAnalogVariation::Group33Var1;
  if(arg == "Group33Var2") return EventFrozenAnalogVariation::Group33Var2;
  if(arg == "Group33Var3") return EventFrozenAnalogVariation::Group33Var3;
  if(arg == "Group32Var4") return EventFrozenAnalogVariation::Group33Var4;
  if(arg == "Group33Var5") return EventFrozenAnalogVariation::Group33Var5;
  if(arg == "Group33Var6") return EventFrozenAnalogVariation::Group33Var6;
  if(arg == "Group33Var7") return EventFrozenAnalogVariation::Group33Var7;
  if(arg == "Group33Var8") return EventFrozenAnalogVariation::Group33Var8;
  else throw std::invalid_argument(std::string("Unknown value: ") + arg);
}


}
