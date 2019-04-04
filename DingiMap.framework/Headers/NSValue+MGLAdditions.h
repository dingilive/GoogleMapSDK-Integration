#import <Foundation/Foundation.h>

#import "DingiGeometry.h"
#import "DingiLight.h"
#import "DingiOfflinePack.h"
#import "DingiTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Methods for round-tripping values for Mapbox-defined types.
 */
@interface NSValue (MGLAdditions)

#pragma mark Working with Geographic Coordinate Values

/**
 Creates a new value object containing the specified Core Location geographic
 coordinate structure.

 @param coordinate The value for the new object.
 @return A new value object that contains the geographic coordinate information.
 */
+ (instancetype)valueWithMGLCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 The Core Location geographic coordinate structure representation of the value.
 */
@property (readonly) CLLocationCoordinate2D MGLCoordinateValue;

/**
 Creates a new value object containing the specified Mapbox map point structure.

 @param point The value for the new object.
 @return A new value object that contains the coordinate and zoom level information.
 */
+ (instancetype)valueWithMGLMapPoint:(MGLMapPoint)point;

/**
 The Mapbox map point structure representation of the value.
 */
@property (readonly) MGLMapPoint MGLMapPointValue;

/**
 Creates a new value object containing the specified Mapbox coordinate span
 structure.

 @param span The value for the new object.
 @return A new value object that contains the coordinate span information.
 */
+ (instancetype)valueWithDingiCoordinateSpan:(DingiCoordinateSpan)span;

/**
 The Mapbox coordinate span structure representation of the value.
 */
@property (readonly) DingiCoordinateSpan DingiCoordinateSpanValue;

/**
 Creates a new value object containing the specified Mapbox coordinate bounds
 structure.

 @param bounds The value for the new object.
 @return A new value object that contains the coordinate bounds information.
 */
+ (instancetype)valueWithDingiCoordinateBounds:(DingiCoordinateBounds)bounds;

/**
 The Mapbox coordinate bounds structure representation of the value.
 */
@property (readonly) DingiCoordinateBounds DingiCoordinateBoundsValue;

/**
 Creates a new value object containing the specified Mapbox coordinate 
 quad structure.

 @param quad The value for the new object.
 @return A new value object that contains the coordinate quad information.
 */
+ (instancetype)valueWithDingiCoordinateQuad:(DingiCoordinateQuad)quad;

/**
 The Mapbox coordinate quad structure representation of the value.
 */
- (DingiCoordinateQuad)DingiCoordinateQuadValue;

#pragma mark Working with Offline Map Values

/**
 Creates a new value object containing the given `DingiOfflinePackProgress`
 structure.

 @param progress The value for the new object.
 @return A new value object that contains the offline pack progress information.
 */
+ (NSValue *)valueWithDingiOfflinePackProgress:(DingiOfflinePackProgress)progress;

/**
 The `DingiOfflinePackProgress` structure representation of the value.
 */
@property (readonly) DingiOfflinePackProgress DingiOfflinePackProgressValue;

#pragma mark Working with Transition Values

/**
 Creates a new value object containing the given `DingiTransition`
 structure.
 
 @param transition The value for the new object.
 @return A new value object that contains the transition information.
 */
+ (NSValue *)valueWithDingiTransition:(DingiTransition)transition;

/**
 The `DingiTransition` structure representation of the value.
 */
@property (readonly) DingiTransition DingiTransitionValue;

/**
 Creates a new value object containing the given `DingiSphericalPosition`
 structure.
 
 @param lightPosition The value for the new object.
 @return A new value object that contains the light position information.
 */
+ (instancetype)valueWithDingiSphericalPosition:(DingiSphericalPosition)lightPosition;

/**
 The `DingiSphericalPosition` structure representation of the value.
 */
@property (readonly) DingiSphericalPosition DingiSphericalPositionValue;

/**
 Creates a new value object containing the given `DingiLightAnchor`
 enum.
 
 @param lightAnchor The value for the new object.
 @return A new value object that contains the light anchor information.
 */
+ (NSValue *)valueWithDingiLightAnchor:(DingiLightAnchor)lightAnchor;

/**
 The `DingiLightAnchor` enum representation of the value.
 */
@property (readonly) DingiLightAnchor DingiLightAnchorValue;

@end

NS_ASSUME_NONNULL_END
