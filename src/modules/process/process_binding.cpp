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

#include <tide/tide.h>
#include <Poco/Environment.h>
#include <Poco/Process.h>
#include "process_binding.h"
#include "process.h"
#include <signal.h>

namespace ti
{
    std::map<std::string,int> ProcessBinding::signals;
    ProcessBinding::ProcessBinding() :
        AccessorObject("Process")
    {
        
        /**
         * @tiapi(method=True,name=Process.createProcess,since=0.5)
         * @tiapi Create a Process object. There are two main ways to use this function:
         * @tiapi  With an options object (preferred):
         * @tiapi  Ti.Process.createProcess({args: ['mycmd', 'arg1', 'arg2'],
         * @tiapi     env: {'PATH': '/something'}, stdin: pipeIn, stdout: pipeOut, stderr: pipeErr});
         * @tiapi OR
         * @tiapi  Ti.Process.createProcess(args[, environment, stdin, stdout, stderr]);
         * @tiresult[Process.Process] The process object
         */
        SetMethod("createProcess", &ProcessBinding::CreateProcess);
        
        /**
         * @tiapi(method=True,name=Process.createPipe,since=0.5)
         * @tiapi Create an pipe for attach to/from any number of processes.
         * @tiresult[Process.Pipe] A new pipe
         */
        SetMethod("createPipe", &ProcessBinding::CreatePipe);

#if defined(OS_OSX) || (OS_LINUX)
        /**
         * @tiapi(property=True,name=Process.SIGHUP,since=0.5,platforms=osx|linux)
         */
        signals["SIGHUP"] = SIGHUP;
        /**
         * @tiapi(property=True,name=Process.SIGINT,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGINT"] = SIGINT;
        /**
         * @tiapi(property=True,name=Process.SIGQUIT,since=0.5,platforms=osx|linux)
         */
        signals["SIGQUIT"] = SIGQUIT;
        /**
         * @tiapi(property=True,name=Process.SIGILL,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGILL"] = SIGILL;
        /**
         * @tiapi(property=True,name=Process.SIGTRAP,since=0.5,platforms=osx|linux)
         */
        signals["SIGTRAP"] = SIGTRAP;
        /**
         * @tiapi(property=True,name=Process.SIGABRT,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGABRT"] = SIGABRT;
        /**
         * @tiapi(property=True,name=Process.SIGFPE,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGFPE"] = SIGFPE;
        /**
         * @tiapi(property=True,name=Process.SIGKILL,since=0.5,platforms=osx|linux)
         */
        signals["SIGKILL"] = SIGKILL;
        /**
         * @tiapi(property=True,name=Process.SIGBUS,since=0.5,platforms=osx|linux)
         */
        signals["SIGBUS"] = SIGBUS;
        /**
         * @tiapi(property=True,name=Process.SIGSEGV,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGSEGV"] = SIGSEGV;
        /**
         * @tiapi(property=True,name=Process.SIGSYS,since=0.5,platforms=osx|linux)
         */
        signals["SIGSYS"] = SIGSYS;
        /**
         * @tiapi(property=True,name=Process.SIGPIPE,since=0.5,platforms=osx|linux)
         */
        signals["SIGPIPE"] = SIGPIPE;
        /**
         * @tiapi(property=True,name=Process.SIGALRM,since=0.5,platforms=osx|linux)
         */
        signals["SIGALRM"] = SIGALRM;
        /**
         * @tiapi(property=True,name=Process.SIGTERM,since=0.5,platforms=osx|linux|win32)
         */
        signals["SIGTERM"] = SIGTERM;
        /**
         * @tiapi(property=True,name=Process.SIGURG,since=0.5,platforms=osx|linux)
         */
        signals["SIGURG"] = SIGURG;
        /**
         * @tiapi(property=True,name=Process.SIGSTOP,since=0.5,platforms=osx|linux)
         */
        signals["SIGSTOP"] = SIGSTOP;
        /**
         * @tiapi(property=True,name=Process.SIGTSTP,since=0.5,platforms=osx|linux)
         */
        signals["SIGTSTP"] = SIGTSTP;
        /**
         * @tiapi(property=True,name=Process.SIGCHLD,since=0.5,platforms=osx|linux)
         */
        signals["SIGCHLD"] = SIGCHLD;
        /**
         * @tiapi(property=True,name=Process.SIGTTIN,since=0.5,platforms=osx|linux)
         */
        signals["SIGTTIN"] = SIGTTIN;
        /**
         * @tiapi(property=True,name=Process.SIGTTOU,since=0.5,platforms=osx|linux)
         */
        signals["SIGTTOU"] = SIGTTOU;
        /**
         * @tiapi(property=True,name=Process.SIGIO,since=0.5,platforms=osx|linux)
         */
        signals["SIGIO"] = SIGIO;
        /**
         * @tiapi(property=True,name=Process.SIGXCPU,since=0.5,platforms=osx|linux)
         */
        signals["SIGXCPU"] = SIGXCPU;
        /**
         * @tiapi(property=True,name=Process.SIGXFSZ,since=0.5,platforms=osx|linux)
         */
        signals["SIGXFSZ"] = SIGXFSZ;
        /**
         * @tiapi(property=True,name=Process.SIGVTALRM,since=0.5,platforms=osx|linux)
         */
        signals["SIGVTALRM"] = SIGVTALRM;
        /**
         * @tiapi(property=True,name=Process.SIGPROF,since=0.5,platforms=osx|linux)
         */
        signals["SIGPROF"] = SIGPROF;
        /**
         * @tiapi(property=True,name=Process.SIGWINCH,since=0.5,platforms=osx|linux)
         */
        signals["SIGWINCH"] = SIGWINCH;
        /**
         * @tiapi(property=True,name=Process.SIGUSR1,since=0.5,platforms=osx|linux)
         */
        signals["SIGUSR1"] = SIGUSR1;
        /**
         * @tiapi(property=True,name=Process.SIGUSR2,since=0.5,platforms=osx|linux)
         */
        signals["SIGUSR2"] = SIGUSR2;
        
#elif defined(OS_WIN32)
        signals["SIGABRT"] = SIGABRT;
        signals["SIGFPE"] = SIGFPE;
        signals["SIGILL"] = SIGILL;
        signals["SIGINT"] = SIGINT;
        signals["SIGSEGV"] = SIGSEGV;
        signals["SIGTERM"] = SIGTERM;
#endif
#if defined(OS_OSX)
        /**
         * @tiapi(property=True,name=Process.SIGEMT,since=0.5,platforms=osx)
         */
        signals["SIGEMT"] = SIGEMT;
        /**
         * @tiapi(property=True,name=Process.SIGINFO,since=0.5,platforms=osx)
         */
        signals["SIGINFO"] = SIGINFO;
#endif
        std::map<std::string,int>::iterator iter;
        for (iter = signals.begin(); iter != signals.end(); iter++)
        {
            Set(iter->first.c_str(), Value::NewInt(iter->second));
        }
    }

