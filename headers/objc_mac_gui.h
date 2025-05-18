//
// Created by Jackson Smoot on 5/15/25.
//

#ifndef OBJC_MAC_GUI_H
#define OBJC_MAC_GUI_H

// Basic types
typedef void *id;
typedef void *SEL;
typedef void *Class;
typedef signed long NSInteger;
typedef unsigned long NSUInteger;
typedef signed char BOOL;
#define YES ((BOOL)1)
#define NO  ((BOOL)0)
typedef struct CGRect {
    double origin_x;
    double origin_y;
    double size_w;
    double size_h;
} CGRect;
typedef struct CGSize {
    double width;
    double height;
} CGSize;
typedef struct CGPoint {
    double x;
    double y;
} CGPoint;
typedef struct NSRange {
    NSUInteger location;
    NSUInteger length;
} NSRange;

// Core runtime functions
extern Class objc_getClass(const char *name);
extern SEL sel_getUid(const char *name);
extern id objc_msgSend(id self, SEL op, ...);
extern void NSLog(id format, ...);

// Shorthand type
typedef id NSString;
typedef id NSWindow;
typedef id NSApplication;
typedef id NSAutoreleasePool;
typedef id NSButton;
typedef id NSObject;
typedef id NSView;
typedef id NSMenu;
typedef id NSMenuItem;
typedef id NSImage;
typedef double NSTimeInterval;

// Common class lookups
#define cls_NSString         objc_getClass("NSString")
#define cls_NSWindow         objc_getClass("NSWindow")
#define cls_NSApplication    objc_getClass("NSApplication")
#define cls_NSAutoreleasePool objc_getClass("NSAutoreleasePool")
#define cls_NSButton         objc_getClass("NSButton")
#define cls_NSMenu           objc_getClass("NSMenu")
#define cls_NSMenuItem       objc_getClass("NSMenuItem")
#define cls_NSThread         objc_getClass("NSThread")

// Common selector shortcuts
#define sel_alloc                sel_getUid("alloc")
#define sel_init                 sel_getUid("init")
#define sel_release              sel_getUid("release")
#define sel_autorelease          sel_getUid("autorelease")
#define sel_makeKeyAndOrderFront sel_getUid("makeKeyAndOrderFront:")
#define sel_setTitle             sel_getUid("setTitle:")
#define sel_setContentView       sel_getUid("setContentView:")
#define sel_addSubview           sel_getUid("addSubview:")
#define sel_setTarget            sel_getUid("setTarget:")
#define sel_setAction            sel_getUid("setAction:")
#define sel_setMenu              sel_getUid("setMenu:")
#define sel_addItem              sel_getUid("addItem:")
#define sel_setSubmenu           sel_getUid("setSubmenu:")

// Message send wrappers
#define send_msg0(ret_type, obj, sel_name) \
    ((ret_type (*)(id, SEL))objc_msgSend)((obj), (sel_name))

#define send_msg1(ret_type, obj, sel_name, a1) \
    ((ret_type (*)(id, SEL, __typeof__(a1)))objc_msgSend)((obj), (sel_name), (a1))

#define send_msg2(ret_type, obj, sel_name, a1, a2) \
    ((ret_type (*)(id, SEL, __typeof__(a1), __typeof__(a2)))objc_msgSend)((obj), (sel_name), (a1), (a2))

#define send_msg3(ret_type, obj, sel_name, a1, a2, a3) \
    ((ret_type (*)(id, SEL, __typeof__(a1), __typeof__(a2), __typeof__(a3)))objc_msgSend)((obj), (sel_name), (a1), (a2), (a3))

// NSString helper (creates NSString from C string)
static inline NSString nsstring_from_c(const char *cstr) {
    SEL stringWithUTF8String = sel_getUid("stringWithUTF8String:");
    return ((id (*)(id, SEL, const char *))objc_msgSend)(cls_NSString, stringWithUTF8String, cstr);
}

// Logging helper
static inline void log_msg(const char *msg) {
    NSLog(nsstring_from_c(msg));
}

#endif // OBJC_MAC_GUI_H

