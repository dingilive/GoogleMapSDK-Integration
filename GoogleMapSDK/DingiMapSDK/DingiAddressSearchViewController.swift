//
//  AddressSearchViewController.swift
//  maps-ios
//
//  Created by Nafis Islam on 4/10/18.
//  Copyright © 2018 Nafis Islam. All rights reserved.
//

import UIKit
import GoogleMaps
import Toaster
import DingiMap
class DingiAddressSearchViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate, DingiMapViewDelegate {
    
    @IBOutlet var mapView: DingiMapView!
    
    @IBOutlet var gobackview: UIView!
    @IBOutlet var HouseText: UITextField!
    @IBOutlet var RoadText: UITextField!
    @IBOutlet var AreaText: UITextField!
    @IBOutlet var HouseLabel: UILabel!
    @IBOutlet var RoadLabel: UILabel!
    @IBOutlet var AreaLabel: UILabel!
    
    @IBOutlet var tableView: UITableView!
    @IBOutlet var SearchButton: UIButton!
    
    @IBOutlet var visualView: UIVisualEffectView!
    public struct AddrSearch: Codable{
        var name: String
        var address: String
        var id: String
        var location: Array<Double>
    }
    public struct AddrSearchResult: Codable{
        var result: [AddrSearch]
    }
    
    
    @IBAction func GoBackButtonPressed(_ sender: Any) {
        print("go back pressed")
        self.tableView.isHidden = false
        self.visualView.isHidden = false
        self.gobackview.isHidden = true
    }
    
    public struct RoadSearch: Codable{
        var name: String
        var id: String
        var address: String
    }
    weak var delegate: AddrSearchDelegate?
    var Result = Array<AddrSearch>()
    
    var activityIndicator: UIActivityIndicatorView?
    let AreaDropDown = VPAutoComplete()
    let RoadDropDown = VPAutoComplete()
    var AreaNameSuggetion = [String]()
    var RoadNameSuggetion = [String]()
    var AreaSuggetionResult: [AreaSuggest]!
    var RoadSuggetionResult: [RoadSearch]!
    var selectedRegionId = ""
    var navMode = false
    
    @IBOutlet var backView: UIView!
    
    struct location: Codable {
        var lat: Double
        var lon: Double
        init(lat:Double, lon:Double){
            self.lat = lat
            self.lon = lon
        }
    }
    
    public struct AreaSuggest: Codable{
        var name: String
        var id: String
        var address: String
        var rep_point: location
    }
    
    public struct AreaSuggestResult: Codable{
        var search_result: [AreaSuggest]
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    
    @IBAction func AreaNameChanged(_ sender: UITextField) {
        print(sender.text!)
        let url = NSURLComponents(string: "https://ios.api.dingi.live/maps/v2/search/region/")
        var items = [URLQueryItem]()
        items.append(URLQueryItem(name: "query_string", value: sender.text!))
        items.append(URLQueryItem(name: "language", value: "en"))
        url?.queryItems = items
        var urlRequest = URLRequest(url: (url?.url!)!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                if data == nil{
                    return
                }
                self.AreaSuggetionResult = try
                    JSONDecoder().decode(AreaSuggestResult.self, from: data!).search_result
                self.AreaNameSuggetion = []
                var i = 0
                for result in self.AreaSuggetionResult{
                    
                    self.AreaNameSuggetion.append((result.address.components(separatedBy: ",").prefix(2).joined(separator: ",")))
                    i += 1
                    if i == 5{
                        break
                    }
                    
                }
                DispatchQueue.main.async {
                    self.AreaDropDown.reload(array: self.AreaNameSuggetion)
                }
                
            } catch let jsonErr{
                print("Josn parse error: ", jsonErr)
            }
            }.resume()
    }
    
