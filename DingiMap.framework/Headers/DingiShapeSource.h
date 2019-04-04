#import "DingiFoundation.h"
#import "DingiTypes.h"
#import "DingiSource.h"

NS_ASSUME_NONNULL_BEGIN

@protocol DingiFeature;
@class DingiShape;

/**
 Options for `DingiShapeSource` objects.
 */
typedef NSString *DingiShapeSourceOption NS_STRING_ENUM;

/**
 An `NSNumber` object containing a Boolean enabling or disabling clustering.
 If the `shape` property contains point shapes, setting this option to
 `YES` clusters the points by radius into groups. The default value is `NO`.
 

 
 This option only affects point features within an `DingiShapeSource` object; it
 is ignored when creating an `DingiComputedShapeSource` object.
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionClustered;

/**
 An `NSNumber` object containing an integer; specifies the radius of each
 cluster if clustering is enabled. A value of 512 produces a radius equal to
 the width of a tile. The default value is 50.
 
 This option only affects point features within an `DingiShapeSource` object; it
 is ignored when creating an `DingiComputedShapeSource` object.
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionClusterRadius;

/**
 An `NSNumber` object containing an integer; specifies the maximum zoom level at
 which to cluster points if clustering is enabled. Defaults to one zoom level
 less than the value of `DingiShapeSourceOptionMaximumZoomLevel` so that, at the
 maximum zoom level, the shapes are not clustered.
 

 
 This option only affects point features within an `DingiShapeSource` object; it
 is ignored when creating an `DingiComputedShapeSource` object.
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionMaximumZoomLevelForClustering;

/**
 An `NSNumber` object containing an integer; specifies the minimum zoom level at
 which to create vector tiles. The default value is 0.


 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionMinimumZoomLevel;

/**
 An `NSNumber` object containing an integer; specifies the maximum zoom level at
 which to create vector tiles. A greater value produces greater detail at high
 zoom levels. The default value is 18.
 

 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionMaximumZoomLevel;

/**
 An `NSNumber` object containing an integer; specifies the size of the tile
 buffer on each side. A value of 0 produces no buffer. A value of 512 produces a
 buffer as wide as the tile itself. Larger values produce fewer rendering
 artifacts near tile edges and slower performance. The default value is 128.

 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionBuffer;

/**
 An `NSNumber` object containing a double; specifies the Douglas-Peucker
 simplification tolerance. A greater value produces simpler geometries and
 improves performance. The default value is 0.375.
 
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionSimplificationTolerance;

/**
 An `NSNumber` object containing a Boolean enabling or disabling calculating line distance metrics. 
 
 Set this property to `YES` in order for the `DingiLineStyleLayer.lineGradient` property to have its intended effect.
 The default value is `NO`.
 
 */
FOUNDATION_EXTERN MGL_EXPORT const DingiShapeSourceOption DingiShapeSourceOptionLineDistanceMetrics;

/**
 `DingiShapeSource` is a map content source that supplies vector shapes to be
 shown on the map. The shapes may be instances of `MGLShape` or `DingiFeature`,
 or they may be defined by local or external
 <a href="http://geojson.org/">GeoJSON</a> code. A shape source is added to an
 `DingiStyle` object along with an `DingiVectorStyleLayer` object. The vector style
 layer defines the appearance of any content supplied by the shape source. You
 can update a shape source by setting its `shape` or `URL` property.
 
 `DingiShapeSource` is optimized for data sets that change dynamically and fit
 completely in memory. For large data sets that do not fit completely in memory,
 use the `DingiComputedShapeSource` or `DingiVectorTileSource` class.

 Each
 geojson source defined by the style JSON file is represented at runtime by an
 `DingiShapeSource` object that you can use to refine the map’s content and
 initialize new style layers. You can also add and remove sources dynamically
 using methods such as `-[DingiStyle addSource:]` and
 `-[DingiStyle sourceWithIdentifier:]`.

 Any vector style layer initialized with a shape source should have a `nil`
 value in its `sourceLayerIdentifier` property.

 ### Example

 ```swift
 var coordinates: [CLLocationCoordinate2D] = [
     CLLocationCoordinate2D(latitude: 37.77, longitude: -122.42),
     CLLocationCoordinate2D(latitude: 38.91, longitude: -77.04),
 ]
 let polyline = DingiPolylineFeature(coordinates: &coordinates, count: UInt(coordinates.count))
 let source = DingiShapeSource(identifier: "lines", features: [polyline], options: nil)
 mapView.style?.addSource(source)
 ```
 */
MGL_EXPORT
@interface DingiShapeSource : DingiSource

#pragma mark Initializing a Source

