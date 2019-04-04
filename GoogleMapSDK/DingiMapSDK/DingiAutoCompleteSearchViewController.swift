//
//  AutoCompleteSearchViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 12/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import DingiMap
import SwiftyJSON
import DropDown

class DingiAutoCompleteSearchViewController: UIViewController, DingiMapViewDelegate, UITextFieldDelegate {
    
    @IBOutlet var crossButton: UIButton!
    var mapView: DingiMapView!
    @IBOutlet var searchbar: UITextField!
    var Result: JSON?
    let suggestion = DropDown()
    var SuggetionString = [String]()

    
    
    @IBAction func crossButtonPressed(_ sender: Any) {
        crossButton.isHidden = true
        searchbar.text = ""
        suggestion.hide()
        if self.mapView.annotations != nil{
            self.mapView.removeAnnotations(self.mapView.annotations!)
        }
        
    }
    
    
    @IBAction func textfieldvaluechanged(_ sender: Any) {
        
        print(searchbar.text!)
        crossButton.isHidden = false
        callSearchApi()
    }
    
    func callSearchApi(){
        if searchbar.text!.count < 3{
            return
        }
        let url = NSURLComponents(string: "https://api.dingi.live/maps/v2/search")
        var items = [URLQueryItem]()
        
        items.append(URLQueryItem(name: "language", value: "en"))
        items.append(URLQueryItem(name: "q", value: searchbar.text!))
        url?.queryItems = items
        var urlRequest = URLRequest(url: (url?.url!)!)
        urlRequest.httpMethod = "GET"
        urlRequest.timeoutInterval = 20
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                if data == nil{
                    return
                }
                self.Result = try JSON(data: data!)
                var i = 0
                self.SuggetionString = []
                for result in self.Result!["result"]{
                    print(result)
                    self.SuggetionString.append(
                        (result.1["address"].stringValue.components(separatedBy: ",").prefix(2).joined(separator: ",")))
                    i += 1
                    if i == 5{
                        break
                    }
                    
                }
                DispatchQueue.main.async {
                    self.suggestion.dataSource = self.SuggetionString
                    self.suggestion.show()
                    
                }
            } catch let jsonErr{
                print("Josn parse error: ", jsonErr)
            }
            }.resume()
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView = DingiMapView(frame: view.bounds)
        mapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView.setCenter(CLLocationCoordinate2D(latitude: 23.7925, longitude: 90.4078), zoomLevel: 12, animated: false)
        mapView.delegate = self
        view.addSubview(mapView)
        
        view.addSubview(searchbar)
        view.addSubview(crossButton)
        crossButton.isHidden = true
        searchbar.delegate = self
        suggestion.anchorView = searchbar
        suggestion.bottomOffset = CGPoint(x: 0, y:(suggestion.anchorView?.plainView.bounds.height)!)
        
        suggestion.selectionAction = { [unowned self] (index: Int, item: String) in
            print("Selected item: \(item) at index: \(index)")
            self.searchbar.text = item
            self.searchbar.endEditing(true)
            self.showPoiOnMap(item: index)
        }
        
        suggestion.cancelAction = { [unowned self] in
            print("Drop down dismissed")
            self.searchbar.text = ""
            self.crossButton.isHidden = true
            self.searchbar.endEditing(true)
            
        }
        
        
    }
    
    
    func showPoiOnMap(item: Int){
        DispatchQueue.main.async {
            if self.mapView.annotations != nil{
                self.mapView.removeAnnotations(self.mapView.annotations!)
            }
            let hello = DingiPointAnnotation()
            hello.coordinate = CLLocationCoordinate2D(latitude: (self.Result?["result"][item]["location"][0].doubleValue)!, longitude: self.Result!["result"][item]["location"][1].doubleValue)
            hello.title = self.Result?["result"][item]["name"].stringValue
            
            print("testing")
            print(hello.coordinate)
            self.mapView.addAnnotation(hello)
            self.mapView.selectAnnotation(hello, animated: false)
//            self.mapView.setCenter(CLLocationCoordinate2D(latitude: (self.Result?["result"][item]["location"][0].doubleValue)!, longitude: self.Result!["result"][item]["location"][1].doubleValue), animated: true)
            let camera = DingiMapCamera(lookingAtCenter: CLLocationCoordinate2D(latitude: (self.Result?["result"][item]["location"][0].doubleValue)!, longitude: self.Result!["result"][item]["location"][1].doubleValue), altitude: 4500, pitch: 15, heading: 0 )
            self.mapView.setCamera(camera, animated: true)
            
        }
    }
    
    func mapView(_ mapView: DingiMapView, viewFor annotation: DingiAnnotation) -> DingiAnnotationView? {
        return nil
    }
    
    func mapView(_ mapView: DingiMapView, annotationCanShowCallout annotation: DingiAnnotation) -> Bool {
        return true
    }
    
    
    
}
