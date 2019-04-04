//
//  SearchPlaceViewController.swift
//  GoogleMapSDK
//
//  Created by Nafis Islam on 10/3/19.
//  Copyright © 2019 Nafis Islam. All rights reserved.
//

import UIKit
import SwiftyJSON

class SearchPlaceViewController: UITableViewController, UISearchBarDelegate, UISearchResultsUpdating {
    func updateSearchResults(for searchController: UISearchController) {
        callSearchApi()
    }
    
    
    var searchController: UISearchController!
    var resultsController: UITableViewController!
    var delegate: SearchDelegate?
    var Result: JSON?

    override func viewDidLoad() {
        super.viewDidLoad()

        self.searchController = UISearchController(searchResultsController: self.resultsController)
        self.searchController.dimsBackgroundDuringPresentation = false
        self.tableView.tableHeaderView = self.searchController.searchBar
        self.searchController.searchBar.delegate = self
        self.searchController.searchResultsUpdater = self
        self.searchController.searchBar.placeholder = "search"
    }
    
    @IBAction func backPressed(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 80
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if self.Result != nil{
            return (self.Result!["result"].count)
        }
        return 0
    }
    
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "searchcell", for: indexPath)
       
        cell.textLabel?.text = Result!["result"][indexPath.row]["name"].stringValue
        cell.detailTextLabel?.text = Result!["result"][indexPath.row]["address"].stringValue
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        print("\(indexPath.row) selected")
   
        
        
        self.delegate?.returnFromSearchResult(result: self.Result!["result"][indexPath.row])
        self.dismiss(animated: false, completion: {
            self.dismiss(animated: false,completion:nil)
        })
    }
    
    func callSearchApi(){
        if (self.searchController.searchBar.text?.count)! < 3{
            return
        }
        let url = NSURLComponents(string: "https://api.dingi.live/maps/v2/search")
        var items = [URLQueryItem]()
        items.append(URLQueryItem(name: "language", value: "en"))
        items.append(URLQueryItem(name: "q", value: self.searchController.searchBar.text))
        url?.queryItems = items
        var urlRequest = URLRequest(url: (url?.url!)!)
        urlRequest.httpMethod = "GET"
        urlRequest.timeoutInterval = 20
        urlRequest.setValue("ru7KPUg2Wj17lRGdT1mTn9fCbYYSI2Ojaop8iwB5", forHTTPHeaderField: "x-api-key")
        self.searchController.searchBar.isLoading = true
        URLSession.shared.dataTask(with: urlRequest) { (data, response, err) in
            do{
                if data == nil{
                    return
                }
                self.Result = try JSON(data: data!)
                /* Sample Response
                 {
                 "result": [
                 {
                 "source": "poi",
                 "type": "finance,point_of_interest,establishment",
                 "name": "Shuru Telecom",
                 "address": "Shuru Telecom, Zafrabad, Mohammadpur Thana, Dhaka",
                 "id": "a16ea93f-4729-4752-9ac6-68049ed59e11",
                 "score": 101,
                 "location": [
                 23.751423,
                 90.36184
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "point_of_interest",
                 "name": "Shuru Campus",
                 "address": "Shuru Campus, Uttar Badda, Badda Thana, Dhaka",
                 "id": "3e8fe3e2-47e3-4aa0-bf4e-4a167e593975",
                 "score": 84.136,
                 "location": [
                 23.780872,
                 90.423005
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "restaurant,food,point_of_interest,establishment",
                 "name": "Shuruchi Restaurant",
                 "address": "Shuruchi Restaurant, Mohakhali, Gulshan Thana, Dhaka",
                 "id": "7a905386-6487-4de4-be55-cb22d7980751",
                 "score": 65.402,
                 "location": [
                 23.779925,
                 90.410125
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "grocery_or_supermarket",
                 "name": "Shurush Khan Bazar",
                 "address": "Shurush Khan Bazar, Middle Paikpara, Mirpur Thana, Dhaka",
                 "id": "d8b86c29-2c7a-4b4f-abe5-90402028dc5f",
                 "score": 63.739,
                 "location": [
                 23.790361,
                 90.359459
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "general_contractor",
                 "name": "Shuruchi Properties Limited",
                 "address": "Shuruchi Properties Limited, Banasree, Khilgaon Thana, Dhaka",
                 "id": "81fe7416-41a7-4230-9784-3ee87e454090",
                 "score": 61.114,
                 "location": [
                 23.762911,
                 90.42849
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "clothing_store,store,point_of_interest,establishment",
                 "name": "Shuruchi Poshak Ghor",
                 "address": "Shuruchi Poshak Ghor, Taltola, Khilgaon Thana, Dhaka",
                 "id": "99453b79-b592-42c2-9aea-9a97807e2dcf",
                 "score": 59.961,
                 "location": [
                 23.751593,
                 90.424499
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "point_of_interest,establishment",
                 "name": "Shuruchy Tailors",
                 "address": "Shuruchy Tailors, Sakta, Keraniganj Thana, Dhaka",
                 "id": "b85a6a40-59ba-4d7d-93f1-5e4e54225471",
                 "score": 59.814,
                 "location": [
                 23.730635,
                 90.334251
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "clothing_store,store,point_of_interest,establishment",
                 "name": "Shurupa Fashion",
                 "address": "Shurupa Fashion, Block C, Section 10, Mirpur, Pallabi Thana, Dhaka",
                 "id": "7153f352-a6f0-49d5-9a2d-57c396c9c92c",
                 "score": 58.421,
                 "location": [
                 23.808711,
                 90.373307
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "mosque",
                 "name": "Shurujbag Jame Mosjid",
                 "address": "Shurujbag Jame Mosjid, Karimbag, Sultanganj, Kamrangir Char Thana, Dhaka",
                 "id": "2710410f-04d0-49ef-82b1-240cd0b12d48",
                 "score": 56.695,
                 "location": [
                 23.711381,
                 90.383838
                 ]
                 },
                 {
                 "source": "poi",
                 "type": "car_repair",
                 "name": "Shuruvi motor's",
                 "address": "Shuruvi motor's, Kotwali, Kotwali Thana, Dhaka",
                 "id": "4d349510-2172-4ef0-888b-7b3adbe4b985",
                 "score": 56.112,
                 "location": [
                 23.706511,
                 90.412449
                 ]
                 }
                 ]
                 }
                */
                DispatchQueue.main.async {
                    self.tableView.reloadData()
                    self.searchController.searchBar.isLoading = false
                }
            } catch let jsonErr{
                print("Josn parse error: ", jsonErr)
            }
            }.resume()
    }
    
}