/**
 Returns a shape source with an identifier, URL, and dictionary of options for
 the source.
 
 This class supports the following options: `DingiShapeSourceOptionClustered`,
 `DingiShapeSourceOptionClusterRadius`,
 `DingiShapeSourceOptionMaximumZoomLevelForClustering`,
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`, and
 `DingiShapeSourceOptionSimplificationTolerance`. Shapes provided by a shape
 source are not clipped or wrapped automatically.

 @param identifier A string that uniquely identifies the source.
 @param url An HTTP(S) URL, absolute file URL, or local file URL relative to the
    current application’s resource bundle.
 @param options An `NSDictionary` of options for this source.
 @return An initialized shape source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier URL:(NSURL *)url options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options NS_DESIGNATED_INITIALIZER;

/**
 Returns a shape source with an identifier, a shape, and dictionary of options
 for the source.
 
 This class supports the following options: `DingiShapeSourceOptionClustered`,
 `DingiShapeSourceOptionClusterRadius`,
 `DingiShapeSourceOptionMaximumZoomLevelForClustering`,
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`, and
 `DingiShapeSourceOptionSimplificationTolerance`. Shapes provided by a shape
 source are not clipped or wrapped automatically.

 To specify attributes about the shape, use an instance of an `DingiShape`
 subclass that conforms to the `DingiFeature` protocol, such as `DingiPointFeature`.
 To include multiple shapes in the source, use an `DingiShapeCollection` or
 `DingiShapeCollectionFeature` object, or use the
 `-initWithIdentifier:features:options:` or
 `-initWithIdentifier:shapes:options:` methods.

 To create a shape from GeoJSON source code, use the
 `+[DingiShape shapeWithData:encoding:error:]` method.

 @param identifier A string that uniquely identifies the source.
 @param shape A concrete subclass of `DingiShape`
 @param options An `NSDictionary` of options for this source.
 @return An initialized shape source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier shape:(nullable DingiShape *)shape options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options NS_DESIGNATED_INITIALIZER;

/**
 Returns a shape source with an identifier, an array of features, and a dictionary
 of options for the source.
 
 This class supports the following options: `DingiShapeSourceOptionClustered`,
 `DingiShapeSourceOptionClusterRadius`,
 `DingiShapeSourceOptionMaximumZoomLevelForClustering`,
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`, and
 `DingiShapeSourceOptionSimplificationTolerance`. Shapes provided by a shape
 source are not clipped or wrapped automatically.

 Unlike `-initWithIdentifier:shapes:options:`, this method accepts `DingiFeature`
 instances, such as `DingiPointFeature` objects, whose attributes you can use when
 applying a predicate to `DingiVectorStyleLayer` or configuring a style layer’s
 appearance.

 To create a shape from GeoJSON source code, use the
 `+[DingiShape shapeWithData:encoding:error:]` method.

 @param identifier A string that uniquely identifies the source.
 @param features An array of objects that conform to the DingiFeature protocol.
 @param options An `NSDictionary` of options for this source.
 @return An initialized shape source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier features:(NSArray<DingiShape<DingiFeature> *> *)features options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options;

/**
 Returns a shape source with an identifier, an array of shapes, and a dictionary of
 options for the source.
 
 This class supports the following options: `DingiShapeSourceOptionClustered`,
 `DingiShapeSourceOptionClusterRadius`,
 `DingiShapeSourceOptionMaximumZoomLevelForClustering`,
 `DingiShapeSourceOptionMinimumZoomLevel`, `DingiShapeSourceOptionMaximumZoomLevel`,
 `DingiShapeSourceOptionBuffer`, and
 `DingiShapeSourceOptionSimplificationTolerance`. Shapes provided by a shape
 source are not clipped or wrapped automatically.

 Any `DingiFeature` instance passed into this initializer is treated as an ordinary
 shape, causing any attributes to be inaccessible to an `DingiVectorStyleLayer` when
 evaluating a predicate or configuring certain layout or paint attributes. To
 preserve the attributes associated with each feature, use the
 `-initWithIdentifier:features:options:` method instead.

 To create a shape from GeoJSON source code, use the
 `+[DingiShape shapeWithData:encoding:error:]` method.

 @param identifier A string that uniquely identifies the source.
 @param shapes An array of shapes; each shape is a member of a concrete subclass of DingiShape.
 @param options An `NSDictionary` of options for this source.
 @return An initialized shape source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier shapes:(NSArray<DingiShape *> *)shapes options:(nullable NSDictionary<DingiShapeSourceOption, id> *)options;

#pragma mark Accessing a Source’s Content

/**
 The contents of the source. A shape can represent a GeoJSON geometry, a
 feature, or a collection of features.

 If the receiver was initialized using `-initWithIdentifier:URL:options:`, this
 property is set to `nil`. This property is unavailable until the receiver is
 passed into `-[DingiStyle addSource:]`.

 You can get/set the shapes within a collection via this property. Actions must
 be performed on the application's main thread.
 */
@property (nonatomic, copy, nullable) DingiShape *shape;

/**
 The URL to the GeoJSON document that specifies the contents of the source.

 If the receiver was initialized using `-initWithIdentifier:shape:options:`,
 this property is set to `nil`.
 */
@property (nonatomic, copy, nullable) NSURL *URL;

/**
 Returns an array of map features for this source, filtered by the given
 predicate.

 Each object in the returned array represents a feature for the current style
 and provides access to attributes specified via the `shape` property.

 Features come from tiled GeoJSON data that is converted to tiles internally,
 so feature geometries are clipped at tile boundaries and features
 may appear duplicated across tiles. For example, suppose this source contains a
 long polyline representing a road. The resulting array includes those parts of
 the road that lie within the map tiles that the source has loaded, even if the
 road extends into other tiles. The portion of the road within each map tile is
 included individually.
 
 Returned features may not necessarily be visible to the user at the time they
 are loaded: the style may lack a layer that draws the features in question. To
 obtain only _visible_ features, use the
 `-[DingiMapView visibleFeaturesAtPoint:inStyleLayersWithIdentifiers:predicate:]`
 or
 `-[DingiMapView visibleFeaturesInRect:inStyleLayersWithIdentifiers:predicate:]`
 method.

 @param predicate A predicate to filter the returned features. Use `nil` to
    include all features in the source.
 @return An array of objects conforming to the `DingiFeature` protocol that
    represent features in the source that match the predicate.
 */
- (NSArray<id <DingiFeature>> *)featuresMatchingPredicate:(nullable NSPredicate *)predicate;

@end

NS_ASSUME_NONNULL_END
