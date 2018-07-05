#include "../include/HTML_Parser.hpp"
#include "../include/Spider.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

Spider::Spider(string url, int port){
	proxy_port = port;
	string internal = url;
	vector<string> result = String_Functions::split(internal, "//");
	if(result.size()==2){
		if(result[0]!="http:"){
		 cout << "ERROR! INVALID URL IN SPIDER CALL: "<< url <<endl;
		 return;
		}
		internal = result[1];
	}
	if(result.size()>2){
	 	cout << "ERROR! INVALID URL IN SPIDER CALL: "<< url <<endl;
	 	return;
	}
	
	if(internal.find('/')!=0 && internal.find('/')<internal.length()){
		vector<string> result2 = String_Functions::split_on_first(internal, "/");
		if(host.length()==0){
			host = result2[0];	
		}else{
			cout << "ERROR! INVALID URL IN SPIDER CALL: "<< url <<endl;
			return;
		}
		root = "/";
		root.append(result2[1]);
	}else if(internal.find('/')>internal.length()){
		root = "/";
		host = internal;
	}else{
		cout << "ERROR! INVALID URL IN SPIDER CALL: "<< url <<endl;
	}

};

bool Spider::eval_url(string url){

	string internal = url;
	vector<string> result = String_Functions::split(internal, "//");
	if(result.size()==2){
		if(result[0]!="http:") return false;
		internal = result[1];
	}
	if(result.size()>2) return false;
	
	
	if(internal.find('/')!=0){
		vector<string> result2 = String_Functions::split(internal, "/");
		if(host.length()==0){
			return false;	
		}else{
			if(host!=result2[0]) return false;
		}
	}

	return true;
}

string Spider::parse_url(string url){
	string parsed("");
	string internal = url;
	vector<string> result = String_Functions::split(internal, "//");
	if(result.size()==2)		
		internal = result[1];
		
	
	if(internal.find('/')!=0){
		vector<string> result2 = String_Functions::split_on_first(internal, "/");
		parsed = "/";
		parsed.append(result2[1]);
	}else{
		parsed = url;
	}		
	if(parsed!=url) aliases[parsed]=url;
	
	return parsed;
}

void Spider::generate_tree(int levels){
	int i = levels;
	
	visited_urls.clear();
	par_child.clear();
	htmls.clear();

	if( host.length()==0 || root.length()==0){
		return;
	}

	Proxy_Server proxy = Proxy_Server();
	//int port = rand()%30000 + 30000;
	proxy.init(proxy_port);
	HTTP_Request request = HTTP_Request();
	set<string> to_request;
	to_request.insert(root);

	do{
		set<string> to_request_next;
		for (std::set<string>::iterator url=to_request.begin(); url!=to_request.end(); ++url){
			if(visited_urls.find(*url)==visited_urls.end()){
				visited_urls.insert(*url);
				request.url = *url;
				request.fields["Host:"] = host;
				cout << "Checking the URI: "<< *url<<endl;
				string reply = proxy.make_request(request.Assembly_Request());
				HTTP_Response response = HTTP_Response(reply);
				htmls[*url] = reply;

				set<string> all_hrefs = HTML_Parser::get_hrefs(response.data.c_str());
				set<string> local_hrefs;
				for (std::set<string>::iterator it=all_hrefs.begin(); it!=all_hrefs.end(); ++it)
			        if(this->eval_url(*it))
			        	local_hrefs.insert(this->parse_url(*it));
			    
			 //    all_hrefs = HTML_Parser::get_sources(response.data.c_str());
				// for (std::set<string>::iterator it=all_hrefs.begin(); it!=all_hrefs.end(); ++it)
			 //        if(this->eval_url(*it))
			 //        	local_hrefs.insert(this->parse_url(*it));

			 //    all_hrefs = HTML_Parser::get_imports(response.data.c_str());
				// for (std::set<string>::iterator it=all_hrefs.begin(); it!=all_hrefs.end(); ++it)
			 //        if(this->eval_url(*it))
			 //        	local_hrefs.insert(this->parse_url(*it));    	    
			        
			    
			    par_child[*url]=local_hrefs;
				
			    for (std::set<string>::iterator it=local_hrefs.begin(); it!=local_hrefs.end(); ++it)
			        to_request_next.insert(*it);

			}
		}
		to_request = to_request_next;
	 	i--;
	}while(i>=0);

	// print to check
	// for(std::map<string,set<string>>::iterator it=par_child.begin(); it!=par_child.end(); ++it){
 //        cout << it->first << ": ";
 //        set<string> urls =it->second;
 //        for(set<string>::iterator kt = urls.begin(); kt != urls.end(); ++kt)
 //        	cout << *kt << " ";
 //        cout << endl;	  
 //    }


}

std::string Spider::url_to_filename(std::string url_in){

	string filename("");
	string url = url_in;
	string slash("-");
	vector<string> splitted = String_Functions::split(url, "/");
	if(splitted.size()==1 && splitted[0].length()==0){
		filename = "root.html";	
		return filename;
	}
	for(int i = 0; i<splitted.size(); i++ ){
		filename.append(splitted[i]);
	}
	if(filename.find(".")>filename.length())
		filename.append(".html");
	else if(filename.find("?")<filename.length()){
		int ask = filename.find("?");
		filename = filename.substr(0,ask);
	}
	return filename;
}

void Spider::dump_htmls(int levels){
	this->generate_tree(levels);
	set<string> to_translate = visited_urls;

	dictionary[root]="index.html";
	to_translate.erase(root);

	for(set<string>::iterator it = to_translate.begin(); it!=to_translate.end(); ++it)
		dictionary[*it]=Spider::url_to_filename(*it);
	
	

	for(std::map<string,string>::iterator it=htmls.begin(); it!=htmls.end(); ++it){
     
        HTTP_Response resp = HTTP_Response(it->second);
        if(resp.fields.find("Content-Type:") != resp.fields.end())
        	if(resp.fields["Content-Type:"].find("html")<resp.fields["Content-Type:"].length()){
        		htmls[it->first] = HTML_Parser::isolate_html(it->second.c_str());
			}else{	
				/* What to do if its not HTML?*/
				htmls[it->first] = resp.data;	
			}
		else{	
			htmls[it->first] = resp.data;
		}
	}



	for(std::map<string,string>::iterator it=htmls.begin(); it!=htmls.end(); ++it)
    	for(std::map<string,string>::iterator dt=dictionary.begin(); dt!=dictionary.end(); ++dt){
    		string from("\"");from.append(dt->first.c_str());from.append("\"");
    		string to("\"");to.append(dt->second.c_str());to.append("\"");
    		it->second = String_Functions::replace(it->second,from.c_str(),to.c_str());
    		if(aliases.find(dt->second) != aliases.end()){
    			string from("\"");from.append(aliases[dt->second].c_str());from.append("\"");
    			string to("\"");to.append(dt->second.c_str());to.append("\"");
    			it->second = String_Functions::replace(it->second,from.c_str(),to.c_str());
    		}
    }       	
		


	for(std::map<string,string>::iterator it=htmls.begin(); it!=htmls.end(); ++it){
		cout << "Saving file: " << dictionary[it->first] << endl;
        String_Functions::string_to_file(it->second, dictionary[it->first].c_str());   
    }
}