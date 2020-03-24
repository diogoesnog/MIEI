var MongoClient = require("mongodb").MongoClient;
var url = "mongodb://localhost:27017/SAKILA";

const fs = require("fs")

MongoClient.connect(url, function(err, db) {
  
  if (err) throw err;
  var dbo = db.db("SAKILA");
    
  console.log("Data Customers.\n");

  let dataCustomers = fs.readFileSync('files/customers.json');
  let dataJSONCustomers = JSON.parse(dataCustomers);

  dataJSONCustomers.forEach(element => {
    let idCustomer = (element.idCustomer);
    let FirstName = (element.FirstName);
    let LastName = (element.LastName);
    let Email = (element.Email);
    let Address = (element.Address);
    let City = (element.City);
    let District = (element.District);
    let Country = (element.Country);
    let PostalCode = (element.PostalCode);
    let Phone = (element.Phone);
    let LastUpdate = (element.LastUpdate);
    let idStaff = (element.idStaff);

    var dadosCustomers = { 
      "ID Customer": idCustomer, 
      "First Name": FirstName, 
      "Last Name": LastName, 
      "Email": Email,
      "Address": Address, 
      "City": City , 
      "District": District,  
      "Country": Country,
      "Postal Code": PostalCode, 
      "Phone": Phone, 
      "Last Update": LastUpdate, 
      "Rentals": [],
      "Payments": [], 
      "ID Staff": idStaff
    };

    dbo.collection("customers").insertOne(dadosCustomers, function(err, res) {
      if (err) throw err;
      console.log("Customer Inserido.");
      db.close();
    });

  })

  dataJSONCustomers.forEach(element => {
    let idCustomer = (element.idCustomer);
    
    let rentals = (element.Rentals);
    var rental = rentals.split(",");

    for(var i = 0; i < rental.length; i++) {

      let infosRental = rental[i].split("//");

      dbo.collection("customers").updateOne({"ID Customer": idCustomer}, {$push : {Rentals: {$each : [{
        "ID Rental": infosRental[0] , 
        "Rental Date": infosRental[1], 
        "Return Date": infosRental[2],
        "ID Film": infosRental[3], 
        "Film Title": infosRental[4]
      }]}}}, function(err, res) {
        if (err) throw err;
        console.log("Rental Inserido.");
        db.close();
      });

    }
    
    let payments = (element.Payments);
    var payment = payments.split(",");

    for(var i = 0; i < payment.length; i++) {

      let infosPayments = payment[i].split("//");

      dbo.collection("customers").updateOne({"ID Customer": idCustomer}, {$push : {Payments: {$each : [{
        "ID Rental": infosPayments[0] , 
        "ID Payment": infosPayments[1], 
        "Amount": infosPayments[2], 
        "Payment Date": infosPayments[3], 
      }]}}}, function(err, res) {
        if (err) throw err;
        console.log("Payment Inserido.");
        db.close();
      });

    }
  })

  console.log("Data Films.\n");

  let dataFilms = fs.readFileSync('files/films.json');
  let dataJSONFilms = JSON.parse(dataFilms);

  dataJSONFilms.forEach(element => {
    let idFilm = (element.film_id);
    let Title = (element.Title);
    let Description = (element.Description);
    let ReleaseYear = (element.ReleaseYear);
    let Language = (element.Language);
    let RentalDuration = (element.RentalDuration);
    let RentalRate = (element.RentalRate);
    let Rating = (element.Rating);
    let Length = (element.Length);
    let ReplacementCost = (element.ReplacementCost);
    let SpecialFeatures = (element.SpecialFeatures);
    let Category = (element.Category);

    var dadosFilms = { 
      "ID Film": idFilm, 
      "Title": Title,
      "Description": Description,
      "Release year": ReleaseYear,
      "Language": Language,
      "Rental Duration": RentalDuration,
      "Rental Rate": RentalRate,
      "Rating": Rating,
      "Length": Length,
      "Replacement Cost": ReplacementCost, 
      "Special Features": SpecialFeatures,
      "Category": Category,
      "Actors": []
    };

    dbo.collection("films").insertOne(dadosFilms, function(err, res) {
      if (err) throw err;
      console.log("Filme Inserido.");
      db.close();
    });
  })

  dataJSONFilms.forEach(element => {
    let idFilm = (element.film_id);
    
    let actors = (element.Actors);
    var actor = actors.split(",");

    for(var i = 0; i < actor.length; i++) {

      let infosActor = actor[i].split("//");

      dbo.collection("films").update({"ID Film" : idFilm}, {$push: {Actors: {$each: [{
        "ID Actor": infosActor[0],
        "First Name": infosActor[1],
        "Last Name": infosActor[2]
      }]}}}, function(err, res) {
        if (err) throw err;
        console.log("Actor Inserido.");
        db.close();
      });

    }
  })

  console.log("Dados Stores.\n");

  let dataStores = fs.readFileSync('files/stores.json');
  let dataJSONStores = JSON.parse(dataStores);
  
    let FirstName = (dataJSONStores[0].FirstName);
    let LastName = (dataJSONStores[0].LastName);
    let idManagerStaff = (dataJSONStores[0].idManagerStaff);
    let Address = (dataJSONStores[0].Address);
    let City = (dataJSONStores[0].City);
    let Country = (dataJSONStores[0].Country);
    let PostalCode = (dataJSONStores[0].PostalCode);
    let Phone = (dataJSONStores[0].Phone);

    var dadosStores = { 
        "Manager First Name": FirstName,
        "Manager Last Name": LastName,
        "ID Manager": idManagerStaff, 
        "Address": Address, 
        "City": City,  
        "Country": Country,
        "Phone": Phone, 
        "Inventory": []
    };
      dbo.collection("stores").insertOne(dadosStores, function(err, res) {
      if (err) throw err;
      console.log("Store Inserida.");
      db.close();
    });

    FirstName = (dataJSONStores[4].FirstName);
     LastName = (dataJSONStores[4].LastName);
     idManagerStaff = (dataJSONStores[4].idManagerStaff);
     Address = (dataJSONStores[4].Address);
     City = (dataJSONStores[4].City);
     Country = (dataJSONStores[4].Country);
     PostalCode = (dataJSONStores[4].PostalCode);
     Phone = (dataJSONStores[4].Phone);

    dadosStores = { 
        "Manager First Name": FirstName,
        "Manager Last Name": LastName,
        "ID Manager": idManagerStaff, 
        "Address": Address, 
        "City": City,  
        "Country": Country,
        "Phone": Phone, 
        "Inventory": []
    };
      dbo.collection("stores").insertOne(dadosStores, function(err, res) {
      if (err) throw err;
      console.log("Store Inserida.");
      db.close();
    });

  dataJSONStores.forEach(element => {
    let FirstName = (element.FirstName);
    let LastName = (element.LastName);
    let idFilm = (element.film_id);
    let Title = (element.title)
    let RentalRate = (element.rental_rate)

    dbo.collection("stores").updateOne({"Manager First Name": FirstName}, {$push: {Inventory: {$each: [{
        "ID Film": idFilm,
        "Title":  Title,
        "Rental Rate": RentalRate
    }]}}}, function(err, res) {
      if (err) throw err;
      console.log("Inventory Inserido.");
      db.close();
    });

    
  })

});