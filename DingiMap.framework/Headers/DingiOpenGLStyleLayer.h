#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <QuartzCore/QuartzCore.h>

#import "DingiFoundation.h"
#import "MGLStyleValue.h"
#import "DingiStyleLayer.h"
#import "DingiGeometry.h"

NS_ASSUME_NONNULL_BEGIN

@class DingiMapView;
@class DingiStyle;

typedef struct DingiStyleLayerDrawingContext {
    CGSize size;
    CLLocationCoordinate2D centerCoordinate;
    double zoomLevel;
    CLLocationDirection direction;
    CGFloat pitch;
    CGFloat fieldOfView;
    MGLMatrix4 projectionMatrix;
} DingiStyleLayerDrawingContext;

MGL_EXPORT
@interface DingiOpenGLStyleLayer : DingiStyleLayer

@property (nonatomic, weak, readonly) DingiStyle *style;

- (instancetype)initWithIdentifier:(NSString *)identifier;

- (void)didMoveToMapView:(DingiMapView *)mapView;

- (void)willMoveFromMapView:(DingiMapView *)mapView;

- (void)drawInMapView:(DingiMapView *)mapView withContext:(DingiStyleLayerDrawingContext)context;

- (void)setNeedsDisplay;

@end

NS_ASSUME_NONNULL_END
