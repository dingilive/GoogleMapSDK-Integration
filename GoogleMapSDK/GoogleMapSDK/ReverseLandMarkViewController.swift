//
//  ReverseLandMarkViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 10/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import GoogleMaps
import SwiftyJSON


class ReverseLandMarkViewController: UIViewController, GMSMapViewDelegate {
    
    var mapView: GMSMapView!
    var json: JSON!
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let camera = GMSCameraPosition.camera(withLatitude: 23.7925, longitude: 90.4078, zoom: 14.0)
        mapView = GMSMapView.map(withFrame: CGRect.zero, camera: camera)
        mapView!.delegate = self
        self.view = mapView

    }
    
    func mapView(_ mapView: GMSMapView, didTapAt coordinate: CLLocationCoordinate2D) {
        print("You tapped at \(coordinate.latitude), \(coordinate.longitude)")
        callReverseLandMark(coord: coordinate)
    }
    
    
    func callReverseLandMark(coord: CLLocationCoordinate2D){
        let url = URL(string: "https://api.dingi.live/maps/v2/reverselandmark/?lat=\(coord.latitude)&lng=\(coord.longitude)&language=en")
        var urlRequest = URLRequest(url: url!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                self.json = try JSON(data: data!)
                
                print(self.json)
                
                /* Sample Response
                 {
                 "poi": {
                 "type": "park",
                 "direction": "South West",
                 "distance": 25,
                 "location": {
                 "lon": 90.4145789,
                 "lat": 23.7980508
                 },
                 "name": "Gulshan Health Club"
                 },
                 "way": {
                 "type": "secondary",
                 "distance": 133,
                 "location": {
                 "coordinates": [
                 [
                 90.4124128,
                 23.7995379
                 ],
                 [
                 90.4125199,
                 23.7992668
                 ],
                 [
                 90.41276,
                 23.7986515
                 ],
                 [
                 90.41316,
                 23.7975153
                 ],
                 [
                 90.4134332,
                 23.7967665
                 ],
                 [
                 90.4137011,
                 23.7960354
                 ],
                 [
                 90.4138538,
                 23.795566
                 ],
                 [
                 90.4139606,
                 23.7953119
                 ],
                 [
                 90.4140386,
                 23.7951524
                 ],
                 [
                 90.4140826,
                 23.7950868
                 ],
                 [
                 90.4142426,
                 23.7949076
                 ]
                 ],
                 "type": "LineString"
                 },
                 "name": "Gulshan Avenue"
                 },
                 "address": "Gulshan 2, Gulshan Thana, Dhaka"
                 }
                */
                DispatchQueue.main.async {[weak self] in
                    self!.mapView!.clear()
                    let marker = GMSMarker(position: coord)
                    marker.snippet = "\((self!.json["address"].stringValue.components(separatedBy: ",").prefix(2).joined(separator: ",")))\nRoad: \(self!.json["way"]["name"].stringValue)\nPOI: \(self!.json["poi"]["name"].stringValue)(\(self!.json["poi"]["direction"].stringValue))"
                    marker.map = self!.mapView
                    self!.mapView!.selectedMarker = marker
                    let way = self!.json["way"]["location"]["coordinates"].arrayValue
                    let path = GMSMutablePath()
                    for point in way
                    {
                       path.add(CLLocationCoordinate2D(latitude: point.arrayValue[1].doubleValue, longitude: point.arrayValue[0].doubleValue))
                    }
                    let polyline = GMSPolyline(path: path)
                    polyline.strokeColor = .blue
                    polyline.strokeWidth = 3
                    polyline.map = self!.mapView
                }
                

                
                
                
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            }.resume()
    }
    
    

}
