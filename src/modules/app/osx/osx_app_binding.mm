/**
 * Appcelerator - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#include <tide/tide.h>
#include "../app_binding.h"
#include <Foundation/Foundation.h>

@interface TideExitNotificationListener : NSObject
@end

@implementation TideExitNotificationListener

-(void)tideExitNotification:(id)event
{
	Host* host = Host::GetInstance();
	host->Exit(0);
}

@end

namespace ti
{

void AppBinding::Restart(const ValueList& args, KValueRef result)
{
	Host* host = Host::GetInstance();
	std::string cmdline(host->GetApplication()->arguments.at(0));

	NSProcessInfo* p = [NSProcessInfo processInfo];
	NSString* path = [[NSBundle mainBundle] bundlePath];
	NSString* killArg1AndOpenArg2Script = [NSString 
		stringWithFormat:@"kill -9 %d\n open \"%@\"",
		[p processIdentifier], path];

	// -c tells sh to execute the next argument, passing it the remaining arguments.
	NSArray* shArgs = [NSArray arrayWithObjects:@"-c",
		killArg1AndOpenArg2Script, nil];
	NSTask* restartTask = [NSTask launchedTaskWithLaunchPath:@"/bin/sh" arguments:shArgs];
	[restartTask waitUntilExit]; //wait for killArg1AndOpenArg2Script to finish

	host->Exit(0);
}

void AppBinding::Setup() 
{
	// We register a generic notification listener for listening for TideExit events
	// which come from the boot when we have no active windows in the responder chain
	// and the NSApplication delegate receives the terminate.  
	TideExitNotificationListener *listener = [[TideExitNotificationListener alloc] init];
	[[NSNotificationCenter defaultCenter] addObserver:listener selector:@selector(tideExitNotification:) name:@"TideExit" object:nil];
	[listener release];
}

}
