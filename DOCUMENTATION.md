# Instruções utilizacao do proxy:

### Instancia passando a porta:	
```
int porta = 8228;
Proxy_Server proxy = Proxy_Server(porta);

```
ps: na main.cpp do projeto ja tem um codigo que instancia um proxy com a porta 8228 como padrao, ou muda dependendo do que for passado como parametro.


### Pegando requests vindos do navegador:
```
string req = proxy.get_client_request();
HTTP_Request request = HTTP_Request(req);
```

### Acessando os parametros da Request:
```
request.method = "GET";
request.url = "/exemplo/";
request.version = "HTTP/1.1";
request.fields["Host:"] = "www.host.com";
```


### Fazendo a request para o servidor de origem e obtendo a resposta:
```
string reply = proxy.make_request(request.Assembly_Request());
HTTP_Response response = HTTP_Response(reply);
``` 

### Acessando os parametros da Response:
```
response.status_code="200 OK";
response.version = "HTTP/1.1";
response.fields["Content-Type:"] ="text/html; charset=UTF-8" ; 
response.data = [algum html ou outro payload da resposta];
```


### Respondendo o navegador:
```
proxy.reply_client(response.Assembly_Response());
```


#Instrucoes de utilizacao do Spider

obs: tanto o spider em si (que gera a arvore) quanto o cliente recursivo (dump) utilizam a classe Spider.

### Instancia passando a url desejada e a porta:	
```
string url("www.ba.gov.br");
int porta = 8228;
Spider spider = Spider(url, porta);

```

Caso queira utilizar a url de uma request:
```
HTTP_Request request = HTTP_Request(req);
int porta = 8228;
Spider spider = Spider(request.url, porta);
```

### Gera arvore passando os numero de niveis:
```
spider.generate_tree(0);
```
Nesse caso, com o numero 0 ele so inspecionara a url passada (root). Caso passe o numero 1, inspecionara a url passada e todas as suas "filhas". E assim por diante.

### Acessando a arvore:

Duas estruturas sao utilizadas: 
- A string 'root' que indica qual o no raiz da arvore.
- O dicionario 'par_child' que relaciona urls a listas de urls "filhas";

```
string no_raiz = spider.root;
set<string> primeiro_nivel = spider.par_child[no_raiz];
```

Idealmente se deve iterar nesse set "primeiro_nivel", e ir verificando no spider.par_child. se aquela key nao existir no dicionario, indica que e um no folha.

Iterando em um set<string>:
```
for (set<string>::iterator it=nome_do_set.begin(); it!=nome_do_set.end(); ++it){
        cout << *it; // acessa o elemento assim
    }
```

Verificando a presenca de uma url no dicionario par_child:
```
if ( par_child.find(url) == par_child.end() ) {
  // nao encontrada
} else {
  // encontrada
}

```

### Fazendo o dump passando o numero de niveis:

```
string url("www.ba.gov.br");
int porta = 8228;
Spider spider = Spider(url, porta);
spider.dump_htmls(0);
```

Essa funcao ira fazer o dump (apenas dos htmls) da url passada e demais niveis dentro de uma pasta com o mesmo nome do host da url. 
A url passada (raiz) sempre sera salva como index.html.
Se passado o numero de niveis 0, apenas o index.html sera salvo, caso seja nivel 1, todas as paginas do primeiro sub-nivel tambem serao salvas, e assim por diante.



# O que falta fazer:

- Interface Grafica
- Verificacao de erros na classe Spider (so funciona se usada corretamente, com urls validas, etc..)
- Dump de imagens
- Funcao de printar arvore na linha de comando (caso necessario)
- Utilizacao de Threads (caso necessario)