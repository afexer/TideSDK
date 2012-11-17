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

#include "../ui_module.h"
#include <tide/net/proxy_config.h>
#include <Poco/Environment.h>
#include <Poco/URI.h>
using Poco::URI;
using std::string;
namespace ti
{
    void NormalizeURLCallback(const char* url, char* buffer, int bufferLength)
    {
        strncpy(buffer, url, bufferLength);
        buffer[bufferLength - 1] = '\0';

        string urlString = url;
        string normalized = URLUtils::NormalizeURL(urlString);
        if (normalized != urlString)
        {
            strncpy(buffer, normalized.c_str(), bufferLength);
            buffer[bufferLength - 1] = '\0';
        }
    }

    void URLToFileURLCallback(const char* url, char* buffer, int bufferLength)
    {
        strncpy(buffer, url, bufferLength);
        buffer[bufferLength - 1] = '\0';

        try
        {
            string newURL = url;
            string path = URLUtils::URLToPath(newURL);
            if (path != newURL)
                newURL = URLUtils::PathToFileURL(path);

            strncpy(buffer, newURL.c_str(), bufferLength);
            buffer[bufferLength - 1] = '\0';
        }
        catch (ValueException& e)
        {
            SharedString ss = e.DisplayString();
            Logger* log = Logger::Get("UI.URL");
            log->Error("Could not convert %s to a path: %s", url, ss->c_str());
        }
        catch (...)
        {
            Logger* log = Logger::Get("UI.URL");
            log->Error("Could not convert %s to a path", url);
        }
    }

    void ProxyForURLCallback(const char* url, char* buffer, int bufferLength)
    {
        buffer[bufferLength - 1] = '\0';

        std::string urlString(url);
        SharedProxy proxy(ProxyConfig::GetProxyForURL(urlString));
        if (proxy.isNull())
            strncpy(buffer, "direct://", bufferLength);
        else
            strncpy(buffer, proxy->ToString().c_str(), bufferLength);
    }

    int CanPreprocessURLCallback(const char* url)
    {
        return Script::GetInstance()->CanPreprocess(url);
    }

    char* PreprocessURLCallback(const char* url, KeyValuePair* headers, char** mimeType)
    {
        Logger* logger = Logger::Get("UI.URL");

        TiObjectRef scope = new StaticBoundObject();
        TiObjectRef kheaders = new StaticBoundObject();
        while (headers->key)
        {
            kheaders->SetString(headers->key, headers->value);
            headers++;
        }

        try
        {
            AutoPtr<PreprocessData> result = 
                Script::GetInstance()->Preprocess(url, scope);
            *mimeType = strdup(result->mimeType.c_str());
            return strdup(result->data->Pointer());
        }
        catch (ValueException& e)
        {
            logger->Error("Error in preprocessing: %s", e.ToString().c_str());
        }
        catch (...)
        {
            logger->Error("Unknown Error in preprocessing");
        }

        return NULL;
    }
}
