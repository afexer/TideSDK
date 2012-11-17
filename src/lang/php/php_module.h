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

#ifndef _PHP_MODULE_H_
#define _PHP_MODULE_H_

/*
 * PHP wreaks havoc on all kinds of cdecl/export/inline/god knows what macros,
 * causing math functions to be exported into each object file. _INC_MATH is
 * the math inclusion macro; defining it here seems to fix this issue for now,
 * but there's probably a better way. Also, undef inline and va_copy so we make
 * sure to get the win32 versions of those for Poco. This is why preprocessor
 * magic == evil
 */

/* 
 * Ground rules for editing include order here:
 * 1. Windows requires that STL includes be before PHP ones.
 * 2. OS X requires that tide/tide.h happen after PHP includes. This is because
 *    PHP redefines NO and YES, which must happen before all Objective-C NO/YES
 *    #defines.
 * 3. Linux requires that you keep breathing.
 */

#include <stack>
#include <iostream>
#include <sstream>

#if defined(OS_WIN32)
#include <tide/tide.h>
#define _INC_MATH
#include <zend_config.w32.h>
#include <sapi/embed/php_embed.h>
#undef inline
#undef va_copy
#undef PARSE_SERVER
#else
#include <sapi/embed/php_embed.h>
#endif

#include <Zend/zend.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_compile.h>
#include <Zend/zend_API.h>
#include <Zend/zend_closures.h>
#include <Zend/zend_hash.h>

#ifndef OS_WIN32
#include <tide/tide.h>
#endif

namespace tide 
{
    class PHPModuleInstance;
    class PHPModule;
}

#include "php_api.h"
#include "php_utils.h"
#include "php_object.h"
#include "php_method.h"
#include "php_function.h"
#include "php_list.h"
#include "php_array_object.h"
#include "php_evaluator.h"
#include "php_module_instance.h"

#include <Poco/URI.h>

namespace tide
{
    class TIDESDK_PHP_API PHPModule : public Module, public ModuleProvider
    {
    public:
        PHPModule(Host* host, const char* path) :
            Module(host, path, STRING(MODULE_NAME), STRING(MODULE_VERSION))
        {

        }

        ~PHPModule()
        {

        }
        void Initialize();
        void Stop();

        virtual bool IsModule(std::string& path);
        virtual Module* CreateModule(std::string& path);
        void InitializeBinding();

        static PHPModule* Instance() { return instance_; }
        static void SetBuffering(bool buffering);
        static std::ostringstream& GetBuffer() { return buffer; }
        static std::string& GetMimeType() { return mimeType; }
        
        void PushURI(Poco::URI& uri) { uriStack.push(new Poco::URI(uri)); }
        void PopURI() { Poco::URI* uri = uriStack.top(); uriStack.pop(); delete uri; }
        Poco::URI* GetURI() { return uriStack.size() == 0 ? 0 : uriStack.top(); }

    private:
        TiObjectRef binding;
        static std::ostringstream buffer;
        static std::string mimeType;
        static PHPModule *instance_;
        std::stack<Poco::URI*> uriStack;

        DISALLOW_EVIL_CONSTRUCTORS(PHPModule);
    };
}

#endif
