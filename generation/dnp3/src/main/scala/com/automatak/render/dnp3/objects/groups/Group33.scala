/**
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
package com.automatak.render.dnp3.objects.groups

import com.automatak.render.dnp3.objects._

import FixedSizeField._
import com.automatak.render.dnp3.objects.VariationNames._
import com.automatak.render.dnp3.objects.generators.ConversionToFrozenAnalog

// frozen analog input event
object Group33 extends ObjectGroup {
  def objects = List(Group33Var0, Group33Var1, Group33Var2, Group33Var3, Group33Var4, Group33Var5, Group33Var6, Group33Var7, Group33Var8)
  def group: Byte = 33
  def desc: String = "Frozen Analog Input Event"
  def isEventGroup: Boolean = true
}

object Group33Var0 extends AnyVariation(Group33, 0)
object Group33Var1 extends FixedSize(Group33, 1, bit32WithFlag)(flags, value32) with ConversionToFrozenAnalog
object Group33Var2 extends FixedSize(Group33, 2, bit16WithFlag)(flags, value16) with ConversionToFrozenAnalog
object Group33Var3 extends FixedSize(Group33, 3, bit32WithFlagTime)(flags, value32, time48) with ConversionToFrozenAnalog
object Group33Var4 extends FixedSize(Group33, 4, bit16WithFlagTime)(flags, value16, time48) with ConversionToFrozenAnalog
object Group33Var5 extends FixedSize(Group33, 5, singlePrecisionWithFlag)(flags, float32) with ConversionToFrozenAnalog
object Group33Var6 extends FixedSize(Group33, 6, doublePrecisionWithFlag)(flags, float64) with ConversionToFrozenAnalog
object Group33Var7 extends FixedSize(Group33, 7, singlePrecisionWithFlagTime)(flags, float32, time48) with ConversionToFrozenAnalog
object Group33Var8 extends FixedSize(Group33, 8, doublePrecisionWithFlagTime)(flags, float64, time48) with ConversionToFrozenAnalog
