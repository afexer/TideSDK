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

#include "../tide.h"
#include <sstream>

namespace tide
{

    bool TiObject::Equals(TiObjectRef other)
    {
        return other.get() == this;
    }

    bool TiObject::HasProperty(const char* name)
    {
        SharedStringList names = this->GetPropertyNames();
        for (size_t i = 0; i < names->size(); i++)
        {
            if (!strcmp(name, names->at(i)->c_str()))
                return true;
        }
        return false;
    }

    SharedString TiObject::DisplayString(int levels)
    {
        std::stringstream ss;

        SharedStringList props = this->GetPropertyNames();
        ss << "(" << this->GetType() << ")" << " {";
        for (size_t i = 0; i < props->size(); i++)
        {
            KValueRef prop = this->Get(props->at(i));
            SharedString disp_string = prop->DisplayString(levels);

            ss << " " << *(props->at(i))
                << " : " << *disp_string << ",";
        }

        if (props->size() > 0) // Erase last comma
            ss.seekp((int)ss.tellp() - 1);

        ss << "}";

        return new std::string(ss.str());
    }

    void TiObject::Set(SharedString name, KValueRef value)
    {
        this->Set(name->c_str(), value);
    }

    KValueRef TiObject::Get(SharedString name)
    {
        return this->Get(name->c_str());
    }

