#import "DingiFoundation.h"
#import "DingiGeometry.h"
#import "DingiTypes.h"
#import "DingiShapeSource.h"

NS_ASSUME_NONNULL_BEGIN

@protocol DingiFeature;

/**
 An `NSNumber` object containing a Boolean value; specifies whether the shape of
 an `DingiComputedShapeSource` should be wrapped to accomodate coordinates with
 longitudes beyond −180 and 180. The default value is `NO`.
 
 Setting this option to `YES` affects rendering performance.
 
 This option is used with the `DingiComputedShapeSource` class; it is ignored when
 creating an `DingiShapeSource` object.
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionWrapsCoordinates;

/**
 An `NSNumber` object containing a Boolean value; specifies whether the shape of
 an `DingiComputedShapeSource` should be clipped at the edge of each tile. The
 default value is `NO`.
 
 Setting this option to `YES` affects rendering performance. Use this option to
 clip `DingiPolyline`s and `DingiPolygon`s at tile boundaries without artifacts.
 
 This option is used with the `DingiComputedShapeSource` class; it is ignored when
 creating an `DingiShapeSource` object.
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionClipsCoordinates;

FOUNDATION_EXTERN MGL_EXPORT MGLExceptionName const MGLInvalidDatasourceException;

/**
 Data source for `DingiComputedShapeSource`. This protocol defines two optional methods for fetching
 data, one based on tile coordinates, and one based on a bounding box. Classes that implement this
 protocol must implement one, and only one of the methods. Methods on this protocol will not be
 called on main thread, they will be called on the caller's `requestQueue`.
 */
@protocol DingiComputedShapeSourceDataSource <NSObject>

@optional
/**
 Fetch features for a tile. This method will not be invoked on the main queue, it
 will be invoked on the caller's `requestQueue`.
 @param x Tile X coordinate.
 @param y Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (NSArray<DingiShape <DingiFeature> *>*)featuresInTileAtX:(NSUInteger)x y:(NSUInteger)y zoomLevel:(NSUInteger)zoomLevel;

/**
 Fetch features for a tile. This method will not be invoked on the main queue, it
 will be invoked on the caller's `requestQueue`.
 @param bounds The bounds to fetch data for.
 @param zoomLevel Tile zoom level.
 */
- (NSArray<DingiShape <DingiFeature> *>*)featuresInCoordinateBounds:(DingiCoordinateBounds)bounds zoomLevel:(NSUInteger)zoomLevel;

@end

/**
 `DingiComputedShapeSource` is a map content source that supplies vector shapes,
 one tile at a time, to be shown on the map on demand. You implement a class
 conforming to the `DingiComputedShapeSourceDataSource` protocol that returns
 instances of `DingiShape` or `DingiFeature`, then add a computed shape source to an
 `DingiStyle` object along with an `DingiVectorStyleLayer` object. The vector style
 layer defines the appearance of any content supplied by the computed shape
 source.
 
 `DingiComputedShapeSource` is similar to `DingiShapeSource` but is optimized for
 data sets that change dynamically or are too large to fit completely in memory.
 It is also useful for data that is divided into tiles in a format other than
 <a href="https://www.mapbox.com/vector-tiles/">Mapbox Vector Tiles</a>. For
 <a href="http://geojson.org/">GeoJSON</a> data, use the `DingiShapeSource` class.
 For static tiles or Mapbox Vector Tiles, use the `DingiVectorTileSource` class.
 
 You can add and remove sources dynamically using methods such as
 `-[DingiStyle addSource:]` and `-[DingiStyle sourceWithIdentifier:]`. This class
 cannot be represented in a style JSON file; you must add it ot the style at
 runtime.
 */
MGL_EXPORT
@interface DingiComputedShapeSource : DingiSource

/**
 Returns a custom shape data source initialized with an identifier, and a
 dictionary of options for the source according to the
 <a href="https://www.mapbox.com/mapbox-gl-style-spec/#sources-geojson">style
 specification</a>.
 
 This class supports the following options:
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`,
 `DingiShapeSourceOptionSimplificationTolerance`,
 `DingiShapeSourceOptionWrapsCoordinates`, and
 `DingiShapeSourceOptionClipsCoordinates`. Shapes provided by a computed
 shape source cannot be clustered.

 @param identifier A string that uniquely identifies the source.
 @param options An `NSDictionary` of options for this source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options NS_DESIGNATED_INITIALIZER;

/**
 Returns a custom shape data source initialized with an identifier, data source, and a
 dictionary of options for the source according to the
 <a href="https://www.mapbox.com/mapbox-gl-style-spec/#sources-geojson">style
 specification</a>.
 
 This class supports the following options:
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`,
 `DingiShapeSourceOptionSimplificationTolerance`,
 `DingiShapeSourceOptionWrapsCoordinates`, and
 `DingiShapeSourceOptionClipsCoordinates`. Shapes provided by a computed shape
 source cannot be clustered.

 @param identifier A string that uniquely identifies the source.
 @param options An `NSDictionary` of options for this source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier dataSource:(id<DingiComputedShapeSourceDataSource>)dataSource options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options;

/**
 Invalidates all the features and properties intersecting with or contained in
 the specified bounds. New fetch requests will immediately be invoked on the
 `DingiComputedShapeSourceDataSource`.
 @param bounds  Coordinate bounds to invalidate.
 */
- (void) invalidateBounds:(DingiCoordinateBounds)bounds;

/**
 Invalidates all the feautres and properties of a given tile. A new fetch request
 will immediately be invoked on the `DingiComputedShapeSourceDataSource`.
 @param x Tile X coordinate.
 @param y Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (void) invalidateTileAtX:(NSUInteger)x y:(NSUInteger)y zoomLevel:(NSUInteger)zoomLevel;

/**
 Set a new set of features for a tile. This method can be invkoed from background threads.
 For best performance, use this method only to update tiles that have already been requested
 through `DingiComputedShapeSourceDataSource.`
 @param features  Features for the tile.
 @param x         Tile X coordinate.
 @param y         Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (void) setFeatures:(NSArray<DingiShape <DingiFeature> *>*)features inTileAtX:(NSUInteger)x y:(NSUInteger)y zoomLevel:(NSUInteger)zoomLevel;

/**
 An object that implements the `DingiComputedShapeSourceDataSource` protocol that will be queried for tile data.
 */
@property (nonatomic, weak, nullable) id<DingiComputedShapeSourceDataSource> dataSource;

/**
 A queue that calls to the data source will be made on.
 */
@property (nonatomic, readonly) NSOperationQueue *requestQueue;

@end

NS_ASSUME_NONNULL_END
