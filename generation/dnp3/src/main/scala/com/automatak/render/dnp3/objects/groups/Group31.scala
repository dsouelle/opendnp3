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

object Group31 extends ObjectGroup {
  def objects = List(Group31Var0, Group31Var1, Group31Var2, Group31Var3, Group31Var4, Group31Var5, Group31Var6)
  def group: Byte = 31
  def desc: String = "Frozen Analog Input"
  def isEventGroup: Boolean = false
}

object Group31Var0 extends AnyVariation(Group31, 0)
object Group31Var1 extends FixedSize(Group31, 1, bit32WithFlag)(flags, value32) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
object Group31Var2 extends FixedSize(Group31, 2, bit16WithFlag)(flags, value16) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
object Group31Var3 extends FixedSize(Group31, 3, bit32WithoutFlag)(value32) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
object Group31Var4 extends FixedSize(Group31, 4, bit16WithoutFlag)(value16) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
object Group31Var5 extends FixedSize(Group31, 5, singlePrecisionWithFlag)(flags, float32) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
object Group31Var6 extends FixedSize(Group31, 6, doublePrecisionWithFlag)(flags, float64) with ConversionToFrozenAnalog with StaticVariation.FrozenAnalog
