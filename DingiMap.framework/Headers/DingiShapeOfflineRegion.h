#import <Foundation/Foundation.h>

#import "DingiFoundation.h"
#import "DingiOfflineRegion.h"
#import "DingiShape.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An offline region defined by a style URL, geographic shape, and
 range of zoom levels.
 
 This class requires fewer resources than DingiTilePyramidOfflineRegion
 for irregularly shaped regions.
 */
MGL_EXPORT
@interface DingiShapeOfflineRegion : NSObject <DingiOfflineRegion, NSSecureCoding, NSCopying>

/**
 The shape for the geographic region covered by the downloaded
 tiles.
 */
@property (nonatomic, readonly) DingiShape *shape;

/**
 The minimum zoom level for which to download tiles and other resources.

 For more information about zoom levels, `-[DingiMapView zoomLevel]`.
 */
@property (nonatomic, readonly) double minimumZoomLevel;

/**
 The maximum zoom level for which to download tiles and other resources.

 For more information about zoom levels, `-[DingiMapView zoomLevel]`.
 */
@property (nonatomic, readonly) double maximumZoomLevel;

- (instancetype)init NS_UNAVAILABLE;

/**
 Initializes a newly created offline region with the given style URL, geometry,
 and range of zoom levels.

 This is the designated initializer for `DingiShapeOfflineRegion`.

 @param styleURL URL of the map style for which to download resources. The URL
    may be a full HTTP or HTTPS URL.
 @param shape The shape of the geographic region to be covered by
    the downloaded tiles.
 @param minimumZoomLevel The minimum zoom level to be covered by the downloaded
    tiles. This parameter should be set to at least 0 but no greater than the
    value of the `maximumZoomLevel` parameter. For each required tile source, if
    this parameter is set to a value less than the tile source’s minimum zoom
    level, the download covers zoom levels down to the tile source’s minimum
    zoom level.
 @param maximumZoomLevel The maximum zoom level to be covered by the downloaded
    tiles. This parameter should be set to at least the value of the
    `minimumZoomLevel` parameter. For each required tile source, if this
    parameter is set to a value greater than the tile source’s minimum zoom
    level, the download covers zoom levels up to the tile source’s maximum zoom
    level.
 */
- (instancetype)initWithStyleURL:(nullable NSURL *)styleURL shape:(DingiShape *)shape fromZoomLevel:(double)minimumZoomLevel toZoomLevel:(double)maximumZoomLevel NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
