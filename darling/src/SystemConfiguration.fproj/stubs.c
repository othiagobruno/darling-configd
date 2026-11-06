#include <string.h>
#include <stdio.h>
#include <SystemConfiguration/SystemConfiguration.h>

#define STUB() printf("STUB %s\n", __func__)

const CFStringRef kSCDynamicStoreUseSessionKeys = CFSTR("UseSessionKeys");

CFTypeID SCNetworkConnectionGetTypeID(void)
{
    STUB();
	return 0;
}

Boolean SCNetworkConnectionScheduleWithRunLoop(SCNetworkConnectionRef ref, CFRunLoopRef rl, CFStringRef rlMode)
{
    STUB();
	return 0;
}

Boolean SCNetworkConnectionUnscheduleFromRunLoop(SCNetworkConnectionRef ref, CFRunLoopRef rl, CFStringRef rlMode)
{
    STUB();
	return 0;
}

Boolean SCNetworkConnectionStop(SCNetworkConnectionRef ref, Boolean force)
{
    STUB();
	return 0;
}

Boolean SCNetworkConnectionStart(SCNetworkConnectionRef ref, CFDictionaryRef userOptions, Boolean linger)
{
    STUB();
	return 0;
}

Boolean
SCNetworkConnectionCopyUserPreferences		(
						CFDictionaryRef				  __nullable	selectionOptions,
						CFStringRef		__nonnull	* __nullable	serviceID,
						CFDictionaryRef		__nonnull	* __nullable	userOptions
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA) {
    STUB();
	return 0;
}

SCNetworkConnectionRef SCNetworkConnectionCreateWithServiceID(CFAllocatorRef allocator, CFStringRef serviceID, SCNetworkConnectionCallBack cb, SCNetworkConnectionContext* ctxt)
{
    STUB();
	return NULL;
}

CFTypeID SCNetworkReachabilityGetTypeID(void)
{
    STUB();
	return 0;
}

Boolean SCNetworkReachabilityScheduleWithRunLoop(SCNetworkReachabilityRef ref, CFRunLoopRef rl, CFStringRef rlMode)
{
    STUB();
	return 0;
}

Boolean SCNetworkReachabilityUnscheduleFromRunLoop(SCNetworkReachabilityRef ref, CFRunLoopRef rl, CFStringRef rlMode)
{
    STUB();
	return 0;
}

Boolean SCNetworkReachabilitySetCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityCallBack cb, SCNetworkReachabilityContext* ctxt)
{
    STUB();
	return 0;
}

Boolean SCNetworkReachabilityGetFlags(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags* flags)
{
    STUB();
	return 0;
}

SCNetworkReachabilityRef SCNetworkReachabilityCreateWithName(CFAllocatorRef allocator, const char* nodeName)
{
    STUB();
	return NULL;
}

SCNetworkReachabilityRef SCNetworkReachabilityCreateWithAddressPair(CFAllocatorRef allocator, const struct sockaddr* localAddress, const struct sockaddr* remoteAddress)
{
    STUB();
	return NULL;
}

SCNetworkReachabilityRef SCNetworkReachabilityCreateWithAddress(CFAllocatorRef allocator, const struct sockaddr* remoteAddress)
{
    STUB();
	return NULL;
}

CFStringRef SCDynamicStoreKeyCreateNetworkGlobalEntity(CFAllocatorRef allocator, CFStringRef domain, CFStringRef entity)
{
	// the domain constants already carry their trailing colon (e.g. "State:")
	return CFStringCreateWithFormat(allocator, NULL, CFSTR("%@/%@/%@/%@"), domain, kSCCompNetwork, kSCCompGlobal, entity);
}




CFStringRef SCDynamicStoreKeyCreate(CFAllocatorRef allocator, CFStringRef fmt, ...)
{
	STUB();
	return NULL;
}



CFStringRef SCDynamicStoreKeyCreateComputerName(CFAllocatorRef allocator) {
	STUB();
	return NULL;
};

Boolean SCPreferencesSetComputerName(SCPreferencesRef	prefs, CFStringRef __nullable	name, CFStringEncoding	nameEncoding) {
	STUB();
	return FALSE;
};

Boolean SCPreferencesSetLocalHostName(SCPreferencesRef	prefs, CFStringRef __nullable	name) {
	STUB();
	return FALSE;
};

CFStringRef SCDynamicStoreKeyCreateHostNames(CFAllocatorRef allocator) {
	STUB();
	return NULL;
};

CFStringRef SCDynamicStoreKeyCreateNetworkInterfaceEntity(CFAllocatorRef allocator, CFStringRef domain, CFStringRef ifname, CFStringRef entity) {
	STUB();
	return NULL;
};

CFStringRef SCDynamicStoreKeyCreateProxies(CFAllocatorRef allocator)
{
	return SCDynamicStoreKeyCreateNetworkGlobalEntity(allocator, kSCDynamicStoreDomainState, kSCEntNetProxies);
}

const char *SCErrorString(int status)
{
	switch (status) {
		case kSCStatusOK:			return "Success!";
		case kSCStatusFailed:			return "Failed!";
		case kSCStatusInvalidArgument:		return "Invalid argument";
		case kSCStatusAccessError:		return "Permission denied (must be root to perform this operation)";
		case kSCStatusNoKey:			return "No such key";
		case kSCStatusKeyExists:		return "Key already defined";
		case kSCStatusLocked:			return "Lock already held";
		case kSCStatusNeedLock:			return "Lock required for this operation";
		case kSCStatusNoStoreSession:		return "Configuration daemon session not active";
		case kSCStatusNoStoreServer:		return "Configuration daemon not (no longer) available";
		case kSCStatusNotifierActive:		return "Notifier is currently active";
		case kSCStatusNoPrefsSession:		return "Preference session not active";
		case kSCStatusPrefsBusy:		return "Preferences update currently in progress";
		case kSCStatusNoConfigFile:		return "Configuration file not found";
		case kSCStatusNoLink:			return "No such link";
		case kSCStatusStale:			return "Write attempted on stale version of object";
		case kSCStatusMaxLink:			return "Maximum link count exceeded";
		case kSCStatusReachabilityUnknown:	return "Network reachability cannot be determined";
		case kSCStatusConnectionNoService:	return "Network service for connection not available";
		case kSCStatusConnectionIgnore:		return "Network connection information not available at this time";
		default:
			// Values in the range of errno are reported using the C library's text.
			if (status > 0 && status < 1000)
				return strerror(status);
			return "(unknown status)";
	}
}
