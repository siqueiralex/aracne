# Aracne

Proxy HTTP com função de Cliente Recursivo e Spider. 
Implementado como Trabalho Final da disciplina Teleinformática e Redes 2, na Universidade de Brasília, durante o primeiro semestre de 2018. 

### Alunos: 
- Alex Siqueira Lacerda 16/0047692
- Jonatas Gomes Pinto Junior 14/0146407





## Classe Proxy_Server:
A classe Proxy_Server implementa toda a lógica de Sockets do servidor, para receber requisições e enviar respostas ao navegador e para realizar requisições HTTP à internet e receber resposta.


### Instancia e dando init para escutar na porta:	
```
int porta = 8228;
Proxy_Server proxy = Proxy_Server()
proxy.init(porta);
```

### Pegando requests vindos do navegador:
```
string req = proxy.get_client_request();
```

### Fazendo a request para o servidor de origem e obtendo a resposta:
```
string reply = proxy.make_request(req);
``` 

### Respondendo o navegador:
```
proxy.reply_client(response.Assembly_Response());
```





## Classe HTTP_Request
Classe que faz o parse da requisição HTTP e torna possível tratamentos e manipulações.

### Instanciando uma Request a partir de uma string:
```
HTTP_Request request = HTTP_Request(req);
```

### Acessando os parametros da Request:
```
request.method = "GET";
request.url = "/exemplo/";
request.version = "HTTP/1.1";
request.fields["Host:"] = "www.host.com";
```

### Monta a Request de volta para um string:
```
string req = request.assembly();
```





## Classe HTTP_Response
Classe que faz o parse da resposta HTTP e torna possível tratamentos e manipulações.

### Instanciando uma response a partir de uma string:
```
HTTP_Response response = HTTP_Response(resp);
```

### Acessando os parametros da response:
```
response.status_code="200 OK";
response.version = "HTTP/1.1";
response.fields["Content-Type:"] ="text/html; charset=UTF-8" ; 
response.data = [algum html ou outro payload da resposta];
```
### Monta a Response de volta para um string:
```
string res = response.assembly();
```






## Classe Spider	
Classe que se utiliza de todas as outras para realizar a função de cliente recursivo (dump de páginas subjacentes a uma url) e spider (construção de uma árvore hipertextual de links entre páginas a partir de uma url).


### Instancia passando a url desejada :	
```
string url("www.ba.gov.br");
Spider spider = Spider(url);
```

Caso queira utilizar a url de uma request:
```
HTTP_Request request = HTTP_Request(req);
Spider spider = Spider(request.url);
```

### Verifica se a url passada é valida:
```
if(spider.valid){
	// passou
}else{
	// não passou
}
```

### Gera arvore passando os numero de niveis:
```
spider.generate_tree(0);
```
ps: nível 0 só inspeciona a raiz.

### Imprime a árvore:
```
spider.print_tree();
```

### Faz o dump passando o numero de niveis:

Ele vai salvar todos os htmls numa pasta com o nome do host. A url raiz ficara com o nome index.html.

```
spider.dump_htmls(0);
```
ps: nível 0 só inspeciona a raiz.



## Dificuldades encontradas:

-Programação baixo nível em sockets torna o funcionamento do programa instável por existirem muitos detalhes a serem considerados. (Nem sempre funciona corretamente) 
-Complexidade de fazer o parse HTTP e HTML, funciona pra maioria dos casos, mais existem muitas situações em que se comporta mal.
-Não conseguimos criar a interface gráfica devido à grande quantidade de problemas encontrados na lógica do programa.
-Muitas funções blocantes que exigem conhecimento de Programação Concorrente para implementação de Threads (não foi feito).  