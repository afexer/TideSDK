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

#ifndef _MEDIA_BINDING_H_
#define _MEDIA_BINDING_H_

#include <tide/tide.h>
#include <map>
#include <vector>
#include <string>

namespace ti
{
    class MediaBinding : public StaticBoundObject
    {
        public:
        MediaBinding(TiObjectRef);

        protected:
        virtual ~MediaBinding();

        private:
        TiObjectRef global;
        void _CreateSound(const ValueList& args, KValueRef result);
        void _Beep(const ValueList& args, KValueRef result);

        virtual TiObjectRef CreateSound(std::string& url) = 0;
        virtual void Beep() = 0;
    };
}

#endif
