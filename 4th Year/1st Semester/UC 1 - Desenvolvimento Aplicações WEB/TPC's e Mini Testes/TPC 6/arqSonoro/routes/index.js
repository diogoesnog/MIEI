const express = require("express")
const jsonFile = require("jsonfile")
var router = express.Router()

var baseDados = "arqSonoro.json"

/* GET da Home Page. */
router.get(["/", "/arqSonoro"], function(req, res, next) {

    jsonFile.readFile(baseDados, (erro, musicas) => {
      if(erro) res.render("paginaErro", {erro: "Não foi possível obter a Home Page."});  
      else res.render("indice", {listaMusicas: musicas});
    });
});

/* Página para adicionar uma nova música ao Arquivo Sonoro. */
router.get("/adicionarMusica", function(req, res, next) {
    res.render("adicionarMusica");
});

/* GET de uma música específica que é processada numa página WEB dedicada. */
router.get("/ver/:tituloMusica", function(req, res, next) {
   
    var titulo = req.params.tituloMusica;
    console.log("Música " + titulo + " requerida.");

    jsonFile.readFile(baseDados, (erro, musicas) => {
      if(!erro){
        var indice = musicas.findIndex(musica => musica.tit == titulo);

        if(indice > -1){
          var musica = musicas[indice];
          console.log("Música " + titulo + " encontrada!!!")
          console.log(musica);
          res.render('consultarMusica', {musica: musica});
        }
        else {
            console.log("Música " + titulo +  " não existe.");
            res.end("1");
        }
      }
    });
});

/* GET para modificar um registo já existente. Este update é processado numa página WEB dedicada. */
router.get("/editar/:tituloMusica", function(req, res, next) {

    var titulo = req.params.tituloMusica;
    console.log("Alteração para a música " + titulo + " requerida.");
    
    jsonFile.readFile(baseDados, (erro, musicas) => {
      if(!erro){
        var indice = musicas.findIndex(musica => musica.tit == titulo);

        if(indice > -1){
          var musica = musicas[indice];
          console.log("Música " + titulo + " encontrada!!!")
          console.log(musica);
          res.render("editarMusica", {musica: musica});
        }
        else {
          console.log("Música " + titulo +  " não existe.");
          res.end("1");
        }
      }
    });
});

/* DELETE de um registo no Arquivo Sonoro. */
router.delete("/:tituloMusica", function(req, res, next) {

    var titulo = req.params.tituloMusica;
    console.log("Remoção para a música " + titulo + " requerida.");

    jsonFile.readFile(baseDados, (erro,musicas) => {
        if(!erro){
          var indice = musicas.findIndex(musica => musica.tit == titulo);

          if(indice > -1){
              musicas.splice(indice, 1);
              jsonFile.writeFile(baseDados, musicas, erro => {
                  if(erro) console.log("Não foi possível atualizar a Base de Dados JSON.");
                  else console.log("Base de Dados JSON atualizada com sucesso.");
              })
              res.redirect(303,"/");
          }
          else {
            console.log("Música " + titulo +  " não existe.");
            res.end("1");
          }
      }
    });
});

/* POST que trata do envio de dados para a Base de Dados JSON. */
/* Usado quando se cria um novo registo. */
router.post("/", function(req,res, next) {
  
  jsonFile.readFile(baseDados, (erro, musicas) => {
    if(!erro){
      musicas.push(req.body);
      jsonFile.writeFile(baseDados, musicas, erro =>{
        if(erro) console.log("Não foi possível adicionar a música.");
        else console.log("Nova música adicionada com sucesso.");
      });
    }
  });
  res.redirect("/");
});

/* PUT que trata de adicionar o registo em si à Base de Dados JSON. */
/* Usado quando se atualiza um dado registo. */
router.put("/", function(req, res, next) {
 
  var provincia = req.body.uprov;
  var local = req.body.ulocal;
  var titulo = req.body.utit;
  var instrumento = req.body.uinst;
  var fileT = req.body.ufilett;
  var fileText = req.body.ufiletext;
  var duracao = req.body.uduracao;

  jsonFile.readFile(baseDados, (erro, musicas) => {
    if(!erro){
      var indice = musicas.findIndex(musica => musica.tit == titulo);
      
      if(indice > -1){
          musicas.splice(indice, 1);

          var toJson = {
            "prov": provincia,
            "local": local,
            "tit": titulo,
            "inst": instrumento,
            "file":{"@t": fileT, "#text": fileText},
            "duracao": duracao
          };

          musicas.push(toJson);

          jsonFile.writeFile(baseDados, musicas, erro => {
            if(erro) console.log("Não foi possível atualizar a Base de Dados JSON.");
            else console.log("Base de Dados JSON atualizada com sucesso.");
          });
          res.redirect(303,"/");
      }
      else {
        console.log("Música " + titulo +  " não existe.");
        res.end("1");
      }
    }
  });
});

module.exports = router;