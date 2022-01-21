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
package com.automatak.dnp3.example;

import com.automatak.dnp3.*;
import com.automatak.dnp3.enums.*;
import com.automatak.dnp3.impl.DNP3ManagerFactory;
import com.automatak.dnp3.mock.DefaultOutstationApplication;
import com.automatak.dnp3.mock.PrintingChannelListener;
import com.automatak.dnp3.mock.PrintingLogHandler;
import com.automatak.dnp3.mock.SuccessCommandHandler;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * Example master than can be run against the example outstation
 */
public class OutstationDemo {

    static Outstation outstation;
    static Outstation outstation2;
    private static State state = new State();
    public static void main(String[] args) throws Exception {

        // create the root class with a thread pool size of 1
        DNP3Manager manager = DNP3ManagerFactory.createManager(1, PrintingLogHandler.getInstance());

        try {
            run(manager);
        }
        catch(Exception ex)
        {
            System.out.println("Exception: " + ex.getMessage());
        }
        finally {
            // This call is needed b/c the thread-pool will stop the application from exiting
            // and the finalizer isn't guaranteed to run b/c the GC might not be collected during main() exit
            manager.shutdown();
        }
    }

    private static void run(DNP3Manager manager) throws Exception {

        // Create a tcp channel class that will connect to the loopback
        Channel channel = manager.addTCPServer(
                "client1",
                LogMasks.NORMAL | LogMasks.APP_COMMS,
                ServerAcceptMode.CloseExisting,
                new IPEndpoint("127.0.0.1", 20000),
                PrintingChannelListener.getInstance()
        );

        // Create the default outstation configuration
        DatabaseConfig dbConfig = new DatabaseConfig(10, 10, 10, 10, 10, 10, 10, 10);
        EventBufferConfig eventConfig = new EventBufferConfig(100, 100, 100, 100, 100, 100, 100, 100);
        eventConfig = changeDefaultVariations(dbConfig, eventConfig);
        OutstationStackConfig config = new OutstationStackConfig(dbConfig, eventConfig);
        config.linkConfig.localAddr = 1024;

        // Create an Outstation instance, pass in a simple a command handler that responds successfully to everything
        outstation = channel.addOutstation(
                "outstation",
                new myCommandHandler(CommandStatus.SUCCESS),
                DefaultOutstationApplication.getInstance(),
                config
        );

        outstation.enable();

        // Create a tcp channel class that will connect to the loopback
        channel = manager.addTCPServer(
                "client2",
                LogMasks.NORMAL | LogMasks.APP_COMMS,
                ServerAcceptMode.CloseExisting,
                new IPEndpoint("127.0.0.1", 20001),
                PrintingChannelListener.getInstance()
        );

        // Create the default outstation configuration
        dbConfig = new DatabaseConfig(10, 10, 10, 10, 10, 10, 10, 10);
        eventConfig = new EventBufferConfig(100, 100, 100, 100, 100, 100, 100, 100);
        eventConfig = changeDefaultVariations(dbConfig, eventConfig);
        config = new OutstationStackConfig(dbConfig, eventConfig);
        config.linkConfig.localAddr = 1024;

        // Create an Outstation instance, pass in a simple a command handler that responds successfully to everything
        outstation2 = channel.addOutstation(
                "outstation2",
                new myCommandHandler(CommandStatus.SUCCESS),
                DefaultOutstationApplication.getInstance(),
                config
        );

        outstation2.enable();

        // all this stuff just to read a line of text in Java. Oh the humanity.
        String line = "";
        InputStreamReader converter = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(converter);


        int i = 0;
        //boolean state = false;
        while (true) {
            System.out.println("Enter something to update a counter or type <quit> to exit");
            line = in.readLine();
            if(line.equals("quit")) break;
            else {
                DNPTime timestamp = new DNPTime(System.currentTimeMillis());
                OutstationChangeSet set = new OutstationChangeSet();
                Flags flags = new Flags();
                flags.set(CounterQuality.ONLINE);
                state.count = i;
                set.update(new Counter(state.count, flags, timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(FrozenCounterQuality.ONLINE);
                set.freezeCounter(i, false);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(AnalogQuality.ONLINE);
                set.update(new AnalogInput(state.value, flags, timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(FrozenAnalogQuality.ONLINE);
                set.freezeAnalog(i, false);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(BinaryQuality.ONLINE);
                state.binary = !state.binary;
                if (state.binary){
                    flags.set(BinaryQuality.STATE);
                }
                set.update(new BinaryInput(state.binary,flags,timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(DoubleBitBinaryQuality.ONLINE);
                if (state.dbit == DoubleBit.DETERMINED_ON) {
                    state.dbit = DoubleBit.DETERMINED_OFF;
                    flags.set(DoubleBitBinaryQuality.STATE1);
                }else {
                    state.dbit = DoubleBit.DETERMINED_ON;
                    flags.set(DoubleBitBinaryQuality.STATE2);
                }
                set.update(new DoubleBitBinaryInput(state.dbit,flags,timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(BinaryOutputStatusQuality.ONLINE);
                if (state.binary){
                    flags.set(BinaryOutputStatusQuality.STATE);
                }
                set.update(new BinaryOutputStatus(state.binary,flags,timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);

                set = new OutstationChangeSet();
                flags = new Flags();
                flags.set(AnalogOutputStatusQuality.ONLINE);
                set.update(new AnalogOutputStatus(state.value, flags, timestamp), i);
                outstation.apply(set);
                outstation2.apply(set);
                ++i;
                state.value = state.value + i;
                if (i==10) {
                    i = 0;
                    state.binary = !state.binary;
                    state.value = 10.5;
                    if (state.dbit == DoubleBit.DETERMINED_ON) {
                        state.dbit = DoubleBit.DETERMINED_OFF;
                    }else {
                        state.dbit = DoubleBit.DETERMINED_ON;
                    }
                }
            }
        }
    }
    public static EventBufferConfig changeDefaultVariations(DatabaseConfig dbConfig, EventBufferConfig eventconfig) {
        if (dbConfig.binary.size()>0)
            for (int i = 0; i<dbConfig.binary.size();i++)
                dbConfig.binary.get(i).eventVariation = EventBinaryVariation.Group2Var2; //Var2:with absolute time
        if (dbConfig.doubleBinary.size()>0)
            for (int i = 0; i<dbConfig.doubleBinary.size();i++)
                dbConfig.doubleBinary.get(i).eventVariation = EventDoubleBinaryVariation.Group4Var2; //Var2:with absolute time
        if (dbConfig.counter.size()>0)
            for (int i = 0; i<dbConfig.counter.size();i++)
                dbConfig.counter.get(i).eventVariation = EventCounterVariation.Group22Var5; //Var5:32-bit with flag and time
        if (dbConfig.frozenCounter.size()>0)
            for (int i = 0; i<dbConfig.frozenCounter.size();i++)
                dbConfig.frozenCounter.get(i).eventVariation = EventFrozenCounterVariation.Group23Var5; //Var5:32-bit with flag and time
        if (dbConfig.analog.size()>0)
            for (int i = 0; i<dbConfig.analog.size();i++){
                dbConfig.analog.get(i).eventVariation = EventAnalogVariation.Group32Var7; //Var7:single precision float with Time
                dbConfig.analog.get(i).staticVariation = StaticAnalogVariation.Group30Var5; //Var5:single precision float with Flag
            }
        if (dbConfig.frozenAnalog.size()>0)
            for (int i = 0; i<dbConfig.frozenAnalog.size();i++){
                dbConfig.frozenAnalog.get(i).eventVariation = EventFrozenAnalogVariation.Group33Var7; //Var7:single precision float with Time
                dbConfig.frozenAnalog.get(i).staticVariation = StaticFrozenAnalogVariation.Group31Var7; //Var7:single precision float with Flag
            }
        if (dbConfig.boStatus.size()>0)
            for (int i = 0; i<dbConfig.boStatus.size();i++)
                dbConfig.boStatus.get(i).eventVariation = EventBinaryOutputStatusVariation.Group11Var2; //Var2:with absolute time
        if (dbConfig.aoStatus.size()>0)
            for (int i = 0; i<dbConfig.aoStatus.size();i++){
                dbConfig.aoStatus.get(i).eventVariation = EventAnalogOutputStatusVariation.Group42Var7; //Var7:single precision float with Time
                dbConfig.aoStatus.get(i).staticVariation = StaticAnalogOutputStatusVariation.Group40Var3; //Var3:single precision float with Flag
            }
        return eventconfig;
    }
    static class myCommandHandler implements CommandHandler {
        private final CommandStatus status;
        private State state = new State();

        public myCommandHandler(CommandStatus status)
        {
            this.status = status;
        }

        @Override
        public void begin() {
            // TODO Auto-generated method stub
            System.out.println("start asdu");
        }

        @Override
        public void end() {
            // TODO Auto-generated method stub
            System.out.println("end asdu");
        }

        @Override
        public CommandStatus select(ControlRelayOutputBlock command, int index) {
            // TODO Auto-generated method stub
            System.out.println("start selectCROB");
            return status;
        }

        @Override
        public CommandStatus select(AnalogOutputInt32 arg0, int arg1) {
            // TODO Auto-generated method stub
            System.out.println("start selectAOI32");
            return status;
        }

        @Override
        public CommandStatus select(AnalogOutputInt16 arg0, int arg1) {
            // TODO Auto-generated method stub
            System.out.println("start selectAOI16");
            return status;
        }

        @Override
        public CommandStatus select(AnalogOutputFloat32 arg0, int arg1) {
            // TODO Auto-generated method stub
            System.out.println("start selectAOF32");
            return status;
        }

        @Override
        public CommandStatus select(AnalogOutputDouble64 arg0, int arg1) {
            // TODO Auto-generated method stub
            System.out.println("start selectAOD64");
            return status;
        }

        @Override
        public CommandStatus operate(ControlRelayOutputBlock command, int index, Database arg2, OperateType opType) {
            // TODO Auto-generated method stub
            System.out.println("start operateCROB, OperateType");
            List<String> nodeName = new ArrayList();
            List<OutstationChangeSet> myList = new ArrayList();
            List<Integer> nodeIndex = new ArrayList();
            String str = "";
            DNPTime timestamp = new DNPTime(System.currentTimeMillis());
            OutstationChangeSet set = new OutstationChangeSet();
            if (command.opType==OperationType.LATCH_ON){
                state.binary = true;
                str = index + " - BinaryOutputStatus(true, 0x81," + new java.util.Date(timestamp.msSinceEpoch) + ")";
                Flags flags = new Flags();
                flags.set(BinaryOutputStatusQuality.ONLINE);
                flags.set(BinaryOutputStatusQuality.STATE);
                BinaryOutputStatus temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                set.update(temp, index);
                outstation.apply(set);
            }else if (command.opType==OperationType.LATCH_OFF){
                state.binary = false;
                str = index + " - BinaryOutputStatus(false, 0x01," + new java.util.Date(timestamp.msSinceEpoch) + ")";
                Flags flags = new Flags();
                flags.set(BinaryOutputStatusQuality.ONLINE);
                flags.set(BinaryOutputStatusQuality.STATE);
                BinaryOutputStatus temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                set.update(temp, index);
                outstation.apply(set);
            }
            else if (command.opType==OperationType.PULSE_ON){
                state.binary = true;
                Flags flags = new Flags();
                flags.set(BinaryOutputStatusQuality.ONLINE);
                flags.set(BinaryOutputStatusQuality.STATE);
                BinaryOutputStatus temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                set.update(temp, index);
                outstation.apply(set);
                try {
                    state.binary = false;
                    TimeUnit.MILLISECONDS.sleep(command.onTimeMs);
                    timestamp = new DNPTime(System.currentTimeMillis());
                    temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                    set.update(temp, index);
                    outstation.apply(set);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
            else if (command.opType==OperationType.PULSE_OFF){
                state.binary = false;
                Flags flags = new Flags();
                flags.set(BinaryOutputStatusQuality.ONLINE);
                flags.set(BinaryOutputStatusQuality.STATE);
                BinaryOutputStatus temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                set.update(temp, index);
                outstation.apply(set);
                try {
                    state.binary = true;
                    TimeUnit.MILLISECONDS.sleep(command.offTimeMs);
                    timestamp = new DNPTime(System.currentTimeMillis());
                    temp = new BinaryOutputStatus( state.binary, flags, timestamp);
                    set.update(temp, index);
                    outstation.apply(set);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
            myList.add(set);
            nodeName.add(str);
            nodeIndex.add(index);
            return status;
        }

        @Override
        public CommandStatus operate(AnalogOutputInt32 command, int index, Database arg2, OperateType arg3) {
            System.out.println("start operateAOI32");
            List<String> nodeName = new ArrayList();
            List<OutstationChangeSet> myList = new ArrayList();
            List<Integer> nodeIndex = new ArrayList();
            String str = "";
            DNPTime timestamp = new DNPTime(System.currentTimeMillis());
            OutstationChangeSet set = new OutstationChangeSet();
            state.value = command.value;
            str = index + " - AnalogOutputStatus("+ state.value + ", 0x01," + new java.util.Date(timestamp.msSinceEpoch) + ")";
            Flags flags = new Flags();
            flags.set(AnalogOutputStatusQuality.ONLINE);
            AnalogOutputStatus temp = new AnalogOutputStatus(command.value, flags, timestamp);
            set.update(temp, index);
            outstation.apply(set);
            myList.add(set);
            nodeName.add(str);
            nodeIndex.add(index);
            return status;
        }

        @Override
        public CommandStatus operate(AnalogOutputInt16 command, int index, Database arg2, OperateType arg3) {
            System.out.println("start operateAOI16");
            List<String> nodeName = new ArrayList();
            List<OutstationChangeSet> myList = new ArrayList();
            List<Integer> nodeIndex = new ArrayList();
            String str = "";
            DNPTime timestamp = new DNPTime(System.currentTimeMillis());
            OutstationChangeSet set = new OutstationChangeSet();
            state.value = command.value;
            str = index + " - AnalogOutputStatus("+ state.value + ", 0x01," + new java.util.Date(timestamp.msSinceEpoch) + ")";
            Flags flags = new Flags();
            flags.set(AnalogOutputStatusQuality.ONLINE);
            AnalogOutputStatus temp = new AnalogOutputStatus(command.value, flags, timestamp);
            set.update(temp, index);
            outstation.apply(set);
            myList.add(set);
            nodeName.add(str);
            nodeIndex.add(index);
            return status;
        }

        @Override
        public CommandStatus operate(AnalogOutputFloat32 command, int index, Database arg2, OperateType arg3) {
            System.out.println("start operateAOF32");
            List<String> nodeName = new ArrayList();
            List<OutstationChangeSet> myList = new ArrayList();
            List<Integer> nodeIndex = new ArrayList();
            String str = "";
            DNPTime timestamp = new DNPTime(System.currentTimeMillis());
            OutstationChangeSet set = new OutstationChangeSet();
            state.value = command.value;
            str = index + " - AnalogOutputStatus("+ state.value + ", 0x01," + new java.util.Date(timestamp.msSinceEpoch) + ")";
            Flags flags = new Flags();
            flags.set(AnalogOutputStatusQuality.ONLINE);
            AnalogOutputStatus temp = new AnalogOutputStatus(command.value, flags, timestamp);
            //AnalogOutputStatus temp = new AnalogOutputStatus(command.value,(byte) 0x01, timestamp.msSinceEpoch);
            set.update(temp, index);
            outstation.apply(set);
            myList.add(set);
            nodeName.add(str);
            nodeIndex.add(index);
            return status;
        }

        @Override
        public CommandStatus operate(AnalogOutputDouble64 command, int index, Database arg2, OperateType arg3) {
            System.out.println("start operateAOD64");
            List<String> nodeName = new ArrayList();
            List<OutstationChangeSet> myList = new ArrayList();
            List<Integer> nodeIndex = new ArrayList();
            String str = "";
            DNPTime timestamp = new DNPTime(System.currentTimeMillis());
            OutstationChangeSet set = new OutstationChangeSet();
            state.value = command.value;
            str = index + " - AnalogOutputStatus("+ state.value + ", 0x01," + new java.util.Date(timestamp.msSinceEpoch) + ")";
            Flags flags = new Flags();
            flags.set(AnalogOutputStatusQuality.ONLINE);
            AnalogOutputStatus temp = new AnalogOutputStatus(command.value, flags, timestamp);
            set.update(temp, index);
            outstation.apply(set);
            myList.add(set);
            nodeName.add(str);
            nodeIndex.add(index);
            return status;
        }

    }
    public static class State {

        public long count = 0;
        public long fcount = 0;
        public double value = 0.0;
        public boolean binary = false;
        public DoubleBit dbit = DoubleBit.INTERMEDIATE;

    }

}