    int TiObject::GetInt(const char* name, int defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsInt())
        {
            return prop->ToInt();
        }
        else
        {
            return defaultValue;
        }
    }

    double TiObject::GetDouble(const char* name, double defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsDouble())
        {
            return prop->ToDouble();
        }
        else
        {
            return defaultValue;
        }
    }

    double TiObject::GetNumber(const char* name, double defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsNumber())
        {
            return prop->ToNumber();
        }
        else
        {
            return defaultValue;
        }
    }

    bool TiObject::GetBool(const char* name, bool defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsBool())
        {
            return prop->ToBool();
        }
        else
        {
            return defaultValue;
        }
    }

    std::string TiObject::GetString(const char* name, std::string defaultValue)
    {
        KValueRef prop = this->Get(name);
        if(prop->IsString())
        {
            return prop->ToString();
        }
        else
        {
            return defaultValue;
        }
    }

    TiObjectRef TiObject::GetObject(const char* name, TiObjectRef defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsObject())
        {
            return prop->ToObject();
        }
        else
        {
            return defaultValue;
        }
    }

    TiMethodRef TiObject::GetMethod(const char* name, TiMethodRef defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsMethod())
        {
            return prop->ToMethod();
        }
        else
        {
            return defaultValue;
        }
    }

    TiListRef TiObject::GetList(const char* name, TiListRef defaultValue)
    {
        KValueRef prop = this->Get(name);
        if (prop->IsList())
        {
            return prop->ToList();
        }
        else
        {
            return defaultValue;
        }
    }

    void TiObject::SetUndefined(const char *name)
    {
        this->Set(name, Value::Undefined);
    }

    void TiObject::SetNull(const char *name)
    {
        this->Set(name, Value::Null);
    }

    void TiObject::SetInt(const char *name, int v)
    {
        KValueRef val = Value::NewInt(v);
        this->Set(name, val);
    }

    void TiObject::SetDouble(const char *name, double v)
    {
        KValueRef val = Value::NewDouble(v);
        this->Set(name, val);
    }

    void TiObject::SetNumber(const char *name, double v)
    {
        KValueRef val = Value::NewDouble(v);
        this->Set(name, val);
    }

    void TiObject::SetBool(const char *name, bool v)
    {
        KValueRef val = Value::NewBool(v);
        this->Set(name, val);
    }

    void TiObject::SetString(const char *name, std::string v)
    {
        KValueRef val = Value::NewString(v);
        this->Set(name, val);
    }

    void TiObject::SetObject(const char *name, TiObjectRef object)
    {
        KValueRef obj_val = Value::NewObject(object);
        this->Set(name, obj_val);
    }

    void TiObject::SetMethod(const char *name, TiMethodRef object)
    {
        KValueRef obj_val = Value::NewMethod(object);
        this->Set(name, obj_val);
    }

    void TiObject::SetList(const char *name, TiListRef object)
    {
        KValueRef obj_val = Value::NewList(object);
        this->Set(name, obj_val);
    }

    void TiObject::GetStringList(const char *name, std::vector<std::string> &list)
    {
        KValueRef prop = this->Get(name);
        if(!prop->IsUndefined() && prop->IsList())
        {
            TiListRef values = prop->ToList();
            if (values->Size() > 0)
            {
                for (unsigned int c = 0; c < values->Size(); c++)
                {
                    KValueRef v = values->At(c);
                    if (v->IsString())
                    {
                        const char *s = v->ToString();
                        list.push_back(s);
                    }
                }
            }
        }
    }

    void TiObject::SetNS(const char *name, KValueRef value)
    {
        std::vector<std::string> tokens;
        FileUtils::Tokenize(std::string(name), tokens, ".");

        TiObject *scope = this;
        for (size_t i = 0; i < tokens.size() - 1; i++)
        {
            const char* token = tokens[i].c_str();
            StaticBoundObject *next;
            KValueRef next_val = scope->Get(token);

            if (next_val->IsUndefined())
            {
                next = new StaticBoundObject();
                TiObjectRef so = next;
                next_val = Value::NewObject(so);
                scope->Set(token, next_val);
                scope = next;
            }
            else if (!next_val->IsObject()
                     && !next_val->IsMethod()
                     && !next_val->IsList())
            {
                std::cerr << "invalid namespace for " << name << ", token: " << token << " was " << next_val->GetType() << std::endl;
                throw Value::NewString("Invalid namespace on setNS");
            }
            else
            {
                scope = next_val->ToObject().get();
            }
        }

        const char *prop_name = tokens[tokens.size()-1].c_str();
        scope->Set(prop_name, value);

#ifdef DEBUG_BINDING
        std::cout << "BOUND: " << value->GetType() << " to: " << name << std::endl;
#endif
    }

    KValueRef TiObject::GetNS(const char *name)
    {
        std::string s(name);
        std::string::size_type last = 0;
        std::string::size_type pos = s.find_first_of(".");
        KValueRef current;
        TiObject* scope = this;
        while (pos != std::string::npos)
        {
            std::string token = s.substr(last,pos-last);
            current = scope->Get(token.c_str());
            if (current->IsObject())
            {
                scope = current->ToObject().get();
            }
            else
            {
                return Value::Undefined;
            }
            last = pos + 1;
            pos = s.find_first_of(".", last);
        }
        if (pos!=s.length())
        {
            std::string token = s.substr(last);
            current = scope->Get(token.c_str());
        }

        return current;
    }

    KValueRef TiObject::CallNS(const char *name)
    {
        ValueList args;
        return CallNS(name, args);
    }
    
    KValueRef TiObject::CallNS(const char *name, KValueRef val1)
    {
        ValueList args;
        args.push_back(val1);
        return CallNS(name, args);
    }

    KValueRef TiObject::CallNS(const char *name, KValueRef val1, KValueRef val2)
    {
        ValueList args;
        args.push_back(val1);
        args.push_back(val2);
        return CallNS(name, args);
    }

    KValueRef TiObject::CallNS(const char *name, KValueRef val1, KValueRef val2, KValueRef val3)
    {
        ValueList args;
        args.push_back(val1);
        args.push_back(val2);
        args.push_back(val3);
        return CallNS(name, args);
    }

    KValueRef TiObject::CallNS(const char *name, const ValueList& args)
    {
        KValueRef callable_value = GetNS(name);
        if (callable_value->IsUndefined()) {
            return callable_value;
        }

        if (!callable_value->IsMethod()) {
            return Value::Undefined;
        }

        return callable_value->ToMethod()->Call(args);
    }

    std::string& TiObject::GetType()
    {
        return type;
    }

    TiObjectRef TiObject::Unwrap(TiObjectRef o)
    {
        AutoPtr<ProfiledBoundObject> pobj = o.cast<ProfiledBoundObject>();
        if (pobj.isNull())
        {
            return o;
        }
        else
        {
            return pobj->GetDelegate();
        }
    }

}
