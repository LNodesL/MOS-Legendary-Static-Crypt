#import <Cocoa/Cocoa.h>

@interface HelloWorldApp : NSObject <NSApplicationDelegate>
@property (strong) NSWindow *window;
@property (strong) NSTextField *label;
@end

@implementation HelloWorldApp

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Create the main window
    self.window = [[NSWindow alloc] initWithContentRect:NSMakeRect(100, 100, 400, 200)
                                              styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                                                backing:NSBackingStoreBuffered
                                                  defer:NO];
    
    [self.window setTitle:@"Hello World GUI"];
    [self.window center];
    
    // Create a label
    self.label = [[NSTextField alloc] initWithFrame:NSMakeRect(50, 80, 300, 40)];
    [self.label setStringValue:@"Hello, World!\nThis is a macOS GUI application that will be packaged into bytes."];
    [self.label setBezeled:NO];
    [self.label setDrawsBackground:NO];
    [self.label setEditable:NO];
    [self.label setSelectable:NO];
    [self.label setAlignment:NSTextAlignmentCenter];
    [self.label setFont:[NSFont systemFontOfSize:16]];
    
    // Add label to window
    [[self.window contentView] addSubview:self.label];
    
    // Show the window
    [self.window makeKeyAndOrderFront:nil];
    
    // Also print to console for runtime output
    printf("Hello, World! (GUI version)\n");
    printf("This is a macOS GUI application that will be packaged into bytes.\n");
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end

int main() {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        HelloWorldApp *appDelegate = [[HelloWorldApp alloc] init];
        [app setDelegate:appDelegate];
        [app run];
    }
    return 0;
}
