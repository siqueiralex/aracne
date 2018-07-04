#include "../include/Spider.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

Spider::Spider(){

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
			host = result2[0];	
		}else{
			if(host!=result2[0]) return false;
		}
	}

	return true;
}
