//
//  DingiReverseLandMarkViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 3/4/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import DingiMap
import SwiftyJSON

class DingiReverseLandMarkViewController: UIViewController, DingiMapViewDelegate {
    
    var mapView: DingiMapView!
    var json: JSON!

    override func viewDidLoad() {
        super.viewDidLoad()

        mapView = DingiMapView(frame: view.bounds)
        mapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView.setCenter(CLLocationCoordinate2D(latitude: 23.7925, longitude: 90.4078), zoomLevel: 12, animated: false)
        mapView.delegate = self
        view.addSubview(mapView)
        
        let singleTap = UITapGestureRecognizer(target: self, action: #selector(handleMapTap(sender:)))
        mapView.addGestureRecognizer(singleTap)
    }
    
    
    @objc func handleMapTap(sender: UITapGestureRecognizer) {
        let spot = sender.location(in: mapView)
        let coord = mapView.convert(spot, toCoordinateFrom: mapView)
        callReverseLandMark(coord: coord)
    }
    
    func mapView(_ mapView: DingiMapView, viewFor annotation: DingiAnnotation) -> DingiAnnotationView? {
        return nil
    }
    
    func mapView(_ mapView: DingiMapView, annotationCanShowCallout annotation: DingiAnnotation) -> Bool {
        return true
    }
    
    func callReverseLandMark(coord: CLLocationCoordinate2D){
        let url = URL(string: "https://api.dingi.live/maps/v2/reverselandmark/?lat=\(coord.latitude)&lng=\(coord.longitude)&language=en")
        var urlRequest = URLRequest(url: url!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                self.json = try JSON(data: data!)
                DispatchQueue.main.async {[weak self] in
                    
                    if self!.mapView.annotations != nil{
                        self!.mapView.removeAnnotations(self!.mapView.annotations!)
                    }
                    
                    let hello = DingiPointAnnotation()
                    hello.coordinate = coord
                    hello.title = ""
                    hello.subtitle = "\((self!.json["address"].stringValue.components(separatedBy: ",").prefix(2).joined(separator: ","))) Road: \(self!.json["way"]["name"].stringValue)\nPOI: \(self!.json["poi"]["name"].stringValue)(\(self!.json["poi"]["direction"].stringValue))"
                    self!.mapView.addAnnotation(hello)
                    self!.mapView.selectAnnotation(hello, animated: false)
                   
                    let way = self!.json["way"]["location"]["coordinates"].arrayValue
                    var coordinates: [CLLocationCoordinate2D] = []
                    var polyline = DingiPolyline()
                    for point in way
                    {
                        coordinates.append(CLLocationCoordinate2D(latitude: point.arrayValue[1].doubleValue, longitude: point.arrayValue[0].doubleValue))
                    }
                    polyline = DingiPolyline(coordinates: &coordinates, count: UInt(coordinates.count))
                    self!.mapView.addAnnotation(polyline)
                }
                
                
                
                
                
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            }.resume()
    }

}
