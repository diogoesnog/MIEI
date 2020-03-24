var mysql = require("mysql");
var fs = require("fs");

const Json2csvParser = require("json2csv").Parser;

// Dados da Conexão em si.
var connection = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "root",
  database: "sakila"
});

// Query para retirar a informação dos Atores.
const queryActors = `
  SELECT 
    actor_id AS idActor, 
    first_name AS FirstName, 
    last_name AS LastName, 
    last_update AS LastUpdate 
  FROM  actor
`;

// Query para retirar a informação das Moradas.
const queryAddress = `
  SELECT 
    address_id AS idAddress, 
    address AS Address, 
    address2 AS Adress2,
    district AS District,
    postal_code AS PostalCode,
    phone AS Phone,
    city AS City,
    country AS Country
  FROM  address

	INNER JOIN city ON address.city_id = city.city_id
  INNER JOIN country ON country.country_id = city.country_id
`;

// Query para retirar a Informações dos Clientes.
const queryCustomers = `   
  SELECT  
    customer.customer_id AS idCustomer, 
    customer.store_id AS idStore,
    customer.first_name AS FirstName, 
    customer.last_name As LastName,
    customer.email AS Email, 
    customer.address_id AS idAddress,
    active AS Active,
    customer.last_update AS LastUpdate
  FROM customer
`;

// Query para retirar a informação dos Filmes.
const queryFilms = `
  SELECT 
    film.film_id AS idFilm, 
    title AS Title, 
    description AS Description, 
    release_year AS ReleaseYear, 
    rental_duration AS RentalDuration, 
    rental_rate AS RentalRate, 
    rating AS Rating,
    length AS Length, 
    replacement_cost AS ReplacementCost, 
    special_features AS SpecialFeatures,
    film.last_update AS LastUpdate,
    language.name AS Language,
    category.name AS Category
  FROM film
  
  INNER JOIN language ON film.language_id = language.language_id
  INNER JOIN film_category ON film.film_id = film_category.film_id
  INNER JOIN category ON film_category.category_id = category.category_id
  
  GROUP BY film.film_id
`;

// Query para retirar a informação da Relação dos Filmes e Atores.
const queryFilmsActors = `
  SELECT 
    actor_id AS idActor,
    film_id AS idFilm,
    last_update AS LastUpdate
  FROM  film_actor
`;

// Query para retirar a informação do Inventário.
const queryInventory = `
  SELECT 
    inventory_id AS idInventory,
    film_id AS idFilm,
    store_id AS idStore,
    last_update AS LastUpdate 
  FROM  inventory
`;

// Query para retirar a informação dos Pagamentos.
const queryPayments = `
  SELECT 
    payment_id AS idPayment,
    customer_id AS idCustomer,
    staff_id AS idStaff,
    rental_id AS idRental,
    amount AS Amount,
    payment_date AS PaymentDate,
    last_update AS LastUpdate
  FROM  payment
`;

// Query para retirar a informação dos Rentals.
const queryRentals = `
  SELECT 
    rental_id AS idRental,
    rental_date AS RentalDate,
    inventory_id AS idInventory,
    customer_id AS idCustomer,
    return_date AS ReturnDate,
    staff_id AS idStaff,
    last_update AS LastUpdate
  FROM  rental
`;

// Query para retirar a informação do Staff.
const queryStaff = `
  SELECT 
    staff_id AS idStaff,
    store.store_id AS idStore,
    staff.first_name AS FirstName, 
    staff.last_name AS LastName, 
    email AS Email,
    active AS Active, 
    address.address_id AS idAddress,
    store.last_update AS LastUpdate
  FROM  store

  INNER JOIN staff on store.manager_staff_id = staff.staff_id
  INNER JOIN address on staff.address_id = address.address_id
`;

// Query para retirar a informação das Lojas.
const queryStores = `
  SELECT 
    store.store_id AS idStore,
    manager_staff_id AS idManagerStaff, 
    store.address_id AS idAddress,
    store.last_update AS LastUpdate
  FROM  store

  INNER JOIN staff on store.manager_staff_id = staff.staff_id

  GROUP BY store.store_id
`;

// Conexão e escrita dos dados no ficheiro CSV.
connection.connect(function(error) {
  
  if (error) throw error;

  connection.query(queryActors, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/actors.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV das Actors salvo.");
    });
  });

  connection.query(queryAddress, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/addresses.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Address salvo.");
    });
  });

  connection.query(queryCustomers, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/customers.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Clientes salvo.");
    });
  });

  connection.query(queryFilms, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/films.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Filmes salvo.");
    });
  });

  connection.query(queryFilmsActors, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/filmsActors.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Filmes/Atores salvo.");
    });
  });

  connection.query(queryInventory, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/inventory.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV do Inventário salvo.");
    });
  });

  connection.query(queryPayments, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/payments.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Pagamentos salvo.");
    });
  });

  connection.query(queryRentals, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/rentals.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV dos Rentals salvo.");
    });
  });

  connection.query(queryStaff, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/staff.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV do Staff salvo.");
    });
  });

  connection.query(queryStores, function (error, data) {
    
    if (error) throw error;

    const jsonData = JSON.parse(JSON.stringify(data));
    const json2csvParser = new Json2csvParser({header: true});

    const csv = json2csvParser.parse(jsonData);
    
    fs.writeFile("files/stores.csv", csv, function(error) {
      if (error) throw error;
      console.log("Ficheiro CSV das Stores salvo.");
    });
  });

  connection.end();
});