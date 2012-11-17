/**
* This file has been modified from its orginal sources.
*
* Copyright (c) 2012 Software in the Public Interest Inc (SPI)
* Copyright (c) 2012 David Pratt
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***
* Copyright (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#ifndef _RUBY_LIST_H_
#define _RUBY_LIST_H_

#include "ruby_module.h"

namespace tide
{
    class KRubyList : public TiList
    {
    public:
        KRubyList(VALUE);
        virtual ~KRubyList();

        void Append(KValueRef value);
        unsigned int Size();
        KValueRef At(unsigned int index);
        void SetAt(unsigned int index, KValueRef value);
        bool Remove(unsigned int index);
        void Set(const char* name, KValueRef value);
        KValueRef Get(const char* name);
        SharedStringList GetPropertyNames();
        SharedString DisplayString(int);
        VALUE ToRuby();

    /*
     * Determine if the given Ruby object equals this one
     * by comparing these objects's identity e.g. equals?()
     *  @param other the object to test
     *  @returns true if objects have reference equality, false otherwise
     */
    virtual bool Equals(TiObjectRef);

    protected:
        VALUE list;
        AutoPtr<KRubyObject> object;
        DISALLOW_EVIL_CONSTRUCTORS(KRubyList);
    };
}

#endif
