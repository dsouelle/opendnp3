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

#ifndef OPENDNP3_CSTRING_H
#define OPENDNP3_CSTRING_H

#include <opendnp3/util/Uncopyable.h>

#include <jni.h>

#include <string>

#include "../adapters/LocalRef.h"

// RAII class for java <=> cint
class CInt : private opendnp3::Uncopyable
{
    JNIEnv* env;
    JInt jint;
    const uint16_t* cint;

public:
    CInt(JNIEnv* env, JInt jint) : env(env), jint(jint), cint(env->GetStringUTFChars(jint, nullptr)) {}

    ~CInt()
    {
        env->ReleaseStringUTFChars(jint, cint);
    }

    std::uint16_t str() const
    {
        return std::uint16_t(cint);
    }

    operator const uint16_t*() const
    {
        return cint;
    }
};

#endif
