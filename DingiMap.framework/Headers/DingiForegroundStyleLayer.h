#import <Foundation/Foundation.h>

#import "DingiFoundation.h"
#import "DingiStyleLayer.h"

NS_ASSUME_NONNULL_BEGIN

@class DingiSource;

/**
 `DingiForegroundStyleLayer` is an abstract superclass for style layers whose
 content is defined by an `DingiSource` object.

 Create instances of `DingiRasterStyleLayer`, `DingiHillshadeStyleLayer`, and the
 concrete subclasses of `DingiVectorStyleLayer` in order to use
 `DingiForegroundStyleLayer`'s methods. Do not create instances of
 `DingiForegroundStyleLayer` directly, and do not create your own subclasses of
 this class.
 */
MGL_EXPORT
@interface DingiForegroundStyleLayer : DingiStyleLayer

#pragma mark Initializing a Style Layer

- (instancetype)init __attribute__((unavailable("Use -init methods of concrete subclasses instead.")));

#pragma mark Specifying a Style Layer’s Content

/**
 Identifier of the source from which the receiver obtains the data to style.
 */
@property (nonatomic, readonly, nullable) NSString *sourceIdentifier;

@end

NS_ASSUME_NONNULL_END