    ProcessBinding::~ProcessBinding()
    {
    }

    void ProcessBinding::CreateProcess(const ValueList& args, KValueRef result)
    {
        args.VerifyException("createProcess", "o|l");
        TiObjectRef temp = 0;
        TiListRef argList = 0;
        TiObjectRef environment = 0;
        AutoPipe stdinPipe = 0;
        AutoPipe stdoutPipe = 0;
        AutoPipe stderrPipe = 0;

        if (args.at(0)->IsObject())
        {
            TiObjectRef options = args.GetObject(0);
            argList = options->GetList("args", 0);
            if (argList.isNull())
                throw ValueException::FromString(
                    "Ti.Process option 'args' must be an array");

            environment = options->GetObject("env", 0);

            temp = options->GetObject("stdin");
            if (!temp.isNull())
                stdinPipe = temp.cast<Pipe>();

            temp = options->GetObject("stdout");
            if (!temp.isNull())
                stdoutPipe = temp.cast<Pipe>();

            temp = options->GetObject("stderr");
            if (!temp.isNull())
                stderrPipe = temp.cast<Pipe>();

        }
        else if (args.at(0)->IsList())
        {
            argList = args.at(0)->ToList();
            
            if (args.size() > 1)
                environment = args.GetObject(1);

            if (args.size() > 2)
            {
                temp = args.GetObject(2);
                if (!temp.isNull())
                    stdinPipe = temp.cast<Pipe>();
            }

            if (args.size() > 3)
            {
                temp = args.GetObject(3);
                if (!temp.isNull())
                    stdoutPipe = temp.cast<Pipe>();
            }

            if (args.size() > 4)
            {
                temp = args.GetObject(4);
                if (!temp.isNull())
                    stderrPipe = temp.cast<Pipe>();
            }
        }

        if (argList.isNull())
        {
            throw ValueException::FromString(
                "Ti.Process option argument 'args' was undefined");
        }

        if (argList->Size() == 0)
        {
            throw ValueException::FromString(
                "Ti.Process option argument 'args' must have at least 1 element");
        }
        else if (argList->At(0)->IsNull() ||
            (argList->At(0)->IsString() && strlen(argList->At(0)->ToString()) == 0))
        {
            throw ValueException::FromString(
                "Ti.Process 1st argument must not be null/empty");
        }

        TiListRef argsClone = new StaticBoundList();
        ExtendArgs(argsClone, argList);

        AutoProcess process = Process::CreateProcess();
        process->SetArguments(argsClone);

        if (!environment.isNull())
            process->SetEnvironment(environment);
        if (!stdinPipe.isNull())
            process->SetStdin(stdinPipe);
        if (!stdoutPipe.isNull())
            process->SetStdout(stdoutPipe);
        if (!stderrPipe.isNull())
            process->SetStderr(stderrPipe);

        // this is a callable object
        result->SetMethod(process);
    }
    
    void ProcessBinding::ExtendArgs(TiListRef dest, TiListRef args)
    {
        for (size_t i = 0; i < args->Size(); i++)
        {
            KValueRef arg = Value::Undefined;
            if (args->At(i)->IsList())
            {
                TiListRef list = args->At(i)->ToList();
                ExtendArgs(dest, list);
                continue;
            }
            else if (!args->At(i)->IsString())
            {
                SharedString ss = args->At(i)->DisplayString();
                arg = Value::NewString(ss);
            }
            else
            {
                arg = args->At(i);
            }
            dest->Append(arg);
        }
    }

    void ProcessBinding::CreatePipe(const ValueList& args, KValueRef result)
    {
        result->SetObject(new Pipe());
    }
}
