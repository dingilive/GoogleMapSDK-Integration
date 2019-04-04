#import <Foundation/Foundation.h>

#import "DingiFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Constants indicating the message's logging level.
 */
typedef NS_ENUM(NSInteger, DingiLoggingLevel) {
    /**
     None-level messages are ignored.
     */
    DingiLoggingLevelNone = 0,
    /**
     Info-level messages contain information that may be helpful for flow tracing
     but is not essential.
     */
    DingiLoggingLevelInfo,
    /**
     Debug-level messages contain information that may be helpful for troubleshooting
     specific problems.
     */
    DingiLoggingLevelDebug,
    /**
     Error-level messages contain information that is intended to aid in process-level
     errors.
     */
    DingiLoggingLevelError,
    /**
     Fault-level messages contain system-level error information.
     */
    DingiLoggingLevelFault,
    /**
     :nodoc: Any new logging level should be included in the default logging implementation.
     */
};

/**
 A block to be called once `loggingLevel` is set to a higher value than `DingiLoggingLevelNone`.
 
 @param loggingLevel The message logging level.
 @param filePath The description of the file and method for the calling message.
 @param line The line where the message is logged.
 @param message The logging message.
 */
typedef void (^DingiLoggingBlockHandler)(DingiLoggingLevel loggingLevel, NSString *filePath, NSUInteger line, NSString *message);

/**
 The `DingiLoggingConfiguration` object provides a global way to set this SDK logging levels
 and logging handler.
 */
MGL_EXPORT
@interface DingiLoggingConfiguration : NSObject

/**
 The handler this SDK uses to log messages.
 
 If this property is set to nil or if no custom handler is provided this property
 is set to the default handler.
 
 The default handler uses `os_log` and `NSLog` for iOS 10+ and iOS < 10 respectively.
 */
@property (nonatomic, copy, null_resettable) DingiLoggingBlockHandler handler;

/**
 The logging level.
 
 The default value is `DingiLoggingLevelNone`.
 
 Setting this property includes logging levels less than or equal to the setted value.
 */
@property (assign, nonatomic) DingiLoggingLevel loggingLevel;

/**
 Returns the shared logging object.
 */
@property (class, nonatomic, readonly) DingiLoggingConfiguration *sharedConfiguration;

- (DingiLoggingBlockHandler)handler UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
