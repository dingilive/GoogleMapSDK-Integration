#import <Foundation/Foundation.h>

#import "DingiFoundation.h"
#import "DingiShape.h"

#import "DingiTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An `DingiShapeCollection` object represents a shape consisting of zero or more
 distinct but related shapes that are instances of `DingiShape`. The constituent
 shapes can be a mixture of different kinds of shapes.

 `DingiShapeCollection` is most commonly used to add multiple shapes to a single
 `DingiShapeSource`. Configure the appearance of an `DingiShapeSource`’s or
 `DingiVectorTileSource`’s shape collection collectively using an
 `DingiSymbolStyleLayer` object, or use multiple instances of
 `DingiCircleStyleLayer`, `DingiFillStyleLayer`, and `DingiLineStyleLayer` to
 configure the appearance of each kind of shape inside the collection.

 You cannot add an `DingiShapeCollection` object directly to a map view as an
 annotation. However, you can create individual `DingiPointAnnotation`,
 `DingiPolyline`, and `DingiPolygon` objects from the `shapes` array and add those
 annotation objects to the map view using the `-[DingiMapView addAnnotations:]`
 method.

 To represent a collection of point, polyline, or polygon shapes, it may be more
 convenient to use an `DingiPointCollection`, `DingiMultiPolyline`, or
 `DingiMultiPolygon` object, respectively. To access a shape collection’s
 attributes, use the corresponding `DingiFeature` object.

 A shape collection is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.1.8">GeometryCollection</a>
 geometry in GeoJSON.
 */
MGL_EXPORT
@interface DingiShapeCollection : DingiShape

/**
 An array of shapes forming the shape collection.
 */
@property (nonatomic, copy, readonly) NSArray<DingiShape *> *shapes;

/**
 Creates and returns a shape collection consisting of the given shapes.

 @param shapes The array of shapes defining the shape collection. The data in
    this array is copied to the new object.
 @return A new shape collection object.
 */
+ (instancetype)shapeCollectionWithShapes:(NSArray<DingiShape *> *)shapes;

@end

NS_ASSUME_NONNULL_END
