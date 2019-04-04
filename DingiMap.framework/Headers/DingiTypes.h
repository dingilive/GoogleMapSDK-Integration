#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#import "DingiFoundation.h"

#pragma once

#if TARGET_OS_IPHONE
@class UIImage;
#define MGLImage UIImage
#else
@class NSImage;
#define MGLImage NSImage
#endif

#if TARGET_OS_IPHONE
@class UIColor;
#define MGLColor UIColor
#else
@class NSColor;
#define MGLColor NSColor
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NSString *MGLExceptionName NS_TYPED_EXTENSIBLE_ENUM;

/**
 :nodoc: Generic exceptions used across multiple disparate classes. Exceptions
 that are unique to a class or class-cluster should be defined in those headers.
 */
FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLAbstractClassException;

/** Indicates an error occurred in the Mapbox SDK. */
FOUNDATION_EXTERN MGL_EXPORT NSErrorDomain const DingiErrorDomain;

/** Error constants for the Mapbox SDK. */
typedef NS_ENUM(NSInteger, DingiErrorCode) {
    /** An unknown error occurred. */
    DingiErrorCodeUnknown = -1,
    /** The resource could not be found. */
    DingiErrorCodeNotFound = 1,
    /** The connection received an invalid server response. */
    DingiErrorCodeBadServerResponse = 2,
    /** An attempt to establish a connection failed. */
    DingiErrorCodeConnectionFailed = 3,
    /** A style parse error occurred while attempting to load the map. */
    DingiErrorCodeParseStyleFailed = 4,
    /** An attempt to load the style failed. */
    DingiErrorCodeLoadStyleFailed = 5,
    /** An error occurred while snapshotting the map. */
    DingiErrorCodeSnapshotFailed = 6
};

/** Options for enabling debugging features in an `DingiMapView` instance. */
typedef NS_OPTIONS(NSUInteger, DingiMapDebugMaskOptions) {
    /** Edges of tile boundaries are shown as thick, red lines to help diagnose
        tile clipping issues. */
    MGLMapDebugTileBoundariesMask = 1 << 1,
    /** Each tile shows its tile coordinate (x/y/z) in the upper-left corner. */
    MGLMapDebugTileInfoMask = 1 << 2,
    /** Each tile shows a timestamp indicating when it was loaded. */
    MGLMapDebugTimestampsMask = 1 << 3,
    /** Edges of glyphs and symbols are shown as faint, green lines to help
        diagnose collision and label placement issues. */
    MGLMapDebugCollisionBoxesMask = 1 << 4,
    /** Each drawing operation is replaced by a translucent fill. Overlapping
        drawing operations appear more prominent to help diagnose overdrawing.
        @note This option does nothing in Release builds of the SDK. */
    MGLMapDebugOverdrawVisualizationMask = 1 << 5,
#if !TARGET_OS_IPHONE
    /** The stencil buffer is shown instead of the color buffer.
        @note This option does nothing in Release builds of the SDK. */
    MGLMapDebugStencilBufferMask = 1 << 6,
    /** The depth buffer is shown instead of the color buffer.
        @note This option does nothing in Release builds of the SDK. */
    MGLMapDebugDepthBufferMask = 1 << 7,
#endif
};

/**
 A structure containing information about a transition.
 */
typedef struct __attribute__((objc_boxable)) DingiTransition {
    /**
     The amount of time the animation should take, not including the delay.
     */
    NSTimeInterval duration;
    
    /**
     The amount of time in seconds to wait before beginning the animation.
     */
    NSTimeInterval delay;
} DingiTransition;

/**
 Creates a new `DingiTransition` from the given duration and delay.
 
 @param duration The amount of time the animation should take, not including 
 the delay.
 @param delay The amount of time in seconds to wait before beginning the 
 animation.
 
 @return Returns a `DingiTransition` struct containing the transition attributes.
 */
NS_INLINE DingiTransition DingiTransitionMake(NSTimeInterval duration, NSTimeInterval delay) {
    DingiTransition transition;
    transition.duration = duration;
    transition.delay = delay;
    
    return transition;
}

NS_ASSUME_NONNULL_END