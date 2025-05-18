//
// Created by Jackson Smoot on 5/15/25.
//
#include "objc_mac_gui.h"
#include "nucleus_core.h"
void *calloc(unsigned long count, unsigned long size);
void *realloc(void *ptr, unsigned long size);

typedef unsigned long size_t;
extern void *malloc(size_t size);
extern void free(void *ptr);

// Declaration for getcwd (no includes)
extern char *getcwd(char *buf, size_t size);

// String length
size_t my_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) ++len;
    return len;
}

// String copy
void my_strcpy(char *dst, const char *src) {
    while (*src) *dst++ = *src++;
    *dst = 0;
}

// String concatenate
void my_strcat(char *dst, const char *src) {
    while (*dst) ++dst;
    while (*src) *dst++ = *src++;
    *dst = 0;
}

// Create full path
char* join_path_with_filename(const char *filename) {
    size_t bufsize = 1024;
    char *cwd = (char *)malloc(bufsize);
    if (!cwd) return nullptr;

    if (!getcwd(cwd, bufsize)) {
        free(cwd);
        return nullptr;
    }

    size_t total = my_strlen(cwd) + my_strlen(filename) + 2;
    char *full = (char *)malloc(total);
    if (!full) {
        free(cwd);
        return nullptr;
    }

    my_strcpy(full, cwd);
    my_strcat(full, filename);

    free(cwd);
    return full; // Remember to free this
}

char* get_current_working_directory() {
    size_t bufsize = 1024; // or larger if needed
    char *buffer = (char *)malloc(bufsize);
    if (!buffer) return nullptr;

    if (getcwd(buffer, bufsize)) {
        return buffer; // Remember to free this later
    } else {
        free(buffer);
        return nullptr;
    }
}

void apple_arm64_log_msg(const char* str) {
    log_msg(str);
}

void apple_arm64_sleep(const NSTimeInterval interval) {

    SEL sleep_selector = sel_getUid("sleepForTimeInterval:");
    void (*sleep_for_seconds)(id, SEL, double) = (void (*)(id, SEL, double))objc_msgSend;
    sleep_for_seconds(cls_NSThread, sleep_selector, interval);
}

void set_app_icon_from_jpeg(const char* jpeg_path) {
    // NSString* path = [NSString stringWithUTF8String:jpeg_path];
    Class NSStringClass = objc_getClass("NSString");
    SEL sel_stringWithUTF8String = sel_getUid("stringWithUTF8String:");
    id ns_path = ((id (*)(Class, SEL, const char*))objc_msgSend)(NSStringClass, sel_stringWithUTF8String, jpeg_path);

    // NSImage* image = [[NSImage alloc] initWithContentsOfFile:path];
    Class NSImageClass = objc_getClass("NSImage");
    id img_alloc = ((id (*)(Class, SEL))objc_msgSend)(NSImageClass, sel_getUid("alloc"));
    SEL sel_initWithContentsOfFile = sel_getUid("initWithContentsOfFile:");
    id ns_image = ((id (*)(id, SEL, id))objc_msgSend)(img_alloc, sel_initWithContentsOfFile, ns_path);

    // [[NSApplication sharedApplication] setApplicationIconImage:image];
    Class NSApplicationClass = objc_getClass("NSApplication");
    id app = ((id (*)(Class, SEL))objc_msgSend)(NSApplicationClass, sel_getUid("sharedApplication"));
    SEL sel_setApplicationIconImage = sel_getUid("setApplicationIconImage:");
    ((void (*)(id, SEL, id))objc_msgSend)(app, sel_setApplicationIconImage, ns_image);
}

void apple_arm64_init_window(const Nucleus_FRect* rect) {
    Class NSAutoreleasePoolClass = objc_getClass("NSAutoreleasePool");
    id pool = ((id (*)(Class, SEL))objc_msgSend)(NSAutoreleasePoolClass, sel_getUid("new"));

    Class NSApplicationClass = objc_getClass("NSApplication");
    id app = ((id (*)(Class, SEL))objc_msgSend)(NSApplicationClass, sel_getUid("sharedApplication"));

    Class NSWindowClass = objc_getClass("NSWindow");

    // Create window rect
    CGRect cg_rect = { rect->x, rect->y, rect->w, rect->h };

    SEL initWithContentRect_styleMask_backing_defer = sel_getUid("initWithContentRect:styleMask:backing:defer:");

    id windowAlloc = ((id (*)(Class, SEL))objc_msgSend)(NSWindowClass, sel_getUid("alloc"));

    // Create the window by sending initWithContentRect:styleMask:backing:defer:
    id window = ((id (*)(id, SEL, struct CGRect, NSUInteger, NSUInteger, BOOL))objc_msgSend)(windowAlloc, initWithContentRect_styleMask_backing_defer,
        cg_rect,
        (NSUInteger)(1 << 0) | (1 << 1) | (1 << 2), // styleMask, e.g. NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
        2, // backing store type: NSBackingStoreBuffered = 2
        NO);

    SEL makeKeyAndOrderFront = sel_getUid("makeKeyAndOrderFront:");
    ((void (*)(id, SEL, id))objc_msgSend)(window, makeKeyAndOrderFront, nullptr);

    // Set activation policy to show in Dock and app switcher
    SEL setActivationPolicy = sel_getUid("setActivationPolicy:");
    ((BOOL (*)(id, SEL, NSInteger))objc_msgSend)(app, setActivationPolicy, 0); // NSApplicationActivationPolicyRegular = 0

    //
    char* icon_path = join_path_with_filename("/dev_icon.png");

    set_app_icon_from_jpeg(icon_path);

    if (icon_path) {
        free(icon_path);
    }

    SEL activateIgnoringOtherApps = sel_getUid("activateIgnoringOtherApps:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(app, activateIgnoringOtherApps, YES);

    SEL run = sel_getUid("run");
    ((void (*)(id, SEL))objc_msgSend)(app, run);

    ((void (*)(id, SEL))objc_msgSend)(pool, sel_getUid("release"));
}