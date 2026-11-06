#include <SystemConfiguration/SystemConfiguration.h>
#include <CoreFoundation/CFRuntime.h>
#include <dispatch/dispatch.h>

// There is no configd to talk to, so a dynamic store is a private in-memory
// key/value table. It starts out empty, never receives notifications, and
// values set through one store are not visible to others.

struct __SCDynamicStore {
	CFRuntimeBase _base;
	CFMutableDictionaryRef values;
	CFArrayRef notificationKeys;
	CFArrayRef notificationPatterns;
	SCDynamicStoreCallBack callout;
	SCDynamicStoreContext context;
};

static void SCDynamicStoreDeallocate(CFTypeRef cf)
{
	struct __SCDynamicStore* store = (struct __SCDynamicStore*)cf;

	if (store->values)
		CFRelease(store->values);
	if (store->notificationKeys)
		CFRelease(store->notificationKeys);
	if (store->notificationPatterns)
		CFRelease(store->notificationPatterns);
	if (store->context.release && store->context.info)
		store->context.release(store->context.info);
}

static CFTypeID gSCDynamicStoreTypeID = _kCFRuntimeNotATypeID;

static const CFRuntimeClass SCDynamicStoreClass = {
	0,
	"SCDynamicStore",
	NULL,
	NULL,
	SCDynamicStoreDeallocate,
	NULL,
	NULL,
	NULL,
	NULL
};

CFTypeID SCDynamicStoreGetTypeID(void)
{
	static dispatch_once_t once;
	dispatch_once(&once, ^{
		gSCDynamicStoreTypeID = _CFRuntimeRegisterClass(&SCDynamicStoreClass);
	});
	return gSCDynamicStoreTypeID;
}

SCDynamicStoreRef SCDynamicStoreCreateWithOptions(CFAllocatorRef allocator, CFStringRef name, CFDictionaryRef storeOptions, SCDynamicStoreCallBack callout, SCDynamicStoreContext* context)
{
	struct __SCDynamicStore* store = (struct __SCDynamicStore*)_CFRuntimeCreateInstance(allocator, SCDynamicStoreGetTypeID(), sizeof(struct __SCDynamicStore) - sizeof(CFRuntimeBase), NULL);

	if (!store)
		return NULL;

	store->values = CFDictionaryCreateMutable(allocator, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	store->callout = callout;
	if (context) {
		store->context = *context;
		if (context->retain && context->info)
			store->context.info = (void*)context->retain(context->info);
	}

	return (SCDynamicStoreRef)store;
}

SCDynamicStoreRef SCDynamicStoreCreate(CFAllocatorRef allocator, CFStringRef name, SCDynamicStoreCallBack callout, SCDynamicStoreContext* context)
{
	return SCDynamicStoreCreateWithOptions(allocator, name, NULL, callout, context);
}

CFPropertyListRef SCDynamicStoreCopyValue(SCDynamicStoreRef store, CFStringRef key)
{
	CFTypeRef value;

	if (!store || !key)
		return NULL;

	value = CFDictionaryGetValue(((struct __SCDynamicStore*)store)->values, key);
	return value ? CFRetain(value) : NULL;
}

Boolean SCDynamicStoreSetValue(SCDynamicStoreRef store, CFStringRef key, CFPropertyListRef value)
{
	if (!store || !key || !value)
		return FALSE;

	CFDictionarySetValue(((struct __SCDynamicStore*)store)->values, key, value);
	return TRUE;
}

Boolean SCDynamicStoreRemoveValue(SCDynamicStoreRef store, CFStringRef key)
{
	if (!store || !key)
		return FALSE;

	CFDictionaryRemoveValue(((struct __SCDynamicStore*)store)->values, key);
	return TRUE;
}

Boolean SCDynamicStoreSetNotificationKeys(SCDynamicStoreRef store, CFArrayRef keys, CFArrayRef patterns)
{
	struct __SCDynamicStore* s = (struct __SCDynamicStore*)store;
	CFArrayRef oldKeys, oldPatterns;

	if (!store)
		return FALSE;

	oldKeys = s->notificationKeys;
	oldPatterns = s->notificationPatterns;
	s->notificationKeys = keys ? CFRetain(keys) : NULL;
	s->notificationPatterns = patterns ? CFRetain(patterns) : NULL;
	if (oldKeys)
		CFRelease(oldKeys);
	if (oldPatterns)
		CFRelease(oldPatterns);
	return TRUE;
}

CFArrayRef SCDynamicStoreCopyNotifiedKeys(SCDynamicStoreRef store)
{
	return CFArrayCreate(NULL, NULL, 0, &kCFTypeArrayCallBacks);
}

Boolean SCDynamicStoreSetDispatchQueue(SCDynamicStoreRef store, dispatch_queue_t queue)
{
	return store != NULL;
}

static void noopSchedule(void* info, CFRunLoopRef rl, CFStringRef mode) {}
static void noopCancel(void* info, CFRunLoopRef rl, CFStringRef mode) {}
static void noopPerform(void* info) {}

// The source never fires (the store has no notifications) but callers expect
// to be able to add it to a run loop.
CFRunLoopSourceRef SCDynamicStoreCreateRunLoopSource(CFAllocatorRef allocator, SCDynamicStoreRef store, CFIndex order)
{
	CFRunLoopSourceContext context = {0};

	if (!store)
		return NULL;

	context.info = (void*)store;
	context.schedule = noopSchedule;
	context.cancel = noopCancel;
	context.perform = noopPerform;
	return CFRunLoopSourceCreate(allocator, order, &context);
}
