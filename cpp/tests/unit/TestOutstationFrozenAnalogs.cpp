/*
 * Copyright 2013-2020 Automatak, LLC
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
 * LLC (www.automatak.com) under one or more contributor license agreements.
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership. Green Energy Corp and Automatak LLC license
 * this file to you under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "utils/APDUHexBuilders.h"
#include "utils/OutstationTestObject.h"

#include <ser4cpp/util/HexConversions.h>

#include <dnp3mocks/DatabaseHelpers.h>

#include <catch.hpp>

using namespace opendnp3;

#define SUITE(name) "OutstationFrozenAnalogs - " name

// "Go back to your oar, Forty-One."
//   - Quintus Arrius
const float analogValue = 41;
const std::string analogValueHex = "29";

// "Elvis has left the building!"
const DNPTime freezeTimestamp(240607800000, TimestampQuality::SYNCHRONIZED);
const std::string freezeTimestampHex = "C0 AA 57 05 38 00";

void TestFreezeOperation1(std::string func, std::function<std::string(uint8_t)> freezeResponse, bool clear)
{
    OutstationConfig config;
    auto database = configure::by_count_of::analog_input(1, true);
    database.frozen_analog[0].svariation = StaticFrozenAnalogVariation::Group31Var4;
    OutstationTestObject t(config, database);
    t.Transaction([](IUpdateHandler& db) {
        db.Modify(FlagsType::AnalogInput, 0, 0, 0x01);
        db.Modify(FlagsType::FrozenAnalog, 0, 0, 0x01);
    });
    t.LowerLayerUp();

    // Freeze all analogs
    t.SendToOutstation("C0 " + func + " 1E 00 06");
    REQUIRE(t.lower->PopWriteAsHex() == freezeResponse(0));
    t.OnTxReady();

    // Read all frozen analogs
    t.SendToOutstation("C1 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C1 81 80 00 1F 07 00 00 00 01 00 00 00 00 00 00 00 00"); // Frozen value at 0
    t.OnTxReady();

    // Update the analogs
    t.Transaction([=](IUpdateHandler& db) { db.Update(Analog(analogValue), 0); });

    // Read all frozen analogs
    t.SendToOutstation("C2 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C2 81 80 00 1F 04 00 00 00 01 00 00 00 00 00 00 00 00"); // Frozen value still at 0
    t.OnTxReady();

    // Change time of application
    t.application->SetTime(freezeTimestamp);

    // Freeze all analogs
    t.SendToOutstation("C3 " + func + " 1E 00 06");
    REQUIRE(t.lower->PopWriteAsHex() == freezeResponse(3));
    t.OnTxReady();

    // Read all frozen analogs
    t.SendToOutstation("C4 01 1F 00 06");
	REQUIRE(t.lower->PopWriteAsHex()
		== "C4 81 80 00 1F 04 00 00 00 01 29 00 " +freezeTimestampHex); // Frozen value now at 41
    t.OnTxReady();

    std::string expectedAnalogValue = clear ? "00" : analogValueHex;

    // Read all analogs
    t.SendToOutstation("C5 01 1E 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C5 81 80 00 1E 01 00 00 00 01 " + expectedAnalogValue
                + " 00 00 00"); // Check if analog value is reset (if necessary)
    t.OnTxReady();
}

std::string NullResponse1(uint8_t seq)
{
    return hex::EmptyResponse(seq, IINField(IINBit::DEVICE_RESTART));
}

std::string NoResponse1(uint8_t seq)
{
    return "";
}

TEST_CASE(SUITE("Freeze 0x07"))
{
    TestFreezeOperation1("07", NullResponse1, false);
}

TEST_CASE(SUITE("Freeze No Ack 0x08"))
{
    TestFreezeOperation1("08", NoResponse1, false);
}

TEST_CASE(SUITE("Freeze And Clear 0x09"))
{
    TestFreezeOperation1("09", NullResponse1, true);
}

TEST_CASE(SUITE("Freeze And Clear No Ack 0x0A"))
{
    TestFreezeOperation1("0A", NoResponse1, true);
}

TEST_CASE(SUITE("Broadcast Support"))
{
    OutstationConfig config;
    auto database = configure::by_count_of::analog_input(1, true);
    database.frozen_analog[0].svariation = StaticFrozenAnalogVariation::Group31Var4;
    OutstationTestObject t(config, database);
    t.Transaction([](IUpdateHandler& db) {
        db.Modify(FlagsType::AnalogInput, 0, 0, 0x01);
        db.Modify(FlagsType::FrozenAnalog, 0, 0, 0x01);
    });
    t.LowerLayerUp();

    // Freeze all analogs
    t.BroadcastToOutstation(LinkBroadcastAddress::DontConfirm, "C0 0A 1E 00 06");//C0 0A 1E 00 06 
    REQUIRE(t.lower->PopWriteAsHex() == ""); // No response
    t.OnTxReady();

    // Read all frozen analogs
    t.SendToOutstation("C1 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C1 81 81 00 1F 04 00 00 00 01 00 00 00 00 00 00 00 00"); // Frozen value at 0
    t.OnTxReady();

    // Update the analogs
    t.Transaction([=](IUpdateHandler& db) { db.Update(Analog(analogValue), 0); });

    // Read all frozen analogs
    t.SendToOutstation("C2 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C2 81 80 00 1F 04 00 00 00 01 00 00 00 00 00 00 00 00"); // Frozen value still at 0
    t.OnTxReady();

    // Change time of application
    t.application->SetTime(freezeTimestamp);

    // Freeze all analogs
    t.BroadcastToOutstation(LinkBroadcastAddress::DontConfirm, "C3 0A 1E 00 06");//C3 0A 1E 00 06
    REQUIRE(t.lower->PopWriteAsHex() == ""); // No response
    t.OnTxReady();

    // Read all frozen analogs
    t.SendToOutstation("C4 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C4 81 81 00 1F 04 00 00 00 01 29 00 " + freezeTimestampHex); // Frozen value now at 41
    t.OnTxReady();

    // Read all analogs
    t.SendToOutstation("C5 01 1E 00 06");
    REQUIRE(t.lower->PopWriteAsHex() == "C5 81 80 00 1E 01 00 00 00 01 00 00 00 00"); // Analog is now reset
    t.OnTxReady();
}

TEST_CASE(SUITE("Range freeze"))
{
    const uint16_t num_analogs = 10;

    OutstationConfig config;
    auto database = configure::by_count_of::analog_input(num_analogs, true);
    OutstationTestObject t(config, database);
    t.Transaction([=](IUpdateHandler& db) {
        db.Modify(FlagsType::AnalogInput, 0, num_analogs - 1, 0x01);
        db.Modify(FlagsType::FrozenAnalog, 0, num_analogs - 1, 0x01);
    });
    t.LowerLayerUp();

    // Read all frozen analogs
    t.SendToOutstation("C0 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C0 81 80 00 1F 01 00 00 09 "
               "01 00 00 00 00 01 00 00 00 00 "
               "01 00 00 00 00 01 00 00 00 00 01 00 00 00 00 01 00 00 00 00 01 00 00 00 00 "
               "01 00 00 00 00 01 00 00 00 00 01 00 00 00 00"); // Frozen value at 0
    t.OnTxReady();

    // Update the analogs
    t.Transaction([=](IUpdateHandler& db) {
        for (uint16_t i = 0; i < num_analogs; ++i)
        {
            db.Update(Analog(analogValue), i);
        }
    });

    // Freeze subset of analogs
    t.SendToOutstation("C1 07 1E 00 00 02 06");
    REQUIRE(t.lower->PopWriteAsHex() == "C1 81 80 00");
    t.OnTxReady();

    // Read all frozen analogs
    t.SendToOutstation("C2 01 1F 00 06");
    REQUIRE(t.lower->PopWriteAsHex()
            == "C2 81 80 00 1F 01 00 00 09 "
               "01 00 00 00 00 01 00 00 00 00 "
               "01 29 00 00 00 01 29 00 00 00 01 29 00 00 00 01 29 00 00 00 01 29 00 00 00 "
               "01 00 00 00 00 01 00 00 00 00 01 00 00 00 00"); // Frozen values are updated
    t.OnTxReady();
}
