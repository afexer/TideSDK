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

#include "ruby_module.h"

namespace tide
{

    static bool ShouldTreatKeysAsSymbols(VALUE hash)
    {
        size_t numberOfSymbolKeys = 0;
        size_t numberOfKeys = 0;

        VALUE keys = rb_funcall(hash, rb_intern("keys"), 0);
        for (int i = 0; i < RARRAY_LEN(keys); i++)
        {
            if (TYPE(rb_ary_entry(keys, i)) == T_SYMBOL)
                numberOfSymbolKeys++;

            numberOfKeys++;
        }

        // If the number of keys that are symbols is grater than
        // zero and more than half of the keys are symbols, than
        // we want to treat all new keys as symbols.
        return ((numberOfSymbolKeys * 2) > numberOfKeys);
    }

    KRubyHash::KRubyHash(VALUE hash) :
        TiObject("Ruby.KRubyHash"),
        hash(hash),
        object(new KRubyObject(hash))
    {
        rb_gc_register_address(&hash);
    }

    KRubyHash::~KRubyHash()
    {
        rb_gc_unregister_address(&hash);
    }

    KValueRef KRubyHash::Get(const char *name)
    {
        VALUE keyAsSymbol = ID2SYM(rb_intern(name));
        if (rb_funcall(hash, rb_intern("has_key?"), 1, keyAsSymbol))
            return RubyUtils::ToTiValue(rb_hash_aref(hash, keyAsSymbol));

        VALUE keyAsString = rb_str_new2(name);
        if (rb_funcall(hash, rb_intern("has_key?"), 1, keyAsString))
            return RubyUtils::ToTiValue(rb_hash_aref(hash, keyAsString));

        return this->object->Get(name);
    }

    void KRubyHash::Set(const char* name, KValueRef value)
    {
        // If this hash already has a key that's a symbol of
        // this name, then just use the symbol version. This
        // allows Tide to work with hashes of symbols (pretty
        // common in Ruby) without really *knowing* about symbols.
        VALUE keyAsSymbol = ID2SYM(rb_intern(name));
        if (rb_funcall(hash, rb_intern("has_key?"), 1, keyAsSymbol)
            || ShouldTreatKeysAsSymbols(hash))
        {
            rb_hash_aset(hash, keyAsSymbol,
                RubyUtils::ToRubyValue(value));
        }
        else
        {
            rb_hash_aset(hash, rb_str_new2(name),
                RubyUtils::ToRubyValue(value));
        }
    }

    SharedString KRubyHash::DisplayString(int levels)
    {
        return this->object->DisplayString(levels);
    }

    SharedStringList KRubyHash::GetPropertyNames()
    {
        SharedStringList property_names = object->GetPropertyNames();

        SharedStringList names(this->object->GetPropertyNames());
        VALUE keys = rb_funcall(hash, rb_intern("keys"), 0);
        for (int i = 0; i < RARRAY_LEN(keys); i++)
        {
            VALUE key = rb_ary_entry(keys, i);
            if (TYPE(key) == T_SYMBOL)
                names->push_back(new std::string(rb_id2name(SYM2ID(key))));
            else if (TYPE(key) == T_STRING)
                names->push_back(new std::string(StringValuePtr(key)));
        }

        return names;
    }

    VALUE KRubyHash::ToRuby()
    {
        return this->object->ToRuby();
    }

    bool KRubyHash::Equals(TiObjectRef other)
    {
        AutoPtr<KRubyHash> hashOther = other.cast<KRubyHash>();
        if (hashOther.isNull())
            return false;
        return hashOther->ToRuby() == this->ToRuby();
    }
}
