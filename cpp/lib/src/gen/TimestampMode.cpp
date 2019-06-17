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
// Copyright 2013-2019 Automatak, LLC
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

#include "opendnp3/gen/TimestampMode.h"
#include <stdexcept>

namespace opendnp3 {

uint8_t TimestampModeSpec::to_type(TimestampMode arg)
{
  return static_cast<uint8_t>(arg);
}

TimestampMode TimestampModeSpec::from_type(uint8_t arg)
{
  switch(arg)
  {
    case(1):
      return TimestampMode::SYNCHRONIZED;
    case(2):
      return TimestampMode::UNSYNCHRONIZED;
    default:
      return TimestampMode::INVALID;
  }
}

char const* TimestampModeSpec::to_string(TimestampMode arg)
{
  switch(arg)
  {
    case(TimestampMode::SYNCHRONIZED):
      return "SYNCHRONIZED";
    case(TimestampMode::UNSYNCHRONIZED):
      return "UNSYNCHRONIZED";
    default:
      return "INVALID";
  }
}

char const* TimestampModeSpec::to_human_string(TimestampMode arg)
{
  switch(arg)
  {
    case(TimestampMode::SYNCHRONIZED):
      return "SYNCHRONIZED";
    case(TimestampMode::UNSYNCHRONIZED):
      return "UNSYNCHRONIZED";
    default:
      return "INVALID";
  }
}

TimestampMode TimestampModeSpec::from_string(const std::string& arg)
{
  if(arg == "SYNCHRONIZED") return TimestampMode::SYNCHRONIZED;
  if(arg == "UNSYNCHRONIZED") return TimestampMode::UNSYNCHRONIZED;
  else return TimestampMode::INVALID;
}


}