    @IBAction func RoadNameChanged(_ sender: UITextField) {
        
        let url = NSURLComponents(string: "https://ios.api.dingi.live/maps/v2/search/way/regionbounded/")
        var items = [URLQueryItem]()
        items.append(URLQueryItem(name: "q", value: sender.text!))
        items.append(URLQueryItem(name: "region_id", value: selectedRegionId))
        items.append(URLQueryItem(name: "language", value: "en"))
        url?.queryItems = items
        var urlRequest = URLRequest(url: (url?.url!)!)
        urlRequest.httpMethod = "GET"
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                if data == nil{
                    return
                }
                self.RoadSuggetionResult = try
                    JSONDecoder().decode([RoadSearch].self, from: data!)
                print(self.RoadSuggetionResult)
                self.RoadNameSuggetion = []
                var i = 0
                for result in self.RoadSuggetionResult{
                    self.RoadNameSuggetion.append((result.address.components(separatedBy: ",").prefix(2).joined(separator: ",")))
                    i += 1
                    //                    if i == 5{
                    //                        break
                    //                    }
                    
                }
                while self.RoadNameSuggetion.count < 3 && self.RoadNameSuggetion.count >= 1{
                    self.RoadNameSuggetion.append("")
                }
                DispatchQueue.main.async {
                    self.RoadDropDown.reload(array: self.RoadNameSuggetion)
                }
                
            } catch let jsonErr{
                print("Josn parse error: ", jsonErr)
            }
            }.resume()
        
    }
    func showLoading(){
        DispatchQueue.main.async {
            let attrsB = [NSAttributedString.Key.foregroundColor : self.hexStringToUIColor(hex: "#404041")]
            let b = NSMutableAttributedString(string: "Please Wait", attributes:attrsB)
            let alert = UIAlertController(title: nil, message: nil, preferredStyle: .alert)
            alert.setValue(b, forKey: "attributedMessage")
            let loadingIndicator = UIActivityIndicatorView(frame: CGRect(x: 5, y: 5, width: 50, height: 50))
            loadingIndicator.hidesWhenStopped = true
            loadingIndicator.activityIndicatorViewStyle = UIActivityIndicatorView.Style.gray
            loadingIndicator.startAnimating();
            alert.view.addSubview(loadingIndicator)
            self.present(alert, animated: true, completion: nil)
        }
    }
    
    @IBAction func SearchButtonPressed(_ sender: Any) {
        print("search button pressed")
        if selectedRegionId.count < 1 {
            self.view.endEditing(true)
            Toast(text: "Please Select an Area First", duration: Delay.short).show()
            return
        }
        
        print(self.HouseText.text!)
        self.view.endEditing(true)
        print(self.RoadText.text!)
        showLoading()
        let url = NSURLComponents(string: "https://ios.api.dingi.live/maps/v2/search/address/guided/")
        var items = [URLQueryItem]()
        items.append(URLQueryItem(name: "house_number", value: self.HouseText.text!))
        items.append(URLQueryItem(name: "street_name", value: self.RoadText.text!))
        items.append(URLQueryItem(name: "region_id", value: selectedRegionId))
        items.append(URLQueryItem(name: "language", value: "en"))
        url?.queryItems = items
        
        var request = URLRequest(url: (url?.url!)!)
        request.httpMethod = "GET"
        request.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        
        let session = URLSession.shared
        session.dataTask(with: request) { (data, response, error) in
            do{
                if data == nil{
                    return
                }
                
                self.Result = try
                    JSONDecoder().decode(AddrSearchResult.self, from: data!).result
                
                DispatchQueue.main.async {
                    self.dismiss(animated: false, completion: nil)
                    if self.Result.count < 1 {
                        Toast(text: "No Address Found", duration: Delay.short).show()
                    }
                    self.tableView.isHidden = false
                    self.tableView.reloadData()
                    
                }
                
                
                
            } catch let jsonErr{
                print("Json parse error: ", jsonErr)
            }
            
            }.resume()
        
    }
    
    
    func initialLoadView(object: UITextField){
        object.layer.shadowColor = hexStringToUIColor(hex: "#404041").cgColor
        object.layer.shadowOffset = CGSize(width: 0, height: 1)
        object.layer.shadowOpacity = 1.0
        object.layer.shadowRadius = 0.0
    }
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.setNeedsStatusBarAppearanceUpdate()
        
        AreaText.delegate = self
        RoadText.delegate = self
        HouseText.delegate = self
        initialLoadView(object: AreaText)
        initialLoadView(object: RoadText)
        initialLoadView(object: HouseText)
        //        tableView.isHidden = true
        gobackview.isHidden = true
        mapView.setCenter(CLLocationCoordinate2D(latitude: 23.7925, longitude: 90.4078), zoomLevel: 12, animated: false)
        mapView.delegate = self
        mapView.showsUserLocation = true
        
        let appearance = ToastView.appearance()
        appearance.cornerRadius = 6
        
        AddSuggestions()
        
        
    }
    
    
    func AddSuggestions(){
        AreaDropDown.dataSource = self.AreaNameSuggetion
        AreaDropDown.onTextField = self.AreaText
        AreaDropDown.onView = self.backView
        AreaDropDown.isOnTop = true
        AreaDropDown.show { (str, index) in
            print("string : \(str) and Index : \(index)")
            self.selectedRegionId = self.AreaSuggetionResult[index].id
            self.AreaText.text = str
            
        }
        
        RoadDropDown.onTextField = self.RoadText
        RoadDropDown.onView = self.backView
        RoadDropDown.isOnTop = true
        // RoadDropDown.cellHeight = 45.0
        RoadDropDown.show { (str, index) in
            print("string : \(str) and Index : \(index)")
            self.RoadText.text = str
            
        }
    }
    
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return Result.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "addresscell", for: indexPath)
        cell.textLabel?.text = Result[indexPath.row].name
        cell.detailTextLabel?.text = Result[indexPath.row].address
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        self.tableView.deselectRow(at: indexPath, animated: false)
        DispatchQueue.main.async {
            self.tableView.isHidden = true
            self.visualView.isHidden = true
            self.gobackview.isHidden = false
            if self.mapView.annotations != nil{
                self.mapView.removeAnnotations(self.mapView.annotations!)
            }

            
            let hello = DingiPointAnnotation()
            hello.coordinate = CLLocationCoordinate2D(latitude: self.Result[indexPath.row].location[0], longitude: self.Result[indexPath.row].location[1])
            hello.title = self.Result[indexPath.row].name
            self.mapView.addAnnotation(hello)
            self.mapView.selectAnnotation(hello, animated: false)
            self.mapView.setCenter(hello.coordinate, zoomLevel: 18, animated: true)
        }
        
        
        
    }
    
    func textFieldDidBeginEditing(_ textfield: UITextField) {
        if textfield == self.RoadText || textfield == self.HouseText{
            if selectedRegionId.count < 1{
                print("no area selected")
                Toast(text: "Please Select an Area First", duration: Delay.short).show()
                textfield.endEditing(true)
                return
            }
        }
        textfield.layer.shadowColor = hexStringToUIColor(hex: "#1EBDCC").cgColor
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        textField.layer.shadowColor = hexStringToUIColor(hex: "#404041").cgColor
        
    }
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
    
    func hexStringToUIColor (hex:String) -> UIColor {
        var cString:String = hex.trimmingCharacters(in: .whitespacesAndNewlines).uppercased()
        
        if (cString.hasPrefix("#")) {
            cString.remove(at: cString.startIndex)
        }
        
        if ((cString.count) != 6) {
            return UIColor.gray
        }
        
        var rgbValue:UInt32 = 0
        Scanner(string: cString).scanHexInt32(&rgbValue)
        return UIColor(
            red: CGFloat((rgbValue & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((rgbValue & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(rgbValue & 0x0000FF) / 255.0,
            alpha: CGFloat(1.0)
        )
    }
    
    func mapView(_ mapView: DingiMapView, viewFor annotation: DingiAnnotation) -> DingiAnnotationView? {
        return nil
    }
    
    func mapView(_ mapView: DingiMapView, annotationCanShowCallout annotation: DingiAnnotation) -> Bool {
        return true
    }
    
}