extension UISearchBar {
    
    public var textField: UITextField? {
        let subViews = subviews.flatMap { $0.subviews }
        guard let textField = (subViews.filter { $0 is UITextField }).first as? UITextField else {
            return nil
        }
        return textField
    }
    
    public var activityIndicator: UIActivityIndicatorView? {
        return textField?.leftView?.subviews.compactMap{ $0 as? UIActivityIndicatorView }.first
    }
    
    var isLoading: Bool {
        get {
            return activityIndicator != nil
        } set {
            if newValue {
                if activityIndicator == nil {
                    let newActivityIndicator = UIActivityIndicatorView(activityIndicatorStyle: .gray)
                    newActivityIndicator.transform = CGAffineTransform(scaleX: 1, y: 1)
                    newActivityIndicator.startAnimating()
                    newActivityIndicator.backgroundColor = UIColor.white
                    textField?.leftView?.addSubview(newActivityIndicator)
                    let leftViewSize = textField?.leftView?.frame.size ?? CGSize.zero
                    newActivityIndicator.center = CGPoint(x: leftViewSize.width/2, y: leftViewSize.height/2)
                }
            } else {
                activityIndicator?.removeFromSuperview()
            }
        }
    }
}

protocol SearchDelegate {
    func returnFromSearchResult(result: JSON)
//    func callDetails(index: Int)
//    func DirectionButtonPressed(lat: Double, lng: Double)
}
